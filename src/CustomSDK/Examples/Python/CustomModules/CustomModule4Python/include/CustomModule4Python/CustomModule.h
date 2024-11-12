#pragma once

#ifndef __CUSTOMMODULE_H__
# define __CUSTOMMODULE_H__

#include <BasicFramework/AbstractCustomModule.h>

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

  //CUSTOMMODULE_C_WRAPPER(CustomModule);
}

#endif // !__CUSTOMMODULE_H__
