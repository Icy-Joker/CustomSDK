#pragma once

#ifndef __SERIALPORTDEBUGGER_H__
# define __SERIALPORTDEBUGGER_H__

#include <boost/asio/serial_port.hpp>
#include <boost/thread.hpp>

#include <QMainWindow>

#include <set>

namespace Ui
{
  class SerialPortDebugger;
}

class SerialPortDebuggerPrivate;

class SerialPortDebugger : public QMainWindow
{
  Q_OBJECT
public:
  explicit SerialPortDebugger(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~SerialPortDebugger();
private:
  void doHandleMessage(const QByteArray& byte_array);
private slots:
  void on_pushButton_SerialPortControl_clicked();
  void on_checkBox_EnableAutoSend_stateChanged(int check_state);
  void on_pushButton_SendMessage_clicked();
signals:
  void signal_SendMessage();
private:
  Ui::SerialPortDebugger* ui;

  SerialPortDebuggerPrivate* private_ptr;
};

#endif // !__SERIALPORTDEBUGGER_H__
