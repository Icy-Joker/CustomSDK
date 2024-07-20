#pragma once

#ifndef DYNAMICLIBRARY_H
# define DYNAMICLIBRARY_H

#include <BasicSupport/CommonTypes.h>

#include <string>

#ifdef _POSIX_VERSION
# include <dlfcn.h>
# //静态链接库
# define STATIC_LIBRARY_PREFIX "lib"
# define STATIC_LIBRARY_SUFFIX
# define STATIC_LIBRARY_EXTENSION ".a"
# //共享动态库
# define SHARED_LIBRARY_PREFIX "lib"
# define SHARED_LIBRARY_SUFFIX
# ifdef __apple_build_version__
#  define SHARED_LIBRARY_EXTENSION ".dylib"
# else
#  define SHARED_LIBRARY_EXTENSION ".so"
# endif
# //模块库
# define MODULE_LIBRARY_PREFIX "lib"
# define MODULE_LIBRARY_SUFFIX
# define MODULE_LIBRARY_EXTENSION ".so"
# //Python模块库
# define PYTHON_MODULE_LIBRARY_PREFIX "_"
# define PYTHON_MODULE_LIBRARY_SUFFIX
# define PYTHON_MODULE_LIBRARY_EXTENSION ".so"
#
typedef void* HMODULE;
typedef void* FARPROC;
#
#else
# include <windows.h>

# //静态链接库
# define STATIC_LIBRARY_PREFIX
# define STATIC_LIBRARY_SUFFIX "-vc" _CRT_VER_NAME "-" _PLATFORM _DEBUG_FLAG
# define STATIC_LIBRARY_EXTENSION ".lib"
# //共享动态库
# define SHARED_LIBRARY_PREFIX
# define SHARED_LIBRARY_SUFFIX "-vc" _CRT_VER_NAME "-" _PLATFORM _DEBUG_FLAG
# define SHARED_LIBRARY_EXTENSION ".dll"
# //模块库
# define MODULE_LIBRARY_PREFIX
# define MODULE_LIBRARY_SUFFIX "-vc" _CRT_VER_NAME "-" _PLATFORM _DEBUG_FLAG
# define MODULE_LIBRARY_EXTENSION ".dll"
# //Python模块库
# define PYTHON_MODULE_LIBRARY_PREFIX "_"
# define PYTHON_MODULE_LIBRARY_SUFFIX
# define PYTHON_MODULE_LIBRARY_EXTENSION ".pyd"
#
#endif

typedef int*(* FunctionPointer)();

class BasicFramework_API DynamicLibrary
{
public:
  DynamicLibrary(const char*);
  ~DynamicLibrary();
public:
  FunctionPointer resolve(const char*);
public:
  void setHandle(HMODULE);
  void setVersion(const char*);
  const std::string& getPath();
  HMODULE getHandle();
private:
  HMODULE module_handle;
  std::string module_path;
  std::string module_version;
};

class DynamicLibrary;
CLASS_PTR_DECLARE(DynamicLibrary);

#endif // !DYNAMICLIBRARY_H
