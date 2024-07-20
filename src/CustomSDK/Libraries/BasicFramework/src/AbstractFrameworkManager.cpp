#include "stdafx.h"

#include "AbstractFrameworkManager.h"

#include "BasicFramework/ConfigManager.h"
#include <BasicFramework/DynamicLibrary.h>
#include <BasicFramework/AbstractCustomModule.h>
#include <BasicFramework/LogManager.h>

#include <boost/filesystem.hpp>

#include <iostream>
#include <algorithm>

AbstractFrameworkManager::AbstractFrameworkManager()
{
}

AbstractFrameworkManager::~AbstractFrameworkManager()
{
}

bool AbstractFrameworkManager::initializeWithConfig(const char* config_path)
{
  bool result = false;

  if(LogManager::getInstance()->initializeWithConfig(config_path))
  {
    if(ConfigManager::getInstance()->loadConfig(config_path))
    {
      {
        LOG_INFO("Loading Preload Modules");
        const std::vector<std::string>& modules = ConfigManager::getInstance()->getPreloadModules();
        std::for_each(modules.begin(),modules.end(),[&](const std::string& module_path)
        {
          AbstractFrameworkManager::doLoadModules(module_path.c_str());
        });
      }
      {
        LOG_INFO("Loading Custom Modules");
        const std::vector<std::string>& modules = ConfigManager::getInstance()->getModules();
        std::for_each(modules.begin(),modules.end(),[&](const std::string& module_path)
        {
          doLoadModules(module_path.c_str());
        });
      }
      {
        //ConfigManager::getInstance()->getExtendConfigs();
      }

      result = true;
    }
  }

  return result;
}

void AbstractFrameworkManager::doLoadModules(const char* module_path)
{
#ifdef _POSIX_VERSION
  if(HMODULE handle_module = dlopen(boost::filesystem::absolute(module_path).string().c_str(),RTLD_LAZY))
  {
    Function_create CustomModule_create = (Function_create)(FARPROC)dlsym(handle_module,"CustomModule_create");
    Function_destroy CustomModule_destroy = (Function_destroy)(FARPROC)dlsym(handle_module,"CustomModule_destroy");
#else
  if(HMODULE handle_module = LoadLibraryA(boost::filesystem::absolute(module_path).string().c_str()))
  {
    Function_create CustomModule_create = (Function_create)(FARPROC)GetProcAddress(handle_module,"CustomModule_create");
    Function_destroy CustomModule_destroy = (Function_destroy)(FARPROC)GetProcAddress(handle_module,"CustomModule_destroy");
#endif
    std::string log_content = "Loading Module[" + std::string(module_path) + "]";
    LOG_INFO(log_content.c_str());
  }
  else
  {
    {
#ifdef WIN32
      //std::string log_content = GetLastError();
#else
      std::string log_content = dlerror();
      LOG_DEBUG(log_content.c_str());
#endif
    }
    {
      std::string log_content = "Load Module[" + std::string(module_path) + "] Failed";
      LOG_WARN(log_content.c_str());
    }
  }
}
