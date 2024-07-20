#include "stdafx.h"

#include "TimerPrivate.h"

#include <utility>
#include <memory>
#include <algorithm>
#include <functional>

#include <boost/make_unique.hpp>

TimerPrivate::TimerPrivate() :
  timer(io_context),
  timeout(0),
  state(Unknown)
{
}

TimerPrivate::~TimerPrivate()
{
  if(this->state != Unknown && this->state != Finished)
  {
    this->stop();
  }
}

void TimerPrivate::setTimeout(uint64_t timeout)
{
  this->timeout = std::chrono::milliseconds(timeout);
}

void TimerPrivate::registerCallback(std::function<void()>&& callback)
{
  this->callbacks.emplace_back(std::move(callback));
}

void TimerPrivate::start(bool loop_enabled)
{
  if(this->state != Running)
  {
    this->loop_enabled = loop_enabled;

    this->executor_work_guard = boost::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(this->io_context.get_executor());
    this->thread_io_context = boost::thread([&]()
    {
      if(this->io_context.stopped())
      {
        this->io_context.restart();
      }
      this->io_context.run();
    });

    this->state = Running;

    this->time_remaining = std::chrono::milliseconds(0);
    this->start_point = std::chrono::steady_clock::now();
    this->schedule();
  }
}

void TimerPrivate::stop()
{
  if(this->state == Running || this->state == Paused)
  {
    this->timer.cancel();//取消正在等待的定时任务
    this->executor_work_guard.reset();//允许io_context退出
    this->io_context.stop();//显式停止io_context,防止资源占用
    if(this->thread_io_context.get_id() != boost::this_thread::get_id() && this->thread_io_context.joinable())
    {
      this->thread_io_context.join();
    }

    this->state = Finished;
  }
}

void TimerPrivate::pause()
{
  if(this->state == Running)
  {
    this->timer.cancel();// 停止当前异步等待

    this->time_remaining = this->timeout - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->start_point);

    this->state = Paused;
  }
}

void TimerPrivate::resume()
{
  if(this->state == Paused)
  {
    this->state = Running;

    this->start_point = std::chrono::steady_clock::now();
    this->schedule();
  }
}

void TimerPrivate::schedule()
{
  if(this->state == Running)
  {
    this->start_point += std::chrono::milliseconds(time_remaining.count() > 0 ? time_remaining : timeout);

    timer.expires_at(this->start_point);
    timer.async_wait([this](const boost::system::error_code& error_code)
    {
      if(!error_code)
      {
        std::for_each(this->callbacks.begin(),this->callbacks.end(),[this](const std::function<void()>& callback)
        {
          callback();
        });

        if(loop_enabled)
        {
          this->time_remaining = std::chrono::milliseconds(0);
          this->schedule();
        }
      }
    });
  }
}
