#pragma once

#ifndef __UDPSOCKETCLIENT_H__
# define __UDPSOCKETCLIENT_H__

#include <QWidget>

class QUdpSocket;

namespace Ui
{
  class UdpSocketClient;
}

class UdpSocketClient : public QWidget
{
  Q_OBJECT
public:
  explicit UdpSocketClient(QWidget* parent = nullptr);
  ~UdpSocketClient() override;
private slots:
  void on_pushButton_BindLocalPort_clicked();
  void on_checkBox_EnableAutoSend_stateChanged(int check_state);
  void on_pushButton_SendMessage_clicked();
private slots:
  void slot_connected();
  void slot_readyRead();
  void slot_disconnected();
signals:
  void signal_SendMessage();
private:
  Ui::UdpSocketClient* ui;

  QUdpSocket* udp_socket_client;
};

#endif // !__UDPSOCKETCLIENT_H__
