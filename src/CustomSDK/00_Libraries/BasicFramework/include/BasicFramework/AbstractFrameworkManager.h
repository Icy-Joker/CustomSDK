#pragma once

#ifndef ABSTRACTFRAMEWORKMANAGER_H
# define ABSTRACTFRAMEWORKMANAGER_H

extern "C"
{
  class BasicFramework_API AbstractFrameworkManager
  {
  public:
    AbstractFrameworkManager();
    virtual ~AbstractFrameworkManager() = 0;
  public:
    bool initializeWithConfig(const char* config_path);
  protected:
    virtual void doLoadModules(const char* module_path);
  };
}

#endif//!ABSTRACTFRAMEWORKMANAGER_H
