#include "stdafx.h"

#include "CustomProject.h"
#include "CustomTarget.h"

#include <boost/program_options.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
  int result = 0;

  //生成Project
  boost::program_options::options_description description_project("For Project");
  description_project.add_options()
    ("project_name",boost::program_options::value<std::string>(),"项目名称")
    ("project_description",boost::program_options::value<std::string>()->default_value(std::string()),"项目描述")
    ("project_version",boost::program_options::value<std::string>()->default_value(std::string("0.0.0.0")),"项目版本号")
    ("child_folder",boost::program_options::value<std::string>()->default_value(std::string()),"项目子类别(以','分隔");
  //生成Target
  boost::program_options::options_description description_target("For Target");
  description_target.add_options()
    ("target_name",boost::program_options::value<std::string>(),"目标名称")
    ("target_type,t",boost::program_options::value<std::string>(),"目标类型(StaticLibrary|DynamicLibrary|PluginLibrary|ExecutableProgram)")
    ("enable_export","允许导出符号,仅对可执行程序有效(特殊情况下使用,例如需要为可扩展的可执行程序添加插件时)")
    ("public_class",boost::program_options::value<std::string>()->default_value(std::string()),"公开类列表(以','分隔)")
    ("private_class",boost::program_options::value<std::string>()->default_value(std::string()),"私有类列表(以','分隔)");
  //
  boost::program_options::options_description description_global("Allowed options");
  description_global.add_options()
    ("help,h","打印此帮助信息");
  description_global.add(description_project);
  description_global.add(description_target);
  description_global.add_options()
    ("output_directory,o",boost::program_options::value<std::string>()->default_value(std::string()),"输出目录");

  boost::program_options::variables_map map_variables;
  try
  {
    boost::program_options::store(boost::program_options::command_line_parser(argc,argv).options(description_global).run(),map_variables);
    boost::program_options::notify(map_variables);

    if(!map_variables.count("help"))
    {
      if(map_variables.count("project_name"))
      {
        const std::string project_name = map_variables["project_name"].as<std::string>();
        const std::string project_description = map_variables["project_description"].as<std::string>();
        const std::string project_version = map_variables["project_version"].as<std::string>();
        const std::string list_project_child_folder = map_variables["child_folder"].as<std::string>();
        const std::string project_output_directory = map_variables["output_directory"].as<std::string>();

        CustomProject custom_project(project_name);
        custom_project.setDescription(project_description);
        custom_project.setVersion(project_version);
        {
          std::string parent_directory_path = "Applications";
          std::istringstream iss(list_project_child_folder);
          std::string token;
          while (std::getline(iss, token, ',')) 
          {
            custom_project.appendChildTarget(parent_directory_path,token);
          }
        }

        custom_project.generate(project_output_directory);
      }
      else if(map_variables.count("target_name"))
      {
        const std::string target_name = map_variables["target_name"].as<std::string>();
        const std::string target_type = map_variables["target_type"].as<std::string>();
        const bool target_enable_export = map_variables.count("enable_export");
        const std::string target_public_class_list = map_variables["public_class"].as<std::string>();
        const std::string target_private_class_list = map_variables["private_class"].as<std::string>();
        const std::string target_output_directory = map_variables["output_directory"].as<std::string>();

        CustomTarget custom_target(target_name,target_type);
        custom_target.setEnableExport(target_enable_export);
        {
          std::istringstream iss(target_public_class_list);
          std::string token;
          while (std::getline(iss, token, ',')) 
          {
            custom_target.appendPublicClassName(token);
          }
        }
        {
          std::istringstream iss(target_private_class_list);
          std::string token;
          while (std::getline(iss, token, ',')) 
          {
            custom_target.appendPrivateClassName(token);
          }
        }
        custom_target.generate(target_output_directory);
      }
    }
    else
    {
      description_global.print(std::cout,'f');
    }
  }
  catch(boost::program_options::error& error)
  {
    std::cout << error.what() << std::endl;
  }
  catch(const char* error)
  {
    std::cout << error << std::endl;
  }
  catch(...)
  {
    std::cout << "Unknown error!" << std::endl;
  }

  return result;
}
