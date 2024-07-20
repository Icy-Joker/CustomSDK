#pragma once

#ifndef DYNAMICLIBRARY_H
# define DYNAMICLIBRARY_H

#include <string>

#include <boost/predef.h>

#include <BasicSupport/CommonTypes.h>

#if defined(BOOST_OS_LINUX_AVAILABLE) || defined(BOOST_OS_MACOS_AVAILABLE)
# include <dlfcn.h>
# //静态链接库
# define STATIC_LIBRARY_PREFIX "lib"
# define STATIC_LIBRARY_SUFFIX
# define STATIC_LIBRARY_EXTENSION ".a"
# //共享动态库
# define SHARED_LIBRARY_PREFIX "lib"
# define SHARED_LIBRARY_SUFFIX
# if defined(BOOST_OS_MACOS_AVAILABLE)
#  define SHARED_LIBRARY_EXTENSION ".so"
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

class CommonFramework_API DynamicLibrary
{
public:
  explicit DynamicLibrary(const std::string&);
  ~DynamicLibrary();
public:
  FunctionPointer resolve(const std::string&);
public:
  HMODULE getHandle();
  void setHandle(HMODULE);
  void setVersion(const std::string&);
  const std::string& getPath();
private:
  HMODULE module_handle{};
  std::string module_path;
  std::string module_version;
};

class DynamicLibrary;
CLASS_PTR_DECLARE(DynamicLibrary);

#endif//!DYNAMICLIBRARY_H
