#include "stdafx.h"

#include "VisualDefinateTool.h"

#include <QApplication>

#include <iostream>

int main(int argc,char* argv[])
{
  int result =0 ;

  QApplication app(argc,argv);

  VisualDefinateTool main_window;
  main_window.show();
  
  result = app.exec();
  
  return result;
}
