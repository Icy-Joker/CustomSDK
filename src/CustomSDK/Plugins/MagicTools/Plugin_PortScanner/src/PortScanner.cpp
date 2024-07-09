#include "stdafx.h"

#include "PortScanner/PortScanner.h"
#include "ui_PortScanner.h"

#include <boost/asio.hpp>

#include <QTcpSocket>
#include <QUdpSocket>
#include <QStandardItemModel>

PortScanner::PortScanner(QWidget* parent,Qt::WindowFlags flags) :
  QMainWindow(parent,flags),
  ui(new Ui::PortScanner())
{
  ui->setupUi(this);

  if(auto* model = new QStandardItemModel(this))
  {
    ui->listView->setModel(model);
  }
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

  if(true)
  {
    QTcpSocket tcp_socket;
    tcp_socket.connectToHost(QHostAddress(ip_address),ip_port_text.toUInt());
    tcp_socket.waitForConnected(3000);
    result = QAbstractSocket::ConnectedState == (tcp_socket.state() & QAbstractSocket::ConnectedState);
  }
  else
  {
  }

  return result;
}

void PortScanner::on_pushButton_Scan_clicked()
{
  QString ip_address = ui->lineEdit_IPAddress->text();
  QString ip_port_text = ui->lineEdit_Port->text();

  QStringList ip_ports = ip_port_text.split(";");

  boost::asio::thread_pool thread_pool(12);

  if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->listView->model()))
  {
    model->clear();
    std::for_each(ip_ports.begin(),ip_ports.end(),[&](QString& ip_port)
    {
      if(!ip_port.isEmpty())
      {
        boost::asio::post(thread_pool,[&]
        {
          qDebug() << "IP Address: " << ip_address << " Port: " << ip_port << " status: " << (::doScan(ip_address,ip_port) ? "opened" : "closed");
        });// 将任务提交到线程池
        model->appendRow(new QStandardItem(QString("%1:%2 %3").arg(ip_address).arg(ip_port).arg(::doScan(ip_address,ip_port) ? "opened" : "closed")));
      }
    });
  }
}
