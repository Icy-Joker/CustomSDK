#pragma once

#include <BasicSupport/CommonTypes.h>

#include <string>

#ifndef WIN32
typedef void* HMODULE;
typedef void* FARPROC;
#endif

typedef int*(*FUNCTION_EXPORT)();

class BasicSupport_API DynamicLibrary
{
public:
	DynamicLibrary(const char*);
	~DynamicLibrary();
public:
	FUNCTION_EXPORT resolve(const char*);
public:
	void setHandle(HMODULE);
	void setVersion(const char*);
	const std::string& getPath();
	HMODULE getHandle();
private:
	HMODULE     library_module_handle;
	std::string library_path;
	std::string library_version;
};

class DynamicLibrary;
CLASS_PTR_DECLARE(DynamicLibrary);
