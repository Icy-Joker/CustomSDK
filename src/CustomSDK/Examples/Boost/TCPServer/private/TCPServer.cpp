#include "stdafx.h"

#include "TCPServer.h"
#include "TCPServerPrivate.h"

TCPServer::TCPServer():
  _p(new TCPServerPrivate())
{
}

TCPServer::~TCPServer()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}
