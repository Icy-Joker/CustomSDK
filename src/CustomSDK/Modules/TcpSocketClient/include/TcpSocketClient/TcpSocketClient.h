#pragma once

#ifndef __TCPSOCKETCLIENT_H__
# define __TCPSOCKETCLIENT_H__

#include <QWidget>

class QTcpSocket;

namespace Ui
{
  class TcpSocketClient;
}

class TcpSocketClient_API TcpSocketClient : public QWidget
{
  Q_OBJECT
public:
  explicit TcpSocketClient(QWidget* parent = nullptr);
  ~TcpSocketClient() override;
private slots:
  void on_pushButton_SessionControl_clicked();
  void on_pushButton_SendMessage_clicked();
private slots:
  void slot_connected();
  void slot_readyRead();
  void slot_disconnected();
private:
  Ui::TcpSocketClient* ui;

  QTcpSocket* tcp_socket_client;
};

#endif // !__TCPSOCKETCLIENT_H__
