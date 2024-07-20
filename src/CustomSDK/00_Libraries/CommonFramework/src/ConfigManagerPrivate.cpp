#include "stdafx.h"

#include "ConfigManagerPrivate.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "CommonFramework/DynamicLibrary.h"

ConfigManagerPrivate::ConfigManagerPrivate()
{
}

ConfigManagerPrivate::~ConfigManagerPrivate()
{
}

bool ConfigManagerPrivate::loadConfig(const std::string& file_path)
{
  bool result = false;

  boost::filesystem::path path = boost::filesystem::absolute(file_path).generic_path().make_preferred();
  if(boost::filesystem::is_regular_file(path) && path.extension().string() == ".xml")
  {
    if(doc.load_file(path.string().c_str()).status == pugi::xml_parse_status::status_ok)
    {
      result = true;
    }
  }

  return result;
}

std::string getSuitableModulePath(const std::string& module_name,const std::string& module_directory)
{
  const std::string module_real_name = std::string(SHARED_LIBRARY_PREFIX) + std::string(module_name) + std::string(SHARED_LIBRARY_SUFFIX SHARED_LIBRARY_EXTENSION);
  boost::filesystem::path module_path = boost::filesystem::path(module_directory).append(module_real_name);

  return module_path.generic_path().make_preferred().string();
}

std::string getSuitableModulePath4CSharp(const std::string& module_name,const std::string& module_directory)
{
  const std::string module_real_name = std::string(module_name) + std::string(SHARED_LIBRARY_EXTENSION);
  boost::filesystem::path module_path = boost::filesystem::path(module_directory).append(module_real_name);

  return module_path.generic_path().make_preferred().string();
}

std::string getSuitableModulePath4Java(const std::string& module_name,const std::string& module_directory)
{
  const std::string module_real_name = std::string(module_name) + std::string(".jar");
  boost::filesystem::path module_path = boost::filesystem::path(module_directory).append(module_real_name);

  return module_path.generic_path().make_preferred().string();
}

std::string getSuitableModulePath4Python(const std::string& module_name,const std::string& module_directory)
{
  const std::string module_real_name = std::string(PYTHON_MODULE_LIBRARY_PREFIX) + std::string(module_name) + std::string(PYTHON_MODULE_LIBRARY_EXTENSION);
  boost::filesystem::path module_path = boost::filesystem::path(module_directory).append(module_real_name);

  return module_path.generic_path().make_preferred().string();
}

std::vector<std::string> ConfigManagerPrivate::getPreloadModules() const
{
  std::vector<std::string> preload_modules;

  for(auto& xpath_node_module : doc.select_nodes("Root/PreloadModules/Module"))
  {
    if(xpath_node_module.node().attribute("enabled").as_bool())
    {
      const std::string module_name = xpath_node_module.node().attribute("name").as_string();
      const std::string module_directory = xpath_node_module.node().attribute("directory").as_string();

      std::string module_path = getSuitableModulePath(module_name,module_directory);
      if(!module_path.empty())
      {
        preload_modules.push_back(module_path);
      }
    }
  }

  return preload_modules;
}

std::vector<std::string> ConfigManagerPrivate::getModules() const
{
  std::vector<std::string> modules;

  if(pugi::xml_node node_modules = doc.select_node("Root/Modules").node())
  {
    const std::string attribute_module_type = node_modules.attribute("Language").as_string("CPlusPlus");
    for(auto& xpath_node_module : node_modules.select_nodes("Module"))
    {
      if(xpath_node_module.node().attribute("enabled").as_bool())
      {
        const std::string module_name = xpath_node_module.node().attribute("name").as_string();
        const std::string module_directory = xpath_node_module.node().attribute("directory").as_string();

        std::string module_path;
        if(attribute_module_type == "CPlusPlus")
        {
          module_path = getSuitableModulePath(module_name,module_directory);
        }
        else if(attribute_module_type == "CSharp")
        {
          module_path = getSuitableModulePath4CSharp(module_name,module_directory);
        }
        else if(attribute_module_type == "Java")
        {
          module_path = getSuitableModulePath4Java(module_name,module_directory);
        }
        else if(attribute_module_type == "Python")
        {
          module_path = getSuitableModulePath4Python(module_name,module_directory);
        }
        if(!module_path.empty())
        {
          modules.push_back(module_path);
        }
      }
    }
  }

  return modules;
}

std::vector<std::pair<std::string,std::string>> ConfigManagerPrivate::getExtendConfigs()
{
  std::vector<std::pair<std::string,std::string>> extend_configs;

  for(auto& xpath_node_module : doc.select_nodes("Root/ExtendConfigs/ExtendConfig"))
  {
    std::pair<std::string,std::string> config;
    config.first = xpath_node_module.node().attribute("key").as_string();
    config.second = xpath_node_module.node().attribute("value").as_string();

    extend_configs.push_back(config);
  }

  return extend_configs;
}
