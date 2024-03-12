#include "stdafx.h"

#include "TCPServerPrivate.h"
#include "TCPSession.h"

#include <boost/function.hpp>

TCPServerPrivate::TCPServerPrivate(QObject* parent /*= nullptr*/):
  socket(boost::asio::ip::tcp::socket(this->io_context)),
  acceptor(boost::asio::ip::tcp::acceptor(this->io_context))
{
}

TCPServerPrivate::~TCPServerPrivate()
{
  this->stopServer();
}

void TCPServerPrivate::startServer(unsigned short ip_port)
{
  this->endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("0.0.0.0"),ip_port);
  //this->socket = boost::asio::ip::tcp::socket (this->io_context);
  this->acceptor = boost::asio::ip::tcp::acceptor(this->io_context,this->endpoint);

  if(this->acceptor.is_open())
  {
    doAccept();

    this->thread_io_context = boost::thread([&]
    {
      while(true)
      {
        try
        {
          boost::this_thread::interruption_point();

          this->io_context.run();

          boost::this_thread::sleep_for(boost::chrono::seconds(0));
        }
        catch(const boost::thread_interrupted& e)
        {
          break;
        }
      }
    });
  }
}

void TCPServerPrivate::stopServer()
{
  std::for_each(this->set_tcp_session.begin(),this->set_tcp_session.end(),[&](boost::shared_ptr<TCPSession> tcp_session_ptr)
  {
    tcp_session_ptr->stop();
  });

  try
  {
    if(this->acceptor.is_open())
    {
      this->acceptor.cancel();
    }
  }
  catch(const boost::system::system_error& error)
  {
    qDebug("acceptor.close() : %s",error.what());
  }

  try
  {
    if(this->acceptor.is_open())
    {
      this->acceptor.close();
    }
  }
  catch(const boost::system::system_error& error)
  {
    qDebug("acceptor.close() : %s",error.what());
  }

  this->thread_io_context.interrupt();
  if(this->thread_io_context.joinable())
  {
    this->thread_io_context.join();
  }
}

void TCPServerPrivate::doAccept()
{
  boost::asio::ip::tcp::socket(this->io_context);
  std::array<char,1024> receive_buffer = {'\0'};
  this->acceptor.async_accept(socket,[=](const boost::system::error_code& error_code)
  {
    if(!error_code)
    {
      qDebug("async_accept");
      boost::shared_ptr<TCPSession> tcp_session_ptr = boost::make_shared<TCPSession>(std::move(socket));
      set_tcp_session.insert(tcp_session_ptr);
      qDebug("size : %d",set_tcp_session.size());
      doAccept();
    }
    else
    {
      qDebug("%s",error_code.what().c_str());
    }
  });
}