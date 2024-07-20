#include "stdafx.h"

#include <functional>

#include "CommonFramework/SharedLibrary.h"

SharedLibrary::SharedLibrary(const std::string& module_path):
  module_handle(nullptr)
{
  this->module_path = module_path;
}

SharedLibrary::~SharedLibrary()
{
}

FunctionPointer SharedLibrary::resolve(const std::string& symbol_name)
{
  FARPROC method;
  if(module_handle)
  {
#ifdef WIN32
    method = GetProcAddress(module_handle, symbol_name.c_str());
#else
    method = dlsym(module_handle, symbol_name.c_str());
#endif
  }
  return (FunctionPointer)method;
}

HMODULE SharedLibrary::getHandle()
{
  return module_handle;
}

void SharedLibrary::setHandle(HMODULE module_handle)
{
  this->module_handle = module_handle;
}

void SharedLibrary::setVersion(const std::string&)
{
}

const std::string& SharedLibrary::getPath()
{
  return std::cref(module_path);
}
