#pragma once

#ifndef TIMERPRIVATE_H
# define TIMERPRIVATE_H

#include <boost/asio/io_context.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/atomic.hpp>

class TimerPrivate
{
private:
  explicit TimerPrivate();
  ~TimerPrivate();
private:
  void setTimeout(uint64_t timeout);
  void registerCallback(std::function<void()>&& callback);
private:
  void start(bool loop_enabled = false);
  void stop();

  void pause();
  void resume();
private:
  void schedule();
private:
  boost::asio::io_context io_context;
  boost::thread thread_io_context;
  boost::asio::steady_timer timer;
  std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> executor_work_guard;

  std::chrono::milliseconds timeout;
  std::chrono::steady_clock::time_point start_point;
  std::chrono::milliseconds time_remaining{0};

  std::vector<std::function<void()>> callbacks;

  boost::atomic<bool> loop_enabled{false};

  enum
  {
    Unknown,
    Running,
    Paused,
    Finished,
    Invalid
  } state;
private:
  friend class Timer;
};

#endif//!TIMERPRIVATE_H
