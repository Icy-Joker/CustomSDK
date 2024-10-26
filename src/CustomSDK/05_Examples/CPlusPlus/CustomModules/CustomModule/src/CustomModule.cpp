#include "stdafx.h"

#include <iostream>

#include "CustomModule/CustomModule.h"

CustomModule::CustomModule() :
  AbstractCustomModule()
{
}

CustomModule::~CustomModule()
{
}

void CustomModule::doSayHello()
{
  std::cout << "[CPlusPlus]:CustomModule::Hello World!" << std::endl;
}

CUSTOMMODULE_C_WRAPPER(CustomModule);
