#pragma once

#ifndef CUSTOMMODULE_H
# define CUSTOMMODULE_H

#include <CommonFramework/AbstractCustomModule.h>

extern "C"
{
  class CustomModule_API CustomModule : public AbstractCustomModule
  {
  public:
    CustomModule();
    ~CustomModule();
  public:
    void doSayHello() override;
  };
}

#endif//!CUSTOMMODULE_H
