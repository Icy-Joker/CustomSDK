#include "stdafx.h"

#include "BasicSupport/Timer.h"
#include "TimerPrivate.h"

#include <utility>

Timer::Timer() :
  private_ptr(new TimerPrivate())
{
}

Timer::~Timer()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

void Timer::setTimeout(unsigned long timeout)
{
  private_ptr->setTimeout(timeout);
}

void Timer::registerCallback(std::function<void()> callback)
{
  private_ptr->registerCallback(std::move(callback));
}

void Timer::start(bool loop_enabled)
{
  private_ptr->start(loop_enabled);
}

void Timer::stop()
{
  private_ptr->stop();
}

void Timer::pause()
{
  private_ptr->pause();
}

void Timer::resume()
{
  private_ptr->resume();
}
