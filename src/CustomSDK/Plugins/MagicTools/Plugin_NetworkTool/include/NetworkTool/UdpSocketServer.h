#pragma once

#ifndef __UDPSOCKETSERVER_H__
# define __UDPSOCKETSERVER_H__

#include <QWidget>

class QUdpSocket;

namespace Ui
{
  class UdpSocketServer;
}

class UdpSocketServer : public QWidget
{
  Q_OBJECT
public:
  explicit UdpSocketServer(QWidget* parent = nullptr);
  ~UdpSocketServer() override;
private slots:
  void on_pushButton_ServerControl_clicked();
private slots:
  void slot_readyRead();
private:
  Ui::UdpSocketServer* ui;

  QUdpSocket* udp_socket_server;
};

#endif // !__UDPSOCKETSERVER_H__
