#pragma once

#ifndef __MODULEMANAGER_H__
# define __MODULEMANAGER_H__

class ModuleManager
{
  enum ModuleType
  {
    Module_None,
    Module_CPlusPlus = Module_None,
    Module_CSharp,
    Module_Java,
    Module_Python,
    Module_Unknown = 0xff
  };
public:
  ModuleManager();
  ~ModuleManager();
public:
  void loadModule();
public:
  ModuleType module_type;
};

#endif // !__MODULEMANAGER_H__
