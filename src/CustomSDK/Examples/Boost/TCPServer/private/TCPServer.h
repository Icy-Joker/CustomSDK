#pragma once

#ifndef __TCPSERVER_H__
# define __TCPSERVER_H__

#include <boost/shared_ptr.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <QWidget>

namespace Ui
{
  class TCPServer;
}
class TCPServerPrivate;

class TCPServer : public QWidget
{
  Q_OBJECT
public:
  explicit TCPServer(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~TCPServer();
public:
protected:
private slots:
  void on_pushButton_ServerControl_clicked();
  void on_checkBox_EnableAutoEcho_stateChanged(int);
  void on_pushButton_SendResponseMessage_clicked();
private slots:
  //void slot_sessionCreated(boost::shared_ptr<boost::asio::ip::tcp::socket>);
  //void slot_messageReceived(boost::shared_ptr<boost::asio::ip::tcp::socket>);
  //void slot_sessionDestroyed(boost::shared_ptr<boost::asio::ip::tcp::socket>);
private:
  TCPServerPrivate* _p;
  Ui::TCPServer* ui;
};

#endif // !__TCPSERVER_H__
