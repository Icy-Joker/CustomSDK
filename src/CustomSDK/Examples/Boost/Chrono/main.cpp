#include "stdafx.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <thread>
#include <chrono>

int main(int argc,char* argv[])
{
  int result = 0;

  auto time_point_start = boost::chrono::high_resolution_clock::now();
  
  std::cout << boost::filesystem::current_path() << "\n";
  
  //auto time_point_end = boost::chrono::high_resolution_clock::now();
  
  auto time_span = boost::chrono::duration_cast<boost::chrono::nanoseconds>(time_point_start.time_since_epoch());

  std::cout << time_span.count() << "\n";
  
  if(true)
  {
    boost::thread thread_work([&]
    {
      while(true)
      {
        try
        {
          boost::this_thread::sleep_for(boost::chrono::seconds(2));
          std::cout<<"a\n";
          //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        catch(...)
        {
          std::cout << "1324142142";
        }
      }
    });
    thread_work.join();
  }

  return result;
}
