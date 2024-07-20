#pragma once

#ifndef EVENTBUS_H
# define EVENTBUS_H

#include <memory>
#include <mutex>
#include <string>
#include <functional>
#include <typeindex>
#include <typeinfo>

#include <fmt/format.h>

#include <CommonFramework/LogManager.h>

struct AbstractEvent
{
  virtual ~AbstractEvent() = default;
  virtual std::string getName() const = 0;
};

class EventBus
{
public:
  // 注册事件监听器
  template<typename EventType>
  void subscribe(std::function<void(const EventType&)> handler)
  {
    std::lock_guard<std::mutex> lock(mutex);
    auto wrapper = [handler](const std::shared_ptr<AbstractEvent>& event)
    {
      LOG_INFO("Calling Event[{}]...",event->getName());

      if(auto real_event = std::dynamic_pointer_cast<EventType>(event))
      {
        handler(*real_event);
      }
    };
    this->handlers[std::type_index(typeid(EventType))].emplace_back(std::move(wrapper));
  }

  // 派发事件
  template<typename EventType>
  void publish(const EventType& event) const
  {
    auto it_found = handlers.find(std::type_index(typeid(EventType)));
    if(it_found != handlers.end())
    {
      LOG_INFO("Distributing Event[{}]...",event.getName());

      auto event_ptr = std::make_shared<EventType>(event);
      for(const auto& handler : it_found->second)
      {
        handler(event_ptr);
      }
    }
  }
private:
  std::mutex mutex;
  std::unordered_map<std::type_index,std::vector<std::function<void(std::shared_ptr<AbstractEvent>)>>> handlers;
};

#endif//!EVENTBUS_H
