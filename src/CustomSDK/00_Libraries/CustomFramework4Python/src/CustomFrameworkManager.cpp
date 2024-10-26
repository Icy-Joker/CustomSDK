#include "stdafx.h"

#include <iostream>

#include <fmt/format.h>

#include <boost/filesystem.hpp>

#include <CommonFramework/DynamicLibrary.h>
#include <CommonFramework/AbstractCustomModule.h>
#include "CommonFramework/LogManager.h"
#include "CustomFramework4Python/CustomFrameworkManager.h"

CustomFrameworkManager::CustomFrameworkManager() :
  AbstractFrameworkManager()
{
}

CustomFrameworkManager::~CustomFrameworkManager()
{
}

CustomFrameworkManager* CustomFrameworkManager::instance()
{
  static CustomFrameworkManager instance;
  return &instance;
}

void CustomFrameworkManager::doLoadModules(const std::string& module_path)
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
      DWORD error_index = GetLastError(); std::error_code error_code(error_index,std::system_category()); std::string log_content = ; LOG_DEBUG("{}",error_code.message());
#else
      LOG_DEBUG("{}",dlerror());
#endif
    }
  }
}
