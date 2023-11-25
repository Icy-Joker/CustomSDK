#include "stdafx.h"

#include <sys/socket.h>
#include <sys/errno.h>
#include <netinet/in.h>
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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    int bind_result = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_result != -1) 
    {
      // 监听端口
      listen(server_socket, 5);
      while(true)
      {
        // 接受客户端连接请求
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
        if (client_socket != -1)
        {
          // 接收客户端消息
          char buffer[1024] = {0};
          int recv_result = recv(client_socket, buffer, 1024, 0);
          if (recv_result != -1)
          {
            std::cout << "收到客户端消息：" << buffer << std::endl;
            // 发送响应消息给客户端
            const char *response = "Hello, Client!";
            send(client_socket, response, strlen(response), 0);
          }
          else
          {
            std::cout << "接收客户端消息失败" << std::endl;
          }
          close(client_socket);
        }
        else
        {
          std::cout << "接受客户端连接请求失败" << std::endl;
        }
      }
    }
    else
    {
    }
    // 关闭服务套接字
    close(server_socket);
  }
  return 0;
}
