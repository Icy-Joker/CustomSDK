#include "stdafx.h"

#include "VisualDesigner.h"

#include <QApplication>

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  VisualDesigner main_window;
  main_window.show();

  result = app.exec();

  return result;
}