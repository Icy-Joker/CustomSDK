#include "stdafx.h"

#include "TCPClient.h"
#include "TCPClientPrivate.h"

TCPClient::TCPClient():
  _p(new TCPClientPrivate())
{
}

TCPClient::~TCPClient()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}
