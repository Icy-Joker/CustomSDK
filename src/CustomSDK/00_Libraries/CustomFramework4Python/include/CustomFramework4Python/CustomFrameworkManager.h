#pragma once

#ifndef CUSTOMFRAMEWORKMANAGER_H
# define __CUSTOMFRAMEWORKMANAGER_H__

#include "CommonFramework/AbstractFrameworkManager.h"

extern "C"
{
  class CustomFramework_API CustomFrameworkManager : public AbstractFrameworkManager
  {
  private:
    CustomFrameworkManager();
    ~CustomFrameworkManager() override;
  public:
    static CustomFrameworkManager* instance();
  protected:
    void doLoadModules(const std::string& module_path) override;
  };
}

#endif//!__CUSTOMFRAMEWORKMANAGER_H__
