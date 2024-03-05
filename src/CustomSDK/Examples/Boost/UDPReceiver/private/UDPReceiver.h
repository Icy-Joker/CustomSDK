#pragma once

#ifndef __UDPRECEIVER_H__
# define __UDPRECEIVER_H__

struct UDPReceiverPrivate;

class UDPReceiver
{
public:
  UDPReceiver();
  ~UDPReceiver();
public:
protected:
private:
  UDPReceiverPrivate* _p;
};

#endif // !__UDPRECEIVER_H__
