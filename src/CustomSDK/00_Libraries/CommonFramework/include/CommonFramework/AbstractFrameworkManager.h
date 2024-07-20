#pragma once

#ifndef ABSTRACTFRAMEWORKMANAGER_H
# define ABSTRACTFRAMEWORKMANAGER_H

#include <string>

extern "C"
{
  class CommonFramework_API AbstractFrameworkManager
  {
  public:
    AbstractFrameworkManager();
    virtual ~AbstractFrameworkManager() = 0;
  public:
    bool initializeWithConfig(const std::string& config_path);
  protected:
    virtual void doLoadModules(const std::string& module_path);
  };
}

#endif//!ABSTRACTFRAMEWORKMANAGER_H
