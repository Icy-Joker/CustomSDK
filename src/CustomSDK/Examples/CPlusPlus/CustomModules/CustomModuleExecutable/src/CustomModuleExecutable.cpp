#include "stdafx.h"

#include "CustomModuleExecutable.h"

#include <CustomModule/CustomModule.h>

CustomModuleExecutable::CustomModuleExecutable()
{
}

CustomModuleExecutable::~CustomModuleExecutable()
{
}

void CustomModuleExecutable::doSomething()
{
  CustomModule custom_module;
  custom_module.doSayHello();
}
