#include "stdafx.h"

#include "SimpleGRPCServerPrivate.h"

#include "SimpleGreetingService.h"

#include <boost/asio.hpp>
#include <boost/thread.hpp>

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::InsecureServerCredentials;

SimpleGRPCServerPrivate::SimpleGRPCServerPrivate():
  executor_work_guard(boost::asio::make_work_guard(io_context))
{
}

SimpleGRPCServerPrivate::~SimpleGRPCServerPrivate()
{
}

void SimpleGRPCServerPrivate::run()
{
  std::vector<std::string> server_addresses = {"0.0.0.0:50051"};

  ServerBuilder builder;
  std::for_each(server_addresses.begin(),server_addresses.end(),[&](const std::string& server_address)
  {
    builder.AddListeningPort(server_address,InsecureServerCredentials());
    std::cout << "Server listening on " << server_address << std::endl;
  });

  grpc::Service* simple_greeting_service = new SimpleGreetingService();
  builder.RegisterService(simple_greeting_service);

  if((server = builder.BuildAndStart()))
  {
    // 注册服务
    //doRegisterService();
    //getAvailableService();
    // 等待服务运行
    server->Wait();
  }
  delete simple_greeting_service;
  simple_greeting_service = nullptr;
}

void SimpleGRPCServerPrivate::stop()
{
  if(server)
  {
    executor_work_guard.reset();
    server->Shutdown();
  }
}
