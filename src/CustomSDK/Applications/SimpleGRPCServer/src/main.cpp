#include "stdafx.h"

#include "SimpleGRPCServer.h"

#include <CustomFramework/CustomFrameworkManager.h>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#include <iostream>

// int main(int argc,char* argv[])
// {
//   int result = 0;
//
//   boost::program_options::options_description option_description("Allowed options");
//   option_description.add_options()
//       ("config_path,c",boost::program_options::value<std::string>(),"配置文件路径")
//       ("help,h","打印此帮助信息");
//
//   boost::program_options::variables_map map_variables;
//   try
//   {
//     boost::program_options::store(boost::program_options::command_line_parser(argc,argv).options(option_description).run(),map_variables);
//     boost::program_options::notify(map_variables);
//
//     if(argc > 1 && !map_variables.count("help"))
//     {
//       const std::string config_path = map_variables.at("config_path").as<std::string>();
//
//       CustomFrameworkManager::getInstance()->initializeWithConfig(config_path.c_str());
//
//       try
//       {
//         boost::asio::io_context io_context;
//         boost::asio::signal_set signals(io_context, SIGINT,SIGTERM);// 捕获 SIGINT（Ctrl+C）
//
//         signals.async_wait([](const boost::system::error_code& error,int signal_number)
//         {
//           if(!error)
//           {
//             std::cout << "Caught signal " << signal_number << ", stopping the program..." << std::endl;
//           }
//         });// 异步处理信号
//
//         // 在另一个线程中运行 io_context
//         std::thread io_thread([&]()
//         {
//           io_context.run();// 运行 io_context 以处理异步操作
//         });
//
//         std::cout << "Press Ctrl+C to stop the program..." << std::endl;
//         // 主线程循环，直到捕获 SIGINT 信号
//         SimpleGreetingService simple_greeting_service;
//         simple_greeting_service.run();
//
//         io_thread.join();// 等待 io_thread 完成
//       }
//       catch(const std::exception& e)
//       {
//         std::cerr << "Exception: " << e.what() << std::endl;
//       }
//
//       std::cout << "Program has been stopped." << std::endl;
//     }
//     else
//     {
//       option_description.print(std::cout,'f');
//     }
//   }
//   catch(boost::program_options::error& error)
//   {
//     std::cout << error.what() << std::endl;
//   }
//   catch(...)
//   {
//     std::cout << "Unknown error!" << std::endl;
//   }
//
//   return result;
// }
//
int main(int argc,char* argv[])
{
  int result = 0;

  SimpleGRPCServer server;
  server.run();

  return result;
}
