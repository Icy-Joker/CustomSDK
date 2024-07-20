#pragma once

#ifndef ASYNCTCPSERVER_H
# define ASYNCTCPSERVER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/ip/tcp.hpp>

class AsyncTcpServer
{
private:
  boost::asio::io_context io_context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> executor_work_guard;

  boost::asio::ip::tcp::socket socket_server;
};

#endif//!ASYNCTCPSERVER_H
