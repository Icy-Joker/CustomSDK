#pragma once

#ifndef TIMER_H
# define TIMER_H

#include <functional>

class BasicSupport_API Timer
{
public:
  Timer();
  ~Timer();
public:
  void setTimeout(uint64_t timeout);
  void registerCallback(std::function<void()> callback);
public:
  void start(bool loop_enabled = false);
  void stop();

  void pause();
  void resume();
private:
  class TimerPrivate* private_ptr;
};

#endif//!TIMER_H
