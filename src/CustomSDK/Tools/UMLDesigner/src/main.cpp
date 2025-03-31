#include "stdafx.h"

#include <QApplication>

#include <iostream>

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  result = app.exec();

  return result;
}
