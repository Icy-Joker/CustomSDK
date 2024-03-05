#pragma once

#ifndef __TCPSERVERPRIVATE_H__
# define __TCPSERVERPRIVATE_H__

#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

struct TCPServerPrivate
{
  boost::asio::io_context io_context;
  boost::asio::ip::tcp::endpoint endpoint;
  boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
  boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;
  boost::thread thread_io_context;
};

#endif // !__TCPSERVERPRIVATE_H__
