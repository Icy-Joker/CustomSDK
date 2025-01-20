#pragma once

#ifndef CUSTOMFRAMEWORKMANAGER_H
# define CUSTOMFRAMEWORKMANAGER_H

#include <BasicSupport/Singleton.h>
#include <CommonFramework/AbstractFrameworkManager.h>

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
    void doLoadModules(const std::string& module_path) override;
  private:
    friend class Singleton<CustomFrameworkManager>;
  };
}

#endif//!CUSTOMFRAMEWORKMANAGER_H
