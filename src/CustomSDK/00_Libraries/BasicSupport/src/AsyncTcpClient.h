#pragma once

#ifndef ASYNCTCPCLIENT_H
# define ASYNCTCPCLIENT_H

#include <string>
#include <memory>

class AsyncTcpClient
{
public:
  AsyncTcpClient();
  ~AsyncTcpClient();
public:
  void bindLocalPort(const std::string& local_host,const std::string& local_port);
  void connectRemoteServer(const std::string& remote_host,const std::string& remote_port);
  void startReceive();
public:
  void sendMessage(const std::string& message_content);
public:
  void setMessageParser(const std::shared_ptr<class AbstractMessageFrameParser>& message_frame_parser);
private:
  class AsyncTcpClientPrivate* private_ptr;
};

#endif//!ASYNCTCPCLIENT_H
