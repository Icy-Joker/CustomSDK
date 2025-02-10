#include "stdafx.h"

#include "SimpleGRPCServer.h"

#include "SimpleGRPCServerPrivate.h"

#include <grpcpp/server_builder.h>

SimpleGRPCServer::SimpleGRPCServer():
  private_ptr(new SimpleGRPCServerPrivate())
{
  grpc::EnableDefaultHealthCheckService(true);// 启用默认健康检查服务
}

SimpleGRPCServer::~SimpleGRPCServer()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

bool SimpleGRPCServer::initializeWithConfig(const char* config_file_path)
{
  bool result = false;

  return result;
}

void SimpleGRPCServer::run()
{
  if(private_ptr)
  {
    private_ptr->run();
  }
}

void SimpleGRPCServer::stop()
{
  if(private_ptr)
  {
    private_ptr->stop();
  }
}
