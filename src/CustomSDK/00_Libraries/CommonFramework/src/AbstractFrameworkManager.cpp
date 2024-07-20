#include "stdafx.h"

#include "AbstractFrameworkManager.h"

#include <algorithm>

#include <fmt/format.h>

#include <boost/filesystem.hpp>

#include "CommonFramework/ConfigManager.h"
#include <CommonFramework/DynamicLibrary.h>
#include <CommonFramework/AbstractCustomModule.h>
#include <CommonFramework/LogManager.h>

AbstractFrameworkManager::AbstractFrameworkManager()
{
}

AbstractFrameworkManager::~AbstractFrameworkManager()
{
}

bool AbstractFrameworkManager::initializeWithConfig(const std::string& config_file_path)
{
  bool result = false;

  if(LogManager::instance()->initializeWithConfig(config_file_path))
  {
    if(ConfigManager::instance()->loadConfig(config_file_path))
    {
      LOG_INFO("Load Config[{}] Success.",config_file_path);

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
    else
    {
      LOG_ERROR("Load Config[{}] Failed.",config_file_path);
    }
  }

  return result;
}

void AbstractFrameworkManager::doLoadModules(const std::string& module_path)
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
    LOG_INFO("Load Module[{}] Success.",module_path);
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
      LOG_WARN("Load Module[{}] Failed.",module_path);
    }
    {
#ifdef WIN32
      DWORD error_index = GetLastError(); std::error_code error_code(error_index,std::system_category()); std::string log_content = error_code.message(); LOG_DEBUG(log_content.c_str());
#else
      LOG_DEBUG("{}",dlerror());
#endif
    }
  }
}
