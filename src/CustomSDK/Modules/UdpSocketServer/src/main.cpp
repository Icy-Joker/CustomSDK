#include "stdafx.h"

#include "UdpSocketServer/UdpSocketServer.h"

#include <QApplication>

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  UdpSocketServer main_window;
  main_window.show();

  result = app.exec();

  return result;
}
