#include "stdafx.h"

#include "HttpClient/HttpClient.h"

#include <QApplication>

int main(int argc,char* argv[])
{
  int result = 0;

  QApplication app(argc,argv);

  HttpClient main_window;
  main_window.show();

  result = app.exec();

  return result;
}
