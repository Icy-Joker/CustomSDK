#pragma once

#ifndef __HTTPSERVER_H__
# define __HTTPSERVER_H__

#include <QWidget>

namespace Ui
{
  class HttpServer;
}

class HttpServerPrivate;

class HttpServer : public QWidget
{
  Q_OBJECT
public:
  explicit HttpServer(QWidget* parent = nullptr);
  ~HttpServer() override;
private:
  bool start(unsigned short server_port);
  bool stop();
private slots:
  void on_pushButton_clicked();
private slots:
  void slot_showMessage(const QString&);
signals:
  void showMessage(const QString&);
private:
  Ui::HttpServer* ui;

  HttpServerPrivate* private_ptr;
};

#endif // !__HTTPSERVER_H__
