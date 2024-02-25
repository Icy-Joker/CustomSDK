#include "stdafx.h"

#include "SerialPortDebugger.h"

#include <QApplication>

int main(int argc, char* argv[])
{
  int result = 0;

  QApplication app(argc, argv);

  SerialPortDebugger main_window;
  main_window.show();

  result = app.exec();

  return result;
}
