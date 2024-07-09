#include "stdafx.h"

#include "PortScanner/PortScanner.h"
#include "ui_PortScanner.h"

#include <QTcpSocket>
#include <QUdpSocket>

PortScanner::PortScanner(QWidget* parent,Qt::WindowFlags flags) :
  QMainWindow(parent,flags),
  ui(new Ui::PortScanner())
{
  ui->setupUi(this);
}

PortScanner::~PortScanner()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

bool doScan(const QString& ip_address,const QString& ip_port_text)
{
  bool result = false;

  QTcpSocket tcp_socket;
  tcp_socket.connectToHost(QHostAddress(ip_address),ip_port_text.toUInt());
  result = QAbstractSocket::ConnectedState == (tcp_socket.state() & QAbstractSocket::ConnectedState);

  return result;
}

void PortScanner::on_pushButton_Scan_clicked()
{
  QString ip_address = ui->lineEdit_IPAddress->text();
  QString ip_port_text = ui->lineEdit_Port->text();

  QStringList ip_ports = ip_port_text.split(";");
  std::for_each(ip_ports.begin(),ip_ports.end(),[&ip_address](QString& ip_port)
  {
    if(::doScan(ip_address,ip_port))
    {
      qDebug() << "IP Address: " << ip_address << " Port: " << ip_port;
    }
  });
}
