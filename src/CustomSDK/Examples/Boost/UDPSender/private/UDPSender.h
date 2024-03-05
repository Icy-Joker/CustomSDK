#pragma once

#ifndef __UDPSENDER_H__
# define __UDPSENDER_H__

struct UDPSenderPrivate;

class UDPSender
{
public:
  UDPSender();
  ~UDPSender();
public:
protected:
private:
  UDPSenderPrivate* _p;
};

#endif // !__UDPSENDER_H__
