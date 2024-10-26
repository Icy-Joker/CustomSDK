#include "stdafx.h"

#include "CustomModule/CustomModule.h"

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
  std::cout <<  "[CPlusPlus]:CustomModule::Hello World!" << std::endl;
}
