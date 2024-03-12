#pragma once

#ifndef __TCPSESSION_H__
# define __TCPSESSION_H__

#include <boost/asio/ip/tcp.hpp>

class TCPSession : public std::enable_shared_from_this<TCPSession>
{
public:
  TCPSession(boost::asio::ip::tcp::socket socket);
  ~TCPSession();
public:
  void start();
  void stop();
private:
  void doReceive();
private:
  boost::asio::ip::tcp::socket socket;
};

#endif // !__TCPSESSION_H__
