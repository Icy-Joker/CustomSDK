#pragma once

#include <BasicSupport/Singleton.h>
#include <BasicSupport/DynamicLibrary.h>

#include <vector>

class BasicSupport_API DynamicLibraryManager : public Singleton<DynamicLibraryManager>
{
	SINGLETON_DECLARE(DynamicLibraryManager)
public:
	DynamicLibraryPtr load(const char*);
	void unload(const char*);
	void unload(HMODULE);
private:
	void initialize();
	void finalize();
private:
	std::vector<DynamicLibraryPtr> vector_dynamic_libraries;
};
