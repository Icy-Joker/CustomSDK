#include "stdafx.h"

#include "CustomProject.h"
#include "CustomProjectPrivate.h"

#include "template_project.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>

#include <cassert>
#include <regex>
#include <iostream>

CustomProject::CustomProject(const std::string& project_name):
  _p(new CustomProjectPrivate())
{
  assert(!project_name.empty());

  setName(project_name);
}

CustomProject::~CustomProject()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}

void CustomProject::setName(const std::string& project_name)
{
  _p->project_name = project_name;
}

void CustomProject::setDescription(const std::string& project_description)
{
  _p->project_description = project_description;
}

void CustomProject::setVersion(const std::string& project_version)
{
  _p->project_version = project_version;
}

void CustomProject::appendChildFolder(const std::string& child_folder)
{
  _p->project_child_folder_list.insert(child_folder);
}

void CustomProject::removeChildFolder(const std::string& child_folder)
{
  _p->project_child_folder_list.erase(child_folder);
}

const std::string& CustomProject::getName() const
{
  return _p->project_name;
}

const std::string& CustomProject::getDescription() const
{
  return _p->project_description.empty() ? _p->project_name : _p->project_description;
}

const std::string& CustomProject::getVersion() const
{
  return _p->project_version;
}

const std::set<std::string>& CustomProject::getAllChildFolder() const
{
  return _p->project_child_folder_list;
}

bool CustomProject::generateVersionInfoResource(const std::string& output_directory) const
{
  bool result = false;

  boost::filesystem::path output_file_path(output_directory + "/VersionInfo.rc.in");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_project_version_info_resource(TEMPLATE_PROJECT_VERSION_INFO_RESOURCE);

      out_stream << template_project_version_info_resource;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomProject::generateCMakeModule(const std::string& output_directory) const
{
  bool result = false;

  boost::filesystem::path output_file_path(output_directory + "/module.cmake");

  if(!boost::filesystem::exists(output_directory))
  {
    boost::filesystem::create_directories(output_directory);
  }

  if(boost::filesystem::exists(output_directory))
  {
    boost::filesystem::ofstream out_stream(output_file_path);
    if(out_stream.is_open())
    {
      std::string template_project_cmake_module(TEMPLATE_PROJECT_CMAKE_MODULE);

      out_stream << template_project_cmake_module;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomProject::generateGroupCMakeConfiguration(const std::string& output_directory) const
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
      std::string template_project_target_group_cmake_configuration(TEMPLATE_PROJECT_TARGET_GROUP_CMAKE_CONFIGURATION);

      out_stream << template_project_target_group_cmake_configuration;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomProject::generateCMakeConfiguration(const std::string& output_directory) const
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
      std::string template_projcet_cmake_configuration(TEMPLATE_PROJECT_CMAKE_CONFIGURATION);

      out_stream << template_projcet_cmake_configuration;

      std::cout << "generated:" << boost::filesystem::absolute(output_file_path) << std::endl;
    }
  }
  else
  {
  }

  return result;
}

bool CustomProject::generate(const std::string& output_directory) const
{
  bool result = false;

  const std::string& project_name = getName();
  const std::string& project_description = getDescription();
  const std::string& project_version = getVersion();
  const std::set<std::string>& project_child_folder_list = getAllChildFolder();
  //项目根目录
  const std::string project_output_directory = output_directory.empty() ? project_name : (output_directory + "/" + project_name);

  if(!boost::filesystem::exists(project_output_directory))
  {
    boost::filesystem::create_directories(project_output_directory);
  }

  if(boost::filesystem::exists(project_output_directory))
  {
    const std::string project_source_root_directory = project_output_directory + "/src/" + project_name;
    const std::string project_script_directory = project_output_directory + "/src/scripts";
    //
    generateVersionInfoResource(project_source_root_directory);
    //
    generateCMakeModule(project_source_root_directory);
    //
    std::for_each(project_child_folder_list.cbegin(),project_child_folder_list.cend(),[&](const std::string& child_folder)
    {
      generateGroupCMakeConfiguration(project_source_root_directory + "/" + child_folder);
    });
    //
    generateCMakeConfiguration(project_source_root_directory);
  }
  else
  {
  }

  return result;
}
