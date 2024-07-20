#include "stdafx.h"

#include <functional>

#include "CommonFramework/DynamicLibrary.h"

DynamicLibrary::DynamicLibrary(const std::string& module_path) :
  module_handle(nullptr)
{
  this->module_path = module_path;
}

DynamicLibrary::~DynamicLibrary()
{
}

FunctionPointer DynamicLibrary::resolve(const std::string& symbol_name)
{
  FARPROC method;
  if(module_handle)
  {
# ifdef WIN32
    method = GetProcAddress(module_handle,symbol_name);
# else
    method = dlsym(module_handle,symbol_name.c_str());
# endif
  }
  return (FunctionPointer)method;
}

HMODULE DynamicLibrary::getHandle()
{
  return module_handle;
}

void DynamicLibrary::setHandle(HMODULE module_handle)
{
  this->module_handle = module_handle;
}

void DynamicLibrary::setVersion(const std::string&)
{
}

const std::string& DynamicLibrary::getPath()
{
  return std::cref(module_path);
}
