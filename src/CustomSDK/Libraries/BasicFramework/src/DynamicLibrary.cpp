#include "stdafx.h"

#include "BasicFramework/DynamicLibrary.h"

#include <functional>

DynamicLibrary::DynamicLibrary(const char* module_path)
{
  this->module_path = module_path;
}

DynamicLibrary::~DynamicLibrary()
{
}

FunctionPointer DynamicLibrary::resolve(const char* symbol_name)
{
  FARPROC method;
  if (module_handle)
  {
# ifdef WIN32
    method = GetProcAddress(module_handle, symbol_name);
# else
    method = dlsym(module_handle, symbol_name);
# endif
  }
  return (FunctionPointer)method;
}

void DynamicLibrary::setHandle(HMODULE module_handle)
{
  this->module_handle = module_handle;
}

void DynamicLibrary::setVersion(const char*)
{
}

const std::string& DynamicLibrary::getPath()
{
  return std::cref(module_path);
}

HMODULE DynamicLibrary::getHandle()
{
  return module_handle;
}
