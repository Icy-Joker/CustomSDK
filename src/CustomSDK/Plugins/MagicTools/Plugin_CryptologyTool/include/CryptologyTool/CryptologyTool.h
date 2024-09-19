#pragma once

#ifndef __CRYPTOLOGYTOOL_H__
# define __CRYPTOLOGYTOOL_H__

#include <QMainWindow>

namespace Ui
{
  class CryptologyTool;
}

class CryptologyTool : public QMainWindow
{
public:
  Q_OBJECT
public:
  explicit CryptologyTool(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~CryptologyTool();
private slots:
  void on_pushButton_Encryption_clicked();
  void on_pushButton_Decryption_clicked();
private:
  Ui::CryptologyTool* ui;
};

#endif // !__CRYPTOLOGYTOOL_H__
