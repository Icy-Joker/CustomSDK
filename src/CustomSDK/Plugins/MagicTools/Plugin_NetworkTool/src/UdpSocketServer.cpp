#include "stdafx.h"

#include "NetworkTool/UdpSocketServer.h"
#include "ui_UdpSocketServer.h"

#include <QUdpSocket>
#include <QNetworkDatagram>

#include <QMetaEnum>

UdpSocketServer::UdpSocketServer(QWidget* parent):
  QWidget(parent),
  ui(new Ui::UdpSocketServer()),
  udp_socket_server(new QUdpSocket(this))
{
  ui->setupUi(this);

  connect(udp_socket_server,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));
}

UdpSocketServer::~UdpSocketServer()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void UdpSocketServer::on_pushButton_ServerControl_clicked()
{
  if(ui->pushButton_ServerControl->text() == QString::fromUtf8("开始"))
  {
    QString server_address = ui->lineEdit_ServerAddress->text();
    unsigned short server_port = ui->spinBox_ServerPort->value();

    if(udp_socket_server->open(QIODevice::ReadWrite))
    {
      if(udp_socket_server->bind(QHostAddress(server_address),server_port))
      {
        ui->pushButton_ServerControl->setText(QString::fromUtf8("停止"));
        ui->lineEdit_ServerAddress->setEnabled(false);
        ui->spinBox_ServerPort->setEnabled(false);
      }
    }
  }
  else if(ui->pushButton_ServerControl->text() == QString::fromUtf8("停止"))
  {
    udp_socket_server->close();
    if(!udp_socket_server->isOpen())
    {
      ui->pushButton_ServerControl->setText(QString::fromUtf8("开始"));
      ui->lineEdit_ServerAddress->setEnabled(true);
      ui->spinBox_ServerPort->setEnabled(true);
    }
  }
}

void UdpSocketServer::slot_readyRead()
{
  QNetworkDatagram network_datagram = udp_socket_server->receiveDatagram();
  if(network_datagram.isValid())
  {
    QString peer_address = network_datagram.senderAddress().toString();
    unsigned short peer_port = network_datagram.senderPort();

    QString message_content = network_datagram.data();

    ui->textBrowser->append(QString("[%1:%2]:%3").arg(peer_address).arg(QString::number(peer_port)).arg(message_content));

    if(true)
    {
      udp_socket_server->writeDatagram(network_datagram.data(),QHostAddress(peer_address),peer_port);
    }
  }
}
