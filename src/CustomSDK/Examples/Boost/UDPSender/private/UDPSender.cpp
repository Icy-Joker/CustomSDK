#include "stdafx.h"

#include "UDPSender.h"
#include "UDPSenderPrivate.h"

UDPSender::UDPSender():
  _p(new UDPSenderPrivate())
{
}

UDPSender::~UDPSender()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}
