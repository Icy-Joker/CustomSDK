#include "stdafx.h"

#include <iostream>

#include <boost/program_options.hpp>

#include <CustomFramework/CustomFrameworkManager.h>

#include "CustomModuleExecutable.h"

int main(int argc,char* argv[])
{
  int result = 0;
  {
    boost::program_options::options_description option_description("Allowed options");
    option_description.add_options()
        ("config_path,c",boost::program_options::value<std::string>()->default_value("../config/config4CPlusPlus.xml"),"配置文件路径")
        ("help,h","打印此帮助信息");

    boost::program_options::variables_map map_variables;
    try
    {
      boost::program_options::store(boost::program_options::command_line_parser(argc,argv).options(option_description).run(),map_variables);
      boost::program_options::notify(map_variables);

      if(argc > 1 && !map_variables.count("help"))
      {
        const std::string config_path = map_variables.at("config_path").as<std::string>();

        CustomFrameworkManager::instance()->initializeWithConfig(config_path);

        CustomModuleExecutable custom_module_executable;
        custom_module_executable.doSomething();
      }
      else
      {
        option_description.print(std::cout,'f');
      }
    }
    catch(boost::program_options::error& error)
    {
      std::cout << error.what() << std::endl;
    }
    catch(...)
    {
      std::cout << "Unknown error!" << std::endl;
    }
  }
  return result;
}
