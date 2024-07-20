#include "stdafx.h"

#include "CommonFramework/ConfigManager.h"
#include "ConfigManagerPrivate.h"

#include "CommonFramework/DynamicLibrary.h"

ConfigManager::ConfigManager():
  Singleton<ConfigManager>(),
  private_ptr(new ConfigManagerPrivate())
{
}

ConfigManager::~ConfigManager()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

bool ConfigManager::loadConfig(const std::string& file_path)
{
  return private_ptr->loadConfig(file_path);
}

std::vector<std::string> ConfigManager::getPreloadModules() const
{
  return private_ptr->getPreloadModules();
}

std::vector<std::string> ConfigManager::getModules() const
{
  return private_ptr->getModules();
}

std::vector<std::pair<std::string,std::string>> ConfigManager::getExtendConfigs()
{
  return private_ptr->getExtendConfigs();
}
