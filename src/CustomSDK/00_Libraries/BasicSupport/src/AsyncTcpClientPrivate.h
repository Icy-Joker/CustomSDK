#pragma once

#ifndef ASYNCTCPCLIENTPRIVATE_H
# define ASYNCTCPCLIENTPRIVATE_H

#include <memory>

#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/thread/thread.hpp>

#include "AbstractMessageFrameParser.h"

class AsyncTcpClientPrivate
{
private:
  explicit AsyncTcpClientPrivate();
  ~AsyncTcpClientPrivate();
public:
  void bindLocalPort(const std::string& local_host,const std::string& local_port);
  void connectRemoteServer(const std::string& remote_host,const std::string& remote_port);
  void startReceive();
public:
  void sendMessage(const std::string& message_content);
public:
  void setMessageParser(std::shared_ptr<class AbstractMessageFrameParser> message_frame_parser);
private:
  boost::asio::io_context io_context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> executor_work_guard;
  boost::thread thread_io_context;

  boost::asio::ip::tcp::socket socket_client;
  boost::asio::ip::tcp::resolver resolver;

  std::string message_buffer;
  std::shared_ptr<AbstractMessageFrameParser> message_frame_parser;
private:
  friend class AsyncTcpClient;
};

#endif//!ASYNCTCPCLIENTPRIVATE_H
