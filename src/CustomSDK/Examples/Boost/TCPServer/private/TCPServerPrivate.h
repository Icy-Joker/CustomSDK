#pragma once

#ifndef __TCPSERVERPRIVATE_H__
# define __TCPSERVERPRIVATE_H__

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <QObject>

#include <set>

class TCPServerPrivate : public QObject
{
  Q_OBJECT
public:
  explicit TCPServerPrivate(QObject* parent = nullptr);
  ~TCPServerPrivate();
public:
  void startServer(unsigned short);
  void stopServer();
private:
  void doAccept();
  signals:
  void sessionCreated();
  void messageReceived();
  void sessionDestroyed();
private:
  boost::asio::io_context io_context;
  boost::asio::ip::tcp::endpoint endpoint;
  boost::asio::ip::tcp::socket socket;
  boost::asio::ip::tcp::acceptor acceptor;
  boost::thread thread_io_context;

  std::set<boost::shared_ptr<class TCPSession>> set_tcp_session;
};

#endif // !__TCPSERVERPRIVATE_H__
