#include "stdafx.h"

#include <iostream>

#include "CustomModule4Python/CustomModule.h"

CustomModule::CustomModule() :
  AbstractCustomModule()
{
}

CustomModule::~CustomModule()
{
}

void CustomModule::doSayHello()
{
  std::cout << "[Python]:CustomModule::Hello World!" << std::endl;
}

CUSTOMMODULE_C_WRAPPER(CustomModule);
