#pragma once

#ifndef ABSTRACTCUSTOMMODULE_H
# define ABSTRACTCUSTOMMODULE_H

extern "C"
{
  class BasicFramework_API AbstractCustomModule
  {
  public:
    explicit AbstractCustomModule();
    virtual ~AbstractCustomModule() = 0;
  public:
    virtual void doSayHello() = 0;
  };
}

#define CUSTOMMODULE_C_WRAPPER(CUSTOM_MODULE_NAME)  \
extern "C"\
{\
  SYMBOL_EXPORT_DECLARE void* CUSTOM_MODULE_NAME##_create() \
  {\
    return new CUSTOM_MODULE_NAME(); \
  }\
  SYMBOL_EXPORT_DECLARE void CUSTOM_MODULE_NAME##_destroy(void* ptr) \
  {\
    delete (CUSTOM_MODULE_NAME*)ptr; \
  }\
}

typedef void* (* Function_create)();
typedef void (* Function_destroy)(void*);

#endif//!ABSTRACTCUSTOMMODULE_H
