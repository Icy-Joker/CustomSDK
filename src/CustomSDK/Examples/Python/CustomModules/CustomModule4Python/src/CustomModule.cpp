#include "stdafx.h"

#include "CustomModule4Python/CustomModule.h"

#include <iostream>

CustomModule::CustomModule():
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
