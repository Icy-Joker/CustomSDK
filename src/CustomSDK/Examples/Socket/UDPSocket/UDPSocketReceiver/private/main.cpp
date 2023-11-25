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
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    int bind_result = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_result != -1) 
    {
      struct sockaddr_in client_addr;
      std::size_t size_client_addr = sizeof(client_addr);
      while(true)
      { 
        // 接收客户端消息
        char buffer[1024] = {0};
        int recv_length = recvfrom(server_socket, buffer, 1024,0, (struct sockaddr*)&client_addr,(socklen_t*)&size_client_addr);
        if (recv_length > 0)
        {
          std::cout << "收到客户端消息：" << buffer << std::endl;
          // 发送响应消息给客户端
          const char *response = "Hello, Client!";
          if(sendto(server_socket, (const void*)response, strlen(response), 0,(struct sockaddr*)&client_addr,size_client_addr) != -1)
          {
            std::cout << "回应客户端消息：" << buffer << std::endl;
          }
          else
          {
          }
        }
        else
        {
          std::cout << "接收客户端消息失败" << std::endl;
        }
      }
    }
    else
    {
      std::cout << "套接字绑定失败" << std::endl;
    }
    // 关闭服务套接字
    close(server_socket);
  }
  return 0;
}
