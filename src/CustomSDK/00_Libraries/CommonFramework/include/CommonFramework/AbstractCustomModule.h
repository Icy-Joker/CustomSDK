#pragma once

#ifndef ABSTRACTCUSTOMMODULE_H
# define ABSTRACTCUSTOMMODULE_H

extern "C"
{
  class CommonFramework_API AbstractCustomModule
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
  SYMBOL_EXPORT_DECLARE AbstractCustomModule* CUSTOM_MODULE_NAME##_create() \
  {\
    return new CUSTOM_MODULE_NAME(); \
  }\
  SYMBOL_EXPORT_DECLARE void CUSTOM_MODULE_NAME##_destroy(AbstractCustomModule* ptr) \
  {\
    delete (CUSTOM_MODULE_NAME*)ptr; \
  }\
}

typedef AbstractCustomModule* (* Function_create)();
typedef void (* Function_destroy)(AbstractCustomModule*);

#endif//!ABSTRACTCUSTOMMODULE_H
