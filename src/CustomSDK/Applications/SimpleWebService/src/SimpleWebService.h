#pragma once

#ifndef __SIMPLEWEBSERVICE_H__
# define __SIMPLEWEBSERVICE_H__

class SimpleWebService
{
public:
  explicit SimpleWebService();
  ~SimpleWebService();
public:
  bool start();
  bool stop();
private:
  void doRegister();
  void doDeregisterService();
};

#endif // !__SIMPLEWEBSERVICE_H__
