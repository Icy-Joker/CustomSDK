#pragma once

#ifndef __ABSTRACTFRAMEWORKMANAGER_H__
# define __ABSTRACTFRAMEWORKMANAGER_H__

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

#endif // !__ABSTRACTFRAMEWORKMANAGER_H__
