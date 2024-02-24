#include "stdafx.h"

#include "CustomTarget.h"
#include "CustomTargetPrivate.h"

#include "template_target.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>

#include <cassert>
#include <regex>
#include <iostream>

CustomTarget::CustomTarget(const std::string& target_name, const std::string& target_type):
  _p(new CustomTargetPrivate())
{
  assert(!target_name.empty());
  assert(!target_type.empty());

  setName(target_name);
  setType(target_type);
  if(target_type == "ExecutableProgram")
  {
    setEnableExport(false);
    appendPrivateClassName(target_name);
  }
}

CustomTarget::~CustomTarget()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}

void CustomTarget::setName(const std::string& target_name)
{
  _p->target_name = target_name;
}

void CustomTarget::setType(const std::string& target_type)
{
  _p->target_type = target_type;
}

void CustomTarget::setEnableExport(const bool& enable_export)
{
  if(getType() == "ExecutableProgram")
  {
    _p->target_enable_export = enable_export;
  }
}

void CustomTarget::appendPublicClassName(const std::string& class_name)
{
  _p->target_public_class_list.insert(class_name);
}

void CustomTarget::removePublicClassName(const std::string& class_name)
{
}

void CustomTarget::appendPrivateClassName(const std::string& class_name)
{
  _p->target_private_class_list.insert(class_name);
}

void CustomTarget::removePrivateClassName(const std::string& class_name)
{
}

const std::string& CustomTarget::getName() const
{
  return _p->target_name;
}

const std::string& CustomTarget::getType() const
{
  return _p->target_type;
}

const bool& CustomTarget::getEnableExport() const
{
  return _p->target_enable_export;
}

const std::set<std::string>& CustomTarget::getAllPublicClassName() const
{
  return _p->target_public_class_list;
}

const std::set<std::string>& CustomTarget::getAllPrivateClassName() const
{
  return _p->target_private_class_list;
}

bool CustomTarget::isValid() const
{
  bool result = false;

  result = true;

  return result;
}

bool CustomTarget::generatePreCompiledHeader(const std::string& output_directory) const
{
  bool result = false;

  const std::string& target_name = getName();

  boost::filesystem::path output_file_path(output_directory + "/stdafx.h");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      const std::string target_api_macro_import = (getType() == "ExecutableProgram") ? "" : ("#include \"" + target_name + "_export.h\"");
      std::string template_precompiled_header(TEMPLATE_PRECOMPILED_HEADER);
      template_precompiled_header = std::regex_replace(template_precompiled_header,std::regex("##BLOCK_TARGET_API_MACRO_IMPORT##"),target_api_macro_import);

      out_stream << template_precompiled_header;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generatePreCompiledSource(const std::string& output_directory) const
{
  bool result = false;

  boost::filesystem::path output_file_path(output_directory + "/stdafx.cpp");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_precompiled_source(TEMPLATE_PRECOMPILED_SOURCE);

      out_stream << template_precompiled_source;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    } 
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateTargetExport(const std::string& output_directory) const
{
  bool result = false;

  const std::string& target_name = getName();
  std::string target_name_upper_case(target_name);
  std::transform(target_name_upper_case.begin(),target_name_upper_case.end(),target_name_upper_case.begin(),::toupper);

  boost::filesystem::path output_file_path(output_directory + "/" + target_name + "_export.h");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_target_export(TEMPLATE_TARGET_EXPORT);
      template_target_export = std::regex_replace(template_target_export,std::regex("##BLOCK_TARGET_NAME_UPPER_CASE##"),target_name_upper_case);
      template_target_export = std::regex_replace(template_target_export,std::regex("##BLOCK_TARGET_NAME##"),target_name);

      out_stream << template_target_export;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateTargetHeader(const std::string& output_directory) const
{
  bool result = false;

  const std::string& target_name = getName();
  std::string target_name_upper_case(target_name);
  std::transform(target_name_upper_case.begin(),target_name_upper_case.end(),target_name_upper_case.begin(),::toupper);

  boost::filesystem::path output_file_path(output_directory + "/" + target_name + ".h");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_target_header(TEMPLATE_TARGET_HEADER);
      template_target_header = std::regex_replace(template_target_header,std::regex("##BLOCK_TARGET_NAME_UPPER_CASE##"),target_name_upper_case);
      template_target_header = std::regex_replace(template_target_header,std::regex("##BLOCK_TARGET_NAME##"),target_name);

      out_stream << template_target_header;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    } 
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateTargetSource(const std::string& output_directory) const
{
  bool result = false;

  const std::string& target_name = getName();

  boost::filesystem::path output_file_path(output_directory + "/" + target_name + ".cpp");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_target_source(TEMPLATE_TARGET_SOURCE);
      template_target_source = std::regex_replace(template_target_source,std::regex("##BLOCK_TARGET_NAME##"),target_name);

      out_stream << template_target_source;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    } 
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateClassPrivateHeader(const std::string& class_name, const std::string& output_directory) const
{
  bool result = false;

  std::string class_name_upper_case(class_name);
  std::transform(class_name_upper_case.begin(),class_name_upper_case.end(),class_name_upper_case.begin(),::toupper);

  boost::filesystem::path output_file_path(output_directory + "/" + class_name + "Private.h");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_class_private_header(TEMPLATE_CLASS_PRIVATE_HEADER);
      template_class_private_header = std::regex_replace(template_class_private_header,std::regex("##BLOCK_CLASS_NAME_UPPER_CASE##"),class_name_upper_case);
      template_class_private_header = std::regex_replace(template_class_private_header,std::regex("##BLOCK_CLASS_NAME##"),class_name);

      out_stream << template_class_private_header;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    } 
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateClassPrivateSource(const std::string& class_name, const std::string& output_directory) const
{
  bool result = false;

  boost::filesystem::path output_file_path(output_directory + "/" + class_name + "Private.cpp");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_class_private_source(TEMPLATE_CLASS_PRIVATE_SOURCE);
      template_class_private_source = std::regex_replace(template_class_private_source,std::regex("##BLOCK_CLASS_NAME##"),class_name);

      out_stream << template_class_private_source;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateClassHeader(const std::string& class_name,bool export_flag, const std::string& output_directory) const
{
  bool result = false;

  std::string class_name_upper_case(class_name);
  std::transform(class_name_upper_case.begin(),class_name_upper_case.end(),class_name_upper_case.begin(),::toupper);

  boost::filesystem::path output_file_path(output_directory + "/" + class_name + ".h");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_class_header(TEMPLATE_CLASS_HEADER);
      template_class_header = std::regex_replace(template_class_header,std::regex("\\s*##BLOCK_TARGET_API_MACRO##\\s*"),export_flag ? (" " + getName() + "_API ") : " ");
      template_class_header = std::regex_replace(template_class_header,std::regex("##BLOCK_CLASS_NAME_UPPER_CASE##"),class_name_upper_case);
      template_class_header = std::regex_replace(template_class_header,std::regex("##BLOCK_CLASS_NAME##"),class_name);

      out_stream << template_class_header;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    } 
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateClassSource(const std::string& class_name, const std::string& output_directory) const
{
  bool result = false;

  boost::filesystem::path output_file_path(output_directory + "/" + class_name + ".cpp");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_class_source(TEMPLATE_CLASS_SOURCE);
      template_class_source = std::regex_replace(template_class_source,std::regex("##BLOCK_CLASS_NAME##"),class_name);

      out_stream << template_class_source;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateEntryMethod(const std::string& output_directory) const
{
  bool result = false;

  boost::filesystem::path output_file_path(output_directory + "/main.cpp");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_entry_method(TEMPLATE_ENTRY_METHOD);

      out_stream << template_entry_method;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    } 
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generateCMakeConfiguration(const std::string& output_directory) const
{
  bool result = false;

  boost::filesystem::path output_file_path(output_directory + "/CMakeLists.txt");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_cmake_configuration(TEMPLATE_CMAKE_CONFIGURATION);
      if(getType() == "StaticLibrary")
      {
        template_cmake_configuration = std::regex_replace(template_cmake_configuration,std::regex("##BLOCK_TARGET_GENERATE_COMMAND##"),"generateStaticLibrary()#生成静态库");
      }
      else if(getType() == "DynamicLibrary")
      {
        template_cmake_configuration = std::regex_replace(template_cmake_configuration,std::regex("##BLOCK_TARGET_GENERATE_COMMAND##"),"generateDynamicLibrary()#生成动态库");
      }
      else if(getType() == "PluginLibrary")
      {
        template_cmake_configuration = std::regex_replace(template_cmake_configuration,std::regex("##BLOCK_TARGET_GENERATE_COMMAND##"),"generatePluginLibrary()#生成插件库");
      }
      else if(getType() == "ExecutableProgram")
      {
        template_cmake_configuration = std::regex_replace(template_cmake_configuration,std::regex("##BLOCK_TARGET_GENERATE_COMMAND##"),"generateExecutableProgram()#生成可执行程序");
      }
      else
      {
        template_cmake_configuration = std::regex_replace(template_cmake_configuration,std::regex("##BLOCK_TARGET_GENERATE_COMMAND##"),"message(FATAL_ERROR \"Unknown TargetType\")");
      }

      out_stream << template_cmake_configuration;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    } 
  }
  else
  {
  }

  return result;
}

bool CustomTarget::generate(const std::string& output_directory) const
{
  bool result = false;

  if(isValid())
  {
    const std::string& target_name = getName();
    const std::string& target_type = getType();
    const bool& target_enable_export = getEnableExport();
    const std::set<std::string>& target_public_class_list = getAllPublicClassName();
    const std::set<std::string>& target_private_class_list = getAllPrivateClassName();

    const std::string& target_directory = output_directory.empty() ? target_name : (output_directory + "/" + target_name);

    if(!boost::filesystem::exists(target_directory))
    {
      boost::filesystem::create_directories(target_directory);
    }

    if(boost::filesystem::exists(target_directory))
    {
      const std::string& target_public_directory = target_directory + "/public/" + target_name;
      const std::string& target_private_directory = target_directory + "/private";

      //预编译头
      generatePreCompiledHeader(target_private_directory);
      generatePreCompiledSource(target_private_directory);
      //类型特定文件
      if(target_type == "ExecutableProgram")
      {
        if(target_enable_export || !target_public_class_list .empty())
        {
          generateTargetExport(target_public_directory);
        }
        generateEntryMethod(target_private_directory);
      }
      else if(target_type == "PluginLibrary")
      {
        generateTargetExport(target_private_directory);
        generateTargetHeader(target_private_directory);
        generateTargetSource(target_private_directory);
      }
      else
      {
        generateTargetExport(target_public_directory);
        generateTargetHeader(target_public_directory);
        generateTargetSource(target_private_directory);
      }
      //公开类
      std::for_each(target_public_class_list.cbegin(),target_public_class_list.cend(),[&](const std::string& class_name_exist)
      {
        generateClassHeader(class_name_exist,true,target_public_directory);
        generateClassPrivateHeader(class_name_exist,target_private_directory);
        generateClassSource(class_name_exist,target_private_directory);
        generateClassPrivateSource(class_name_exist,target_private_directory);
      });
      //私有类
      std::for_each(target_private_class_list.cbegin(),target_private_class_list.cend(),[&](const std::string& class_name_exist)
      {
        generateClassHeader(class_name_exist,false,target_private_directory);
        generateClassPrivateHeader(class_name_exist,target_private_directory);
        generateClassSource(class_name_exist,target_private_directory);
        generateClassPrivateSource(class_name_exist,target_private_directory);
      });
      //CMake配置文件
      generateCMakeConfiguration(target_directory);
    }
    else
    {
    }
  }
  else
  {
  }

  return result;
}

