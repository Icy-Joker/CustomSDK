#pragma once

#ifndef __SIMPLEGREETINGPROXY_H__
# define __SIMPLEGREETINGPROXY_H__

#include <SimpleGreeting.grpc.pb.h>

class SimpleGreetingProxy
{
public:
  explicit SimpleGreetingProxy(const std::string& service_address);
  ~SimpleGreetingProxy();
public:
  [[nodiscard]] std::string doSayHello(const std::string& name) const;
private:
  std::unique_ptr<SimpleGreeting::SimpleGreetingService::Stub> stub;
};

#endif // !__SIMPLEGREETINGPROXY_H__
