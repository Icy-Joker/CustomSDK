#include "stdafx.h"

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
  int result = 0;

  boost::asio::io_context io_context;
  boost::asio::ip::tcp::socket socket(io_context);

  boost::asio::ip::tcp::resolver resolver(io_context);

  resolver.async_resolve("127.0.0.1","5555",[&](const boost::system::error_code& error_code,const boost::asio::ip::tcp::resolver::results_type& results)
  {
    if(!error_code)
    {
      boost::asio::async_connect(socket,results.begin(),results.end(),[&](const boost::system::error_code& error_code,boost::asio::ip::tcp::resolver::results_type::iterator it_endpoint)
      {
        if(!error_code)
        {
          std::cout << "Connected" << std::endl;

          boost::thread thread_async_send([&]
          {
            static boost::function<void(const boost::system::error_code&,std::size_t)> function_async_send = [&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
            {
              if(!error_code)
              {
                std::cout << "bytes_transferred:" << bytes_transferred << std::endl;
                socket.async_send(boost::asio::buffer("Hello Wrold"),function_async_send);
              }
              else
              {
                std::cout << "error_code:" << error_code << std::endl;
              }
              boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
            };
            if(socket.is_open())
            {
              socket.async_send(boost::asio::buffer("Hello Wrold"),function_async_send);
            }
          });
          thread_async_send.join();
        }
      });
    }
    else
    {
    }
  });

  while(true)
  {
    io_context.run();
  }

  return result;
}
