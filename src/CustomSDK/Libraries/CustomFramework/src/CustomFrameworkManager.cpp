#include "stdafx.h"

#include "CustomFrameworkManager.h"

CustomFrameworkManager::CustomFrameworkManager():
  AbstractFrameworkManager()
{
}

CustomFrameworkManager::~CustomFrameworkManager()
{
}

CustomFrameworkManager* CustomFrameworkManager::getInstance()
{
  static CustomFrameworkManager instance;
  return &instance;
}

void CustomFrameworkManager::doLoadModules(const char* module_path)
{
  AbstractFrameworkManager::doLoadModules(module_path);
}
