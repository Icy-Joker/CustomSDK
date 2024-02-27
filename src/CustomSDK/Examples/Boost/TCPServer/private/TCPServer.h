#pragma once

#ifndef __TCPSERVER_H__
# define __TCPSERVER_H__

struct TCPServerPrivate;

class TCPServer
{
public:
  TCPServer();
  ~TCPServer();
public:
protected:
private:
  TCPServerPrivate* _p;
};

#endif // !__TCPSERVER_H__
