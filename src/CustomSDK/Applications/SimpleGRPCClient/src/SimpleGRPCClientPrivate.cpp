#include "stdafx.h"

#include "SimpleGRPCClientPrivate.h"

#include "SimpleGreetingProxy.h"

SimpleGRPCClientPrivate::SimpleGRPCClientPrivate()
{
}

SimpleGRPCClientPrivate::~SimpleGRPCClientPrivate()
{
}

std::string SimpleGRPCClientPrivate::doSayHello(const std::string& username)
{
  std::string result;

  {
    const auto* proxy = new SimpleGreetingProxy("127.0.0.1:50051");
    result = proxy->doSayHello(username);
  }

  return result;
};
