#pragma once

#include <BasicSupport/Singleton.h>
#include <BasicSupport/DynamicLibraryManager.h>

#include <vector>
#include <functional>

#include <iostream>

template<class PLUGIN_DATA_TYPE>
class PluginManager :public Singleton<PluginManager<PLUGIN_DATA_TYPE>>
{
	SINGLETON_DECLARE(PluginManager<PLUGIN_DATA_TYPE>)
public:
	void initialize()
	{
		std::cout << "PluginManager initialize..."<<std::endl;
	}
	void finalize()
	{
		std::cout << "PluginManager finalize..."<< std::endl;
	}
public:
	PLUGIN_DATA_TYPE* loadPlugin(const char* plugin_path)
	{
		PLUGIN_DATA_TYPE* plugin = nullptr;
		if (DynamicLibraryPtr library = DynamicLibraryManager::instance()->load(plugin_path))
		{
			if (FUNCTION_EXPORT method= library->resolve("getPlugin"))
			{
				if (plugin = (PLUGIN_DATA_TYPE*)method())
				{
					vector_plugins.push_back(plugin);
				}
			}
		}
		return plugin;
	}

	const std::vector<PLUGIN_DATA_TYPE*>& getAllPlugins()
	{
		return std::cref(vector_plugins);
	}
private:
	std::vector<PLUGIN_DATA_TYPE*> vector_plugins;
};