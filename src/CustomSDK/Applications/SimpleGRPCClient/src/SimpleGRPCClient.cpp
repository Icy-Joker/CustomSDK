#include "stdafx.h"

#include "SimpleGRPCClient.h"
#include "SimpleGRPCClientPrivate.h"

SimpleGRPCClient::SimpleGRPCClient(const std::string& service_address):
  private_ptr(new SimpleGRPCClientPrivate())
{
}

SimpleGRPCClient::~SimpleGRPCClient()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

std::string SimpleGRPCClient::doSayHello(const std::string& username) const
{
  std::string result;

  if(private_ptr)
  {
    result = SimpleGRPCClientPrivate::doSayHello(username);
  }

  return result;
}
