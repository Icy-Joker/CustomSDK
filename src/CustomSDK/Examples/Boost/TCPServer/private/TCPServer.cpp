#include "stdafx.h"

#include "TCPServer.h"
#include "TCPServerPrivate.h"
#include "ui_TCPServer.h"

#include <boost/function.hpp>

TCPServer::TCPServer(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QWidget(parent,flags),
  _p(new TCPServerPrivate(this)),
  ui(new Ui::TCPServer())
{
  ui->setupUi(this);

  //connect(_p,SIGNAL(sessionCreated()),this,SLOT());
  //connect(_p,SIGNAL(messageReceived()),this,SLOT());
  //connect(_p,SIGNAL(sessionCreated()),this,SLOT());
}

TCPServer::~TCPServer()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void TCPServer::on_pushButton_ServerControl_clicked()
{
  qDebug("on_pushButton_ServerControl_clicked");
  if(ui->pushButton_ServerControl->text() == QString::fromLocal8Bit("开始监听"))
  {
    std::string ip_address = ui->lineEdit_ServerAddress->text().toLocal8Bit().constData();
    unsigned short ip_port = ui->spinBox_ServerPort->value();

    _p->startServer(ip_port);

    ui->pushButton_ServerControl->setText(QString::fromLocal8Bit("停止监听"));
  }
  else if(ui->pushButton_ServerControl->text() == QString::fromLocal8Bit("停止监听"))
  { 
    _p->stopServer();

    ui->pushButton_ServerControl->setText(QString::fromLocal8Bit("开始监听"));
  }
}

void TCPServer::on_checkBox_EnableAutoEcho_stateChanged(int check_status)
{
  ui->pushButton_SendResponseMessage->setEnabled(Qt::CheckState::Checked != (Qt::CheckState) check_status);
}

void TCPServer::on_pushButton_SendResponseMessage_clicked()
{
  qDebug("on_pushButton_SendResponseMessage");
}
