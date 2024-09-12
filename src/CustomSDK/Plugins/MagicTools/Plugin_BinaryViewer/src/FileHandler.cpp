#include "stdafx.h"

#include "FileHandler.h"

#include <QDebug>

FileHandler::FileHandler(QObject* parent):
  QThread(parent)
{
}

FileHandler::~FileHandler()
{
}

void FileHandler::run()
{
  while(true)
  {
    qDebug() << "adsad";
  }
}
