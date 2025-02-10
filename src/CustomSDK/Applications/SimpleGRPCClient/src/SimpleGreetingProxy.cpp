#include "stdafx.h"

#include "SimpleGreetingProxy.h"

#include <grpcpp/grpcpp.h>

SimpleGreetingProxy::SimpleGreetingProxy(const std::string& service_address):
  stub(SimpleGreeting::SimpleGreetingService::NewStub(grpc::CreateChannel(service_address,grpc::InsecureChannelCredentials())))
{
}

SimpleGreetingProxy::~SimpleGreetingProxy()
{
}

std::string SimpleGreetingProxy::doSayHello(const std::string& name) const
{
  std::string result;

  {
    SimpleGreeting::SimpleGreetingRequest request;
    request.set_name(name);

    SimpleGreeting::SimpleGreetingResponse response;
    grpc::ClientContext context;

    grpc::Status status = this->stub->doSayHello(&context,request,&response);
    if(status.ok())
    {
      result = response.message();
    }
    else
    {
      std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }
  }

  return result;
}
