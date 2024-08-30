#include "stdafx.h"

#include "TcpSocketClient/TcpSocketClient.h"
#include "ui_TcpSocketClient.h"

#include <QTcpSocket>

TcpSocketClient::TcpSocketClient(QWidget* parent):
  QWidget(parent),
  ui(new Ui::TcpSocketClient()),
  tcp_socket_client(new QTcpSocket(this))
{
  ui->setupUi(this);

  connect(tcp_socket_client,SIGNAL(connected()),this,SLOT(slot_connected()));
  connect(tcp_socket_client,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));
  connect(tcp_socket_client,SIGNAL(disconnected()),this,SLOT(slot_disconnected()));
}

TcpSocketClient::~TcpSocketClient()
{
  if(tcp_socket_client)
  {
    tcp_socket_client->disconnectFromHost();
    tcp_socket_client->waitForDisconnected();
  }
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void TcpSocketClient::on_pushButton_SessionControl_clicked()
{
  if(ui->pushButton_SessionControl->text() == QString::fromUtf8("连接"))
  {
    QString remote_address = ui->lineEdit_RemoteAddress->text();
    unsigned short remote_port = ui->spinBox_ServerPort->value();

    tcp_socket_client->connectToHost(QHostAddress(remote_address),remote_port);
  }
  else if(ui->pushButton_SessionControl->text() == QString::fromUtf8("断开"))
  {
    tcp_socket_client->disconnectFromHost();
  }
}

void TcpSocketClient::on_pushButton_SendMessage_clicked()
{
  if(tcp_socket_client->state() == QTcpSocket::SocketState::ConnectedState)
  {
    QString message_content = ui->lineEdit_MessageContent->text();

    tcp_socket_client->write(message_content.toUtf8());
  }
}

void TcpSocketClient::slot_connected()
{
  ui->pushButton_SessionControl->setText("断开");
  ui->lineEdit_RemoteAddress->setEnabled(false);
  ui->spinBox_ServerPort->setEnabled(false);
}

void TcpSocketClient::slot_readyRead()
{
  QString peer_address = tcp_socket_client->peerAddress().toString();
  unsigned short peer_port = tcp_socket_client->peerPort();

  QString message_content = QString::fromUtf8(tcp_socket_client->readAll());

  ui->textBrowser->append(QString("[%1:%2]:%3").arg(peer_address).arg(QString::number(peer_port)).arg(message_content));
}

void TcpSocketClient::slot_disconnected()
{
  ui->pushButton_SessionControl->setText("连接");
  ui->lineEdit_RemoteAddress->setEnabled(true);
  ui->spinBox_ServerPort->setEnabled(true);
}
