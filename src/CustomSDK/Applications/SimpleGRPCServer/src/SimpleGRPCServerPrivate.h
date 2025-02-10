#pragma once

#ifndef __SIMPLEGRPCSERVERPRIVATE_H__
# define __SIMPLEGRPCSERVERPRIVATE_H__

#include <grpcpp/server_builder.h>

#include <boost/asio.hpp>

class SimpleGRPCServerPrivate
{
private:
  explicit SimpleGRPCServerPrivate();
  ~SimpleGRPCServerPrivate();
private:
  void run();
  void stop();
private:
  std::unique_ptr<grpc::Server> server;

  boost::asio::io_context io_context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> executor_work_guard;

  friend class SimpleGRPCServer;
};

#endif // !__SIMPLEGRPCSERVERPRIVATE_H__
