#include "stdafx.h"

#include "UdpSocketClient/UdpSocketClient.h"
#include "ui_UdpSocketClient.h"

#include <QUdpSocket>
#include <QNetworkDatagram>

UdpSocketClient::UdpSocketClient(QWidget* parent):
  QWidget(parent),
  ui(new Ui::UdpSocketClient()),
  udp_socket_client(new QUdpSocket(this))
{
  ui->setupUi(this);

  connect(udp_socket_client,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));
}

UdpSocketClient::~UdpSocketClient()
{
  if(udp_socket_client)
  {
    udp_socket_client->disconnectFromHost();
    udp_socket_client->waitForDisconnected();
  }
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void UdpSocketClient::on_pushButton_BindLocalPort_clicked()
{
  udp_socket_client->close();

  if(ui->pushButton_BindLocalPort->text() == QString::fromUtf8("绑定端口"))
  {
    if(udp_socket_client->open(QIODevice::ReadWrite))
    {
      if(udp_socket_client->bind(QHostAddress::AnyIPv4,ui->spinBox_LocalPort->value()))
      {
        ui->pushButton_BindLocalPort->setText(QString::fromUtf8("解绑端口"));
      }
    }
  }
  else if(ui->pushButton_BindLocalPort->text() == QString::fromUtf8("解绑端口"))
  {
    if(!udp_socket_client->isOpen())
    {
      ui->pushButton_BindLocalPort->setText(QString::fromUtf8("绑定端口"));
    }
  }
}

void UdpSocketClient::on_pushButton_SendMessage_clicked()
{
  QString remore_adddress = ui->lineEdit_RemoteAddress->text();
  unsigned short remore_port = ui->spinBox_ServerPort->value();
  QString message_content = ui->lineEdit_MessageContent->text();

  udp_socket_client->writeDatagram(message_content.toUtf8(),QHostAddress(remore_adddress),remore_port);
}

void UdpSocketClient::slot_connected()
{
  ui->lineEdit_RemoteAddress->setEnabled(false);
  ui->spinBox_ServerPort->setEnabled(false);
  ui->spinBox_LocalPort->setEnabled(false);
}

void UdpSocketClient::slot_readyRead()
{
  QNetworkDatagram network_datagram = udp_socket_client->receiveDatagram();
  if(network_datagram.isValid())
  {
    QString peer_address = network_datagram.senderAddress().toString();
    unsigned short peer_port = network_datagram.senderPort();

    QString message_content = QString::fromUtf8(network_datagram.data());

    ui->textBrowser->append(QString("[%1:%2]:%3").arg(peer_address).arg(QString::number(peer_port)).arg(message_content));
  }
}

void UdpSocketClient::slot_disconnected()
{
  ui->lineEdit_RemoteAddress->setEnabled(true);
  ui->spinBox_ServerPort->setEnabled(true);
  ui->spinBox_LocalPort->setEnabled(true);
}
