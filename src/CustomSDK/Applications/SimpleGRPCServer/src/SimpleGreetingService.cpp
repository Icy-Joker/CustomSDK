#include "stdafx.h"

#include "SimpleGreetingService.h"

using SimpleGreeting::SimpleGreetingRequest;
using SimpleGreeting::SimpleGreetingResponse;

SimpleGreetingService::SimpleGreetingService():
  SimpleGreeting::SimpleGreetingService::Service()
{
}

SimpleGreetingService::~SimpleGreetingService()
{
}

grpc::Status SimpleGreetingService::doSayHello(grpc::ServerContext* context,const SimpleGreeting::SimpleGreetingRequest* request,SimpleGreeting::SimpleGreetingResponse* response)
{
  std::string name = request->name();
  std::string message = "Hello " + name + "!";
  response->set_message(message);
  std::cout << "Received request from: " << name << std::endl;
  return grpc::Status::OK;
}
