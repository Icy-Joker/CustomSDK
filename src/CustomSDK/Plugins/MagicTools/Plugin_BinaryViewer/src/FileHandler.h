#pragma once

#ifndef __FILEHANDLER_H__
# define __FILEHANDLER_H__

#include <QThread>

class FileHandler : public QThread
{
  Q_OBJECT
public:
  explicit FileHandler(QObject* parent = nullptr);
  ~FileHandler();
public:
  void run() override;
};

#endif // !__FILEHANDLER_H__
