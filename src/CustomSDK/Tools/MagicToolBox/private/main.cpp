#include "stdafx.h"
#include "MagicToolBox.h"

//#include <BasicUIFramework/BasicUIFramework.h>

#include <QApplication>

int main (int argc, char* argv[])
{
  int ret = 0;

  if(BasicUIFramework::initialize(argc,argv))
  {
        
    MagicToolBox magic_tool_box;
    magic_tool_box.show();

    ret=BasicUIFramework::exec();
  }

	return ret;
}
