#include "stdafx.h"

#include "TCPServer.h"

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include <QApplication>

#include <iostream>

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  TCPServer main_window;
  main_window.show();

  result = app.exec();

  //boost::asio::io_context io_context;
  //boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4(),5555);
  //boost::asio::ip::tcp::socket socket(io_context);
  //boost::asio::ip::tcp::acceptor acceptor(io_context,endpoint);

  //std::array<char,1024> read_buffer = { '\0' };
  //boost::function<void(const boost::system::error_code& error_code)> function_async_accept = [&](const boost::system::error_code& error_code)
  //{
  //  if(!error_code)
  //  {
  //    std::cout << "New Connextion" << std::endl;

  //    boost::thread thread_async_receive([&]
  //    {
  //      static boost::function<void(const boost::system::error_code&,std::size_t)> function_async_receive = [&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
  //      {
  //        if(!error_code)
  //        {
  //          std::cout << "bytes_transferred:" << bytes_transferred << "\t" << read_buffer.data() << std::endl;
  //          socket.async_receive(boost::asio::buffer(read_buffer),function_async_receive);
  //        }
  //        else
  //        {
  //          std::cout << "error_code:" << error_code << std::endl;
  //        }
  //      };

  //      if(socket.is_open())
  //      {
  //        socket.async_receive(boost::asio::buffer(read_buffer),function_async_receive);
  //      }
  //    });
  //    thread_async_receive.join();
  //  }
  //  else
  //  {

  //  }
  //  //acceptor.async_accept(socket,function_async_accept);
  //};

  //acceptor.async_accept(socket,function_async_accept);

  //while(true)
  //{
  //  io_context.run();
  //}

  return result;
}
