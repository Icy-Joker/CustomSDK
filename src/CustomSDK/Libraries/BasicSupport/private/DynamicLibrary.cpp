#include "stdafx.h"
#include "DynamicLibrary.h"

#include <algorithm>
#include <functional>

DynamicLibrary::DynamicLibrary(const char* path)
{
	this->library_path=path;
}


DynamicLibrary::~DynamicLibrary()
{
}

FUNCTION_EXPORT DynamicLibrary::resolve(const char * symbol_name)
{
	FARPROC method;
	if (library_module_handle)
	{
# ifdef WIN32
		method = GetProcAddress(library_module_handle, symbol_name);
# else
		method = dlsym(library_module_handle, symbol_name);
# endif
	}
	return (FUNCTION_EXPORT)method;
}

void DynamicLibrary::setHandle(HMODULE handle)
{
	this->library_module_handle = handle;
}

void DynamicLibrary::setVersion(const char *)
{
}

const std::string & DynamicLibrary::getPath()
{
	return std::cref(library_path);
}

HMODULE DynamicLibrary::getHandle()
{
	return library_module_handle;
}
