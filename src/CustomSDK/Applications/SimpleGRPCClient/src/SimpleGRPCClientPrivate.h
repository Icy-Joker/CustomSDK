#pragma once

#ifndef __SIMPLEGRPCCLIENTPRIVATE_H__
# define __SIMPLEGRPCCLIENTPRIVATE_H__

#include <string>

class SimpleGRPCClientPrivate
{
private:
  explicit SimpleGRPCClientPrivate();
  ~SimpleGRPCClientPrivate();
private:
  static std::string doSayHello(const std::string& username);
private:
  friend class SimpleGRPCClient;
};

#endif // !__SIMPLEGRPCCLIENTPRIVATE_H__
