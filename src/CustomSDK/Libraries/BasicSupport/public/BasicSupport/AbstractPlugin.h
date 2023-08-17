#pragma once

#define PLUGIN_EXPORT(PLUGIN_CLASS)															\
extern "C" SYMBOL_EXPORT  AbstractPlugin* getPlugin()						\
{																																\
	static PLUGIN_CLASS plugin;																		\
	return &plugin;																								\
}																																\

class AbstractPlugin
{
public:
  virtual ~AbstractPlugin(){};
public:
	virtual const char* getName() const = 0;///��ȡ�������
	virtual const char* getDescription() const = 0;///��ȡ�������
};
