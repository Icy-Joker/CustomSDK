#pragma once

#ifndef __CUSTOMFRAMEWORKMANAGER_H__
# define __CUSTOMFRAMEWORKMANAGER_H__

#include <BasicSupport/Singleton.h>
#include <BasicFramework/AbstractFrameworkManager.h>

extern "C"
{
  class CustomFramework_API CustomFrameworkManager : public AbstractFrameworkManager,public Singleton<CustomFrameworkManager>
  {
  public:
    CustomFrameworkManager(const CustomFrameworkManager&) = delete;
    CustomFrameworkManager& operator=(const CustomFrameworkManager&) = delete;
  private:
    CustomFrameworkManager();
    ~CustomFrameworkManager() override;
  protected:
    void doLoadModules(const char* module_path) override;
  private:
    friend class Singleton<CustomFrameworkManager>;
  };
}

#endif // !__CUSTOMFRAMEWORKMANAGER_H__
