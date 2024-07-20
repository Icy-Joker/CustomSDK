#include "stdafx.h"

#include <boost/asio/connect.hpp>

#include "AsyncTcpClientPrivate.h"

AsyncTcpClientPrivate::AsyncTcpClientPrivate():
  executor_work_guard(io_context.get_executor()),
  socket_client(io_context),
  resolver(io_context)
{
}

AsyncTcpClientPrivate::~AsyncTcpClientPrivate()
{
}

void AsyncTcpClientPrivate::bindLocalPort(const std::string& local_host,const std::string& local_port)
{
}

void AsyncTcpClientPrivate::connectRemoteServer(const std::string& remote_host,const std::string& remote_port)
{
  boost::asio::ip::tcp::resolver resolver(socket_client.get_executor());
  auto endpoints = resolver.resolve(remote_host,remote_port);
  // boost::asio::async_connect(socket_client,endpoints,[this](boost::system::error_code error_code,auto)
  // {
  //   if(!error_code)
  //   {
  //   }
  // });
}

void AsyncTcpClientPrivate::startReceive()
{
  // socket_client.async_read_some(boost::asio::dynamic_buffer(message_buffer),
  //   [this](boost::system::error_code error_code,std::size_t length)
  //   {
  //     if(!error_code)
  //     {
  //     }
  //   });
}

void AsyncTcpClientPrivate::sendMessage(const std::string& message_content)
{
}

void AsyncTcpClientPrivate::setMessageParser(std::shared_ptr<class AbstractMessageFrameParser> message_frame_parser)
{
}
