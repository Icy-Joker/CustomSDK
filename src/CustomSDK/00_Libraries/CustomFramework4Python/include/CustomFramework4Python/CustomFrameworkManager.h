#pragma once

#ifndef CUSTOMFRAMEWORKMANAGER_H
# define __CUSTOMFRAMEWORKMANAGER_H__

#include "BasicFramework/AbstractFrameworkManager.h"

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
    void doLoadModules(const char* module_path) override;
  };
}

#endif//!__CUSTOMFRAMEWORKMANAGER_H__
