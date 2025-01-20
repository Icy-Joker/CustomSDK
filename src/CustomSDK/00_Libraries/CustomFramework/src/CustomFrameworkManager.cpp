#include "stdafx.h"

#include "CustomFrameworkManager.h"

CustomFrameworkManager::CustomFrameworkManager() :
  AbstractFrameworkManager()
{
}

CustomFrameworkManager::~CustomFrameworkManager()
{
}

void CustomFrameworkManager::doLoadModules(const std::string& module_path)
{
  AbstractFrameworkManager::doLoadModules(module_path);
}
