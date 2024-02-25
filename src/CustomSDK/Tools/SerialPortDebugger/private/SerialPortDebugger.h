#pragma once

#ifndef __SERIALPORTDEBUGGER_H__
# define __SERIALPORTDEBUGGER_H__

#include <QMainWindow>

#include <set>

namespace Ui
{
  class SerialPortDebugger;
}
struct SerialPortDebuggerPrivate;

class SerialPortDebugger : public QMainWindow
{
  Q_OBJECT
public:
  explicit SerialPortDebugger(QWidget* parent =nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~SerialPortDebugger();
public:
private slots:
  void on_pushButton_SerialPortControl_clicked();
  void on_pushButton_SendMessage_clicked();
private:
  SerialPortDebuggerPrivate* _p;
  Ui::SerialPortDebugger* ui;
};

#endif // !__SERIALPORTDEBUGGER_H__
