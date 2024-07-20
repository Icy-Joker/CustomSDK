#include "stdafx.h"

#include "AsyncTcpClient.h"
#include "AsyncTcpClientPrivate.h"

AsyncTcpClient::AsyncTcpClient():
  private_ptr(new AsyncTcpClientPrivate())
{
}

AsyncTcpClient::~AsyncTcpClient()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

void AsyncTcpClient::bindLocalPort(const std::string& local_address,const std::string& local_port)
{
  private_ptr->bindLocalPort(local_address,local_port);
}

void AsyncTcpClient::connectRemoteServer(const std::string& remote_address,const std::string& remote_port)
{
  private_ptr->connectRemoteServer(remote_address,remote_port);
}

void AsyncTcpClient::startReceive()
{
  private_ptr->startReceive();
}

void AsyncTcpClient::sendMessage(const std::string& message_content)
{
  private_ptr->sendMessage(message_content);
}

void AsyncTcpClient::setMessageParser(const std::shared_ptr<AbstractMessageFrameParser>& message_frame_parser)
{
  private_ptr->setMessageParser(message_frame_parser);
}
