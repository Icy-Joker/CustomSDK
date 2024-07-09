#pragma once

#ifndef __HTTPCLIENT_H__
# define __HTTPCLIENT_H__

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui
{
  class HttpClient;
}

class HttpClient : public QWidget
{
  Q_OBJECT
public:
  explicit HttpClient(QWidget* parent = nullptr);
  ~HttpClient() override;
private slots:
  void on_pushButton_SendRequest_clicked();
private slots:
  void slot_errorOccurred(QNetworkReply::NetworkError network_error);
  void slot_finished(QNetworkReply* network_reply);
private:
  Ui::HttpClient* ui;
  QNetworkAccessManager* network_access_manager;
};

#endif // !__HTTPCLIENT_H__
