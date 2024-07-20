#include "stdafx.h"

#include "ConfigManager.h"
#include "ConfigManagerPrivate.h"

#include "BasicFramework/DynamicLibrary.h"
#include "BasicFramework/LogManager.h"

#include <fstream>
#include <iostream>

#include <pugixml.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

ConfigManager::ConfigManager():
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

ConfigManager* ConfigManager::getInstance()
{
  static ConfigManager instance;
  return &instance;
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
