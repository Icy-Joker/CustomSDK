
#include "SimpleGRPCClient.h"

int main()
{
  const char* target_address = "localhost:50051";
  SimpleGRPCClient client(target_address);

  std::string username = "World";

  const std::string& server_reply = client.doSayHello(username);
  if(!server_reply.empty())
  {
    std::cout << "Server reply: " << server_reply << std::endl;
  }

  return 0;
}
