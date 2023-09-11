#include "stdafx.h"
#include "DynamicLibraryManager.h"

#include <iostream>
#include <algorithm>
#include <functional>

DynamicLibraryPtr DynamicLibraryManager::load(const char* library_path)
{
	DynamicLibraryPtr library = nullptr;
#ifdef _WINDOWS
	if (HMODULE handle_module = LoadLibrary(library_path))
#else
	if (HMODULE handle_module = dlopen(library_path,RTLD_LAZY))
#endif
	{
		library = boost::make_shared<DynamicLibrary>(library_path);
		library->setHandle(handle_module);
		vector_dynamic_libraries.push_back(library);
	}
	return library;
}

void DynamicLibraryManager::unload(const char * library_path) //throw()
{
	auto it_found_vector_dynamic_libraries = std::find_if(std::begin(vector_dynamic_libraries), std::end(vector_dynamic_libraries), [&library_path](DynamicLibraryPtr library_existed)
	{
		return library_existed->getPath() == library_path;
	});
	if (it_found_vector_dynamic_libraries != std::end(vector_dynamic_libraries))
	{
		if (DynamicLibraryPtr library=*it_found_vector_dynamic_libraries)
		{
			try
			{
				unload(library->getHandle());
			} catch (const char* e)
			{
				throw e;
			}
		}
	}
}

void DynamicLibraryManager::unload(HMODULE handle_module) //throw()
{
	if (handle_module)
	{
#ifdef _WINDOWS
		if (!FreeLibrary(handle_module))
#else
		if (dlclose(handle_module) != 0)
#endif
		{
			throw "error";
		}
	}
}

void DynamicLibraryManager::initialize()
{
}

void DynamicLibraryManager::finalize()
{
	for (auto it_found_vector_dynamic_libraries = std::begin(vector_dynamic_libraries);it_found_vector_dynamic_libraries!=std::end(vector_dynamic_libraries);++it_found_vector_dynamic_libraries)
	{
		if (DynamicLibraryPtr library=*it_found_vector_dynamic_libraries)
		{
			try
			{
				//unload(library->getHandle());
			} catch (const char* e)
			{
				std::cout << e << std::endl;
			}
		}
	}
}
