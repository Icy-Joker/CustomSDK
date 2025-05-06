#include "stdafx.h"

#include "MagicToolBox.h"

#include <BasicUIFramework/BasicUIFramework.h>
#include <BasicUIFramework/SplashScreen.h>

#include <CustomFramework/CustomFrameworkManager.h>

int main(int argc,char* argv[])
{
  int result = 0;

  if(BasicUIFramework::initialize(argc,argv))
  {
    if(CustomFrameworkManager::getInstance()->initializeWithConfig("../etc/MagicToolBox.xml"))
    {
      MagicToolBox magic_toolBox;
      magic_toolBox.show();

      result = BasicUIFramework::exec();
    }
  }

  return result;
}
