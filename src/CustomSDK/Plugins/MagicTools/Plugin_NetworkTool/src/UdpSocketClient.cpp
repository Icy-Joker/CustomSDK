#include "stdafx.h"

#include "NetworkTool/UdpSocketClient.h"
#include "ui_UdpSocketClient.h"

#include <boost/thread.hpp>

#include <QUdpSocket>
#include <QNetworkDatagram>

UdpSocketClient::UdpSocketClient(QWidget* parent):
  QWidget(parent),
  ui(new Ui::UdpSocketClient()),
  udp_socket_client(new QUdpSocket(this))
{
  ui->setupUi(this);

  connect(udp_socket_client,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));

  connect(this,SIGNAL(signal_SendMessage()),this,SLOT(on_pushButton_SendMessage_clicked()));
}

UdpSocketClient::~UdpSocketClient()
{
  if(udp_socket_client)
  {
    //udp_socket_client->disconnectFromHost();
    //udp_socket_client->waitForDisconnected();
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
        ui->spinBox_LocalPort->setEnabled(false);
        ui->pushButton_BindLocalPort->setText(QString::fromUtf8("解绑端口"));
      }
    }
  }
  else if(ui->pushButton_BindLocalPort->text() == QString::fromUtf8("解绑端口"))
  {
    if(!udp_socket_client->isOpen())
    {
      ui->spinBox_LocalPort->setEnabled(true);
      ui->pushButton_BindLocalPort->setText(QString::fromUtf8("绑定端口"));
    }
  }
}

void UdpSocketClient::on_checkBox_EnableAutoSend_stateChanged(int check_state)
{
  if(check_state == Qt::CheckState::Checked)
  {
    ui->spinBox->setEnabled(false);

    ui->lineEdit_RemoteAddress->setEnabled(false);
    ui->spinBox_ServerPort->setEnabled(false);

    ui->lineEdit_MessageContent->setEnabled(false);
    ui->pushButton_SendMessage->setEnabled(false);

    boost::thread([this]()
    {
      while(ui->checkBox_EnableAutoSend->isChecked())
      {
        emit signal_SendMessage();
        boost::this_thread::sleep_for(boost::chrono::milliseconds(ui->spinBox->value()));
      }
    });
  }
  else if(check_state == Qt::CheckState::Unchecked)
  {
    ui->spinBox->setEnabled(true);

    ui->lineEdit_RemoteAddress->setEnabled(true);
    ui->spinBox_ServerPort->setEnabled(true);

    ui->lineEdit_MessageContent->setEnabled(true);
    ui->pushButton_SendMessage->setEnabled(true);
  }
}

void UdpSocketClient::on_pushButton_SendMessage_clicked()
{
  QString remote_address = ui->lineEdit_RemoteAddress->text();
  unsigned short remote_port = ui->spinBox_ServerPort->value();
  QString message_content = ui->lineEdit_MessageContent->text();

  udp_socket_client->writeDatagram(message_content.toUtf8(),QHostAddress(remote_address),remote_port);
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

    ui->textBrowser->append(QString("[%1:%2]:%3").arg(peer_address,QString::number(peer_port),message_content));
  }
}

void UdpSocketClient::slot_disconnected()
{
  ui->lineEdit_RemoteAddress->setEnabled(true);
  ui->spinBox_ServerPort->setEnabled(true);
  ui->spinBox_LocalPort->setEnabled(true);
}
