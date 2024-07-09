#include "stdafx.h"

#include "NetworkTool/TcpSocketServer.h"
#include "ui_TcpSocketServer.h"

#include <QTcpServer>
#include <QTcpSocket>

#include <QMetaEnum>

TcpSocketServer::TcpSocketServer(QWidget* parent):
  QWidget(parent),
  ui(new Ui::TcpSocketServer()),
  tcp_socket_server(new QTcpServer(this))
{
  ui->setupUi(this);

  connect(tcp_socket_server, SIGNAL(newConnection()),this, SLOT(slot_newConnection()));
  connect(tcp_socket_server,&QTcpServer::acceptError,this,[&](QAbstractSocket::SocketError socket_error)
  {
    switch(socket_error)
    {
      default:
      {
        qDebug() << QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(socket_error);
        break;
      }
    }
  });
}

TcpSocketServer::~TcpSocketServer()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void TcpSocketServer::on_pushButton_ServerControl_clicked()
{
  if(ui->pushButton_ServerControl->text() == QString::fromUtf8("开始"))
  {
    QString server_address = ui->lineEdit_ServerAddress->text();
    unsigned short server_port = ui->spinBox_ServerPort->value();

    if(!tcp_socket_server->isListening())
    {
      if(tcp_socket_server->listen(QHostAddress(server_address),server_port))
      {
        ui->pushButton_ServerControl->setText(QString::fromUtf8("停止"));
        ui->lineEdit_ServerAddress->setEnabled(false);
        ui->spinBox_ServerPort->setEnabled(false);
      }
    }
  }
  else if(ui->pushButton_ServerControl->text() == QString::fromUtf8("停止"))
  {
    if(tcp_socket_server->isListening())
    {
      tcp_socket_server->close();

      ui->pushButton_ServerControl->setText(QString::fromUtf8("开始"));
      ui->lineEdit_ServerAddress->setEnabled(true);
      ui->spinBox_ServerPort->setEnabled(true);
    }
  }
}

void TcpSocketServer::on_pushButton_SendMessage_clicked()
{
  QString message_content = ui->lineEdit_MessageContent->text();
  if(QTcpSocket* socket_client = ui->comboBox_ClientConnected->currentData(Qt::UserRole).value<QTcpSocket*>())
  {
    socket_client->write(message_content.toUtf8());
  }
}

void TcpSocketServer::slot_newConnection()
{
  if(QTcpSocket* socket_client = tcp_socket_server->nextPendingConnection())
  {
    QString peer_address = socket_client->peerAddress().toString();
    unsigned short peer_port = socket_client->peerPort();

    QString endpoint_name = QString("%1:%2").arg(peer_address).arg(QString::number(peer_port));

    int index = ui->comboBox_ClientConnected->findText(endpoint_name,Qt::MatchExactly);
    if(index == -1)
    {
      ui->comboBox_ClientConnected->addItem(endpoint_name,QVariant::fromValue<QTcpSocket*>(socket_client));
    }

    connect(socket_client,&QTcpSocket::errorOccurred,this,[&,socket_client](QTcpSocket::SocketError socket_error)
    {
      if(QTcpSocket* socket_client = qobject_cast<QTcpSocket*>(sender()))
      {
        int index = ui->comboBox_ClientConnected->findData(QVariant::fromValue<QTcpSocket*>(socket_client),Qt::UserRole,Qt::MatchExactly);
        switch(socket_error)
        {
          case QTcpSocket::RemoteHostClosedError:
          {
            if(index != -1)
            {
              ui->comboBox_ClientConnected->removeItem(index);
            }
            break;
          }
          default:
          {
            qDebug() << QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(socket_error);
            break;
          }
        }
      }
    });
    connect(socket_client,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));
  }
}

void TcpSocketServer::slot_readyRead()
{
  if(QTcpSocket* socket_client = qobject_cast<QTcpSocket*>(sender()))
  {
    QString peer_address = socket_client->peerAddress().toString();
    QString peer_name = socket_client->peerName();
    unsigned short peer_port = socket_client->peerPort();

    QString message_content = socket_client->readAll();

    ui->textBrowser->append(QString("[%1:%2]:%3").arg(peer_address).arg(QString::number(peer_port)).arg(message_content));
    if(!ui->groupBox_ManulControl->isChecked())
    {
      socket_client->write(message_content.toUtf8());
    }
  }
}
