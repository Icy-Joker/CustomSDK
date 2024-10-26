#include "stdafx.h"

#include "CustomFramework4Python/CustomFrameworkManager.h"

#include <BasicFramework/DynamicLibrary.h>
#include <BasicFramework/AbstractCustomModule.h>
#include "BasicFramework/LogManager.h"

#include <boost/filesystem.hpp>

#include <iostream>

CustomFrameworkManager::CustomFrameworkManager():
  AbstractFrameworkManager()
{
}

CustomFrameworkManager::~CustomFrameworkManager()
{
}

CustomFrameworkManager* CustomFrameworkManager::getInstance()
{
  static CustomFrameworkManager instance;
  return &instance;
}

void CustomFrameworkManager::doLoadModules(const char* module_path)
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
