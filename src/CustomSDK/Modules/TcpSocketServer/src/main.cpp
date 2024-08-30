#include "stdafx.h"

#include "TcpSocketServer/TcpSocketServer.h"

#include <QApplication>

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  TcpSocketServer main_window;
  main_window.show();

  result = app.exec();

  return result;
}
