#pragma once

#ifndef __SIMPLEGRPCCLIENT_H__
# define __SIMPLEGRPCCLIENT_H__

#include <SimpleGreeting.grpc.pb.h>

class SimpleGRPCClientPrivate;

class SimpleGRPCClient
{
public:
  explicit SimpleGRPCClient(const std::string& service_address);
  ~SimpleGRPCClient();
public:
  [[nodiscard]] std::string doSayHello(const std::string& username) const;
private:
  SimpleGRPCClientPrivate* private_ptr;;
};

#endif // !__SIMPLEGRPCCLIENT_H__
