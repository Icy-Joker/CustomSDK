#pragma once

#ifndef __TCPCLIENT_H__
# define __TCPCLIENT_H__

struct TCPClientPrivate;

class TCPClient
{
public:
  TCPClient();
  ~TCPClient();
public:
protected:
private:
  TCPClientPrivate* _p;
};

#endif // !__TCPCLIENT_H__
