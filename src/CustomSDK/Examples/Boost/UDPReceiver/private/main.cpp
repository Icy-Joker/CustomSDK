#include "stdafx.h"

#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
  int result = 0;

  boost::asio::io_context io_context;
  boost::asio::ip::udp::endpoint local_endpoint(boost::asio::ip::udp::v4(),4800);
  boost::asio::ip::udp::socket socket(io_context,local_endpoint);

  boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string("127.0.0.1"),4801);

  std::array<char,1024> receive_buffer = {'\0'};
  boost::function<void(const boost::system::error_code&,std::size_t)> function_async_send_to = [&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
  {
    if(!error_code)
    {
      std::cout << bytes_transferred << receive_buffer.data() << std::endl;
      socket.async_receive_from(boost::asio::buffer(receive_buffer),remote_endpoint,function_async_send_to);
    }
  };
  socket.async_receive_from(boost::asio::buffer(receive_buffer),remote_endpoint,function_async_send_to);

  while(true)
  {
    io_context.run();
  }

  return result;
}
