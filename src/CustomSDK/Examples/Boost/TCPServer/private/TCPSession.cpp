#include "stdafx.h"

#include "TCPSession.h"

#include <QDebug>

TCPSession::TCPSession(boost::asio::ip::tcp::socket socket):
  socket(std::move(socket))
{
  this->start();
}

TCPSession::~TCPSession()
{
  this->stop();
}

void TCPSession::start()
{
  doReceive();
}

void TCPSession::stop()
{
  try
  {
    if(socket.is_open())
    {
      socket.cancel();
    }
  }
  catch(const boost::system::system_error& error)
  {
    qDebug("socket.cancel() : %s",error.what());
  }

  try
  {
    if(socket.is_open())
    {
      socket.close();
    }
  }
  catch(const boost::system::system_error& error)
  {
    qDebug("socket.close() : %s",error.what());
  }
}

void TCPSession::doReceive()
{
  if(this->socket.is_open())
  {
    static std::array<char,1024> receive_buffer;
    this->socket.async_receive(boost::asio::buffer(receive_buffer),[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
    {
      if(!error_code)
      {
        receive_buffer[bytes_transferred] = '\0';
        qDebug("%s",receive_buffer);
        //if(ui->checkBox_EnableAutoEcho->isChecked())
        //{
        //  this->socket.async_send(boost::asio::buffer(receive_buffer),[&](const boost::system::error_code& error_code,std::size_t bytes_transferred)
        //  {
        //    if(!error_code)
        //    {
        //    }
        //  });
        //}
        doReceive();
      }
      else
      {
        qDebug("async_receive %s",error_code.what().c_str());
        this->stop();
      }
    });
  }
  else
  {
    qDebug("async_receive bug");
  }
}