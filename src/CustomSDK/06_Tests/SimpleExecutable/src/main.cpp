#include "stdafx.h"

#include <iostream>

#include <boost/thread.hpp>
#include <boost/thread/pthread/thread_data.hpp>

#include <BasicSupport/Timer.h>

struct StructTimer
{
  Timer timer;
};

int main(int argc,char* argv[])
{
  int result = 0;

  {
    StructTimer timer;
    timer.timer.registerCallback([]()
    {
      std::cout << "Hello World..." << std::endl;
    });
    timer.timer.setTimeout(1);
    timer.timer.start();

    boost::this_thread::sleep_for(boost::chrono::seconds(2));
  }

  std::cout << "Hello World" << std::endl;

  while(true)
  {
  }
  return result;
}
