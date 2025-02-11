#include "stdafx.h"

#include "VisualDefinitionTool.h"

#include <QApplication>

#include <iostream>

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  VisualDefinitionTool main_window;
  main_window.showMaximized();

  result = app.exec();

  return result;
}
