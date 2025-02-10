#pragma once

#ifndef __SIMPLEGREETINGSERVICE_H__
# define __SIMPLEGREETINGSERVICE_H__

#include <SimpleGreeting.grpc.pb.h>

class SimpleGreetingService : public SimpleGreeting::SimpleGreetingService::Service
{
public:
  explicit SimpleGreetingService();
  ~SimpleGreetingService() override;
private:
  grpc::Status doSayHello(grpc::ServerContext* context,const SimpleGreeting::SimpleGreetingRequest* request,SimpleGreeting::SimpleGreetingResponse* response) override;
};

#endif // !__SIMPLEGREETINGSERVICE_H__
