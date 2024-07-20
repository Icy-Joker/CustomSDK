#include "stdafx.h"

#include "AbstractFrameworkManager.h"

#include "BasicFramework/ConfigManager.h"
#include <BasicFramework/DynamicLibrary.h>
#include <BasicFramework/AbstractCustomModule.h>
#include <BasicFramework/LogManager.h>

#include <boost/filesystem.hpp>

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

  if(LogManager::instance()->initializeWithConfig(config_path))
  {
    if(ConfigManager::instance()->loadConfig(config_path))
    {
      {
        LOG_INFO("Loading Preload Modules...");
        const std::vector<std::string>& modules = ConfigManager::instance()->getPreloadModules();
        std::for_each(modules.begin(),modules.end(),[&](const std::string& module_path)
        {
          AbstractFrameworkManager::doLoadModules(module_path.c_str());
        });
      }
      {
        LOG_INFO("Loading Custom Modules...");
        const std::vector<std::string>& modules = ConfigManager::instance()->getModules();
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
    Function_destroy CustomModule_destroy = (Function_destroy)(FARPROC)dlsym(handle_module,"CustomModule_create");
#else
  if(HMODULE handle_module = LoadLibraryA(boost::filesystem::absolute(module_path).string().c_str()))
  {
    Function_create CustomModule_create = (Function_create)(FARPROC)GetProcAddress(handle_module,"CustomModule_create");
    Function_destroy CustomModule_destroy = (Function_destroy)(FARPROC)GetProcAddress(handle_module,"CustomModule_destroy");
#endif
    std::string log_content = "Load Module[" + std::string(module_path) + "] Success.";
    LOG_INFO(log_content.c_str());
    if(CustomModule_create && CustomModule_destroy)
    {
      if(AbstractCustomModule* abstract_custom_module = CustomModule_create())
      {
        abstract_custom_module->doSayHello();

        CustomModule_destroy(abstract_custom_module);
      }
    }
  }
  else
  {
    {
      std::string log_content = "Load Module[" + std::string(module_path) + "] Failed.";
      LOG_WARN(log_content.c_str());
    }
    {
#ifdef WIN32
      DWORD error_index = GetLastError();
      std::error_code error_code(error_index,std::system_category());
      std::string log_content = error_code.message();
      LOG_DEBUG(log_content.c_str());
#else
      std::string log_content = dlerror(); LOG_DEBUG(log_content.c_str());
#endif
    }
  }
}
