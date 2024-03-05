#include "stdafx.h"

#include "UDPReceiver.h"
#include "UDPReceiverPrivate.h"

UDPReceiver::UDPReceiver():
  _p(new UDPReceiverPrivate())
{
}

UDPReceiver::~UDPReceiver()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}
