#include "stdafx.h"

#include <sys/socket.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <iostream>

int main(int argc,char* argv[])
{
  int server_socket = socket(PF_INET,SOCK_DGRAM,0);
  if(server_socket != -1)
  {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4800);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    struct sockaddr_in client_addr;
    std::size_t size_client_addr = sizeof(client_addr);
    while(true)
    { 
      {
        // 发送响应消息给客户端
        const char *response = "Hello, Client!";
        if(sendto(server_socket, (const void*)response, strlen(response), 0,(struct sockaddr*)&server_addr,sizeof(server_addr)))
        {
          std::cout << "发送消息：" << response << std::endl;
        }
      }
    }
    close(server_socket);
  }
  return 0;
}
