#include "stdafx.h"

#include "RegularExpressionValidator.h"

#include <QApplication>

int main(int argc, char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  RegularExpressionValidator main_window;
  main_window.show();

  result = app.exec(); 

  return result;
}