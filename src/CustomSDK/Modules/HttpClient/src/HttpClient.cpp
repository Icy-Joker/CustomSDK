#include "stdafx.h"

#include "HttpClient/HttpClient.h"
#include "ui_HttpClient.h"

#include <QNetworkCookieJar>
#include <QSslError>
#include <QMessageBox>
#include <QMetaEnum>

HttpClient::HttpClient(QWidget* parent /*= nullptr*/):
  QWidget(parent),
  ui(new Ui::HttpClient()),
  network_access_manager(new QNetworkAccessManager(this))
{
  ui->setupUi(this);

  network_access_manager->setCookieJar(new QNetworkCookieJar(this));

  connect(network_access_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_finished(QNetworkReply*)));
}

HttpClient::~HttpClient()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void HttpClient::on_pushButton_SendRequest_clicked()
{
  QNetworkRequest network_request;
  network_request.setUrl(QUrl("http://www.baidu.com"));

  QNetworkReply* network_reply = nullptr;
  switch(ui->comboBox->currentIndex())
  {
    case 0:
    {
      network_reply = network_access_manager->get(network_request);
      break;
    }
    case 1:
    {
      network_reply = network_access_manager->post(network_request,QByteArray());
      break;
    }
    case 2:
    {
      network_reply = network_access_manager->put(network_request,QByteArray());
      break;
    }
    case 3:
    {
      network_reply = network_access_manager->deleteResource(network_request);
      break;
    }
    default:
    {
      QMessageBox::warning(this,"Error","Unsupported request type");
      break;
    }
  }
  if(network_reply)
  {
    connect(network_reply,SIGNAL(errorOccurred(QNetworkReply::NetworkError)),this,SLOT(slot_errorOccurred(QNetworkReply::NetworkError)));
  }
}

void HttpClient::slot_errorOccurred(QNetworkReply::NetworkError network_error)
{
  switch(network_error)
  {
    default:
    {
      qDebug() << QMetaEnum::fromType<QNetworkReply::NetworkError>().valueToKey(network_error);
      break;
    }
  }
}

void HttpClient::slot_finished(QNetworkReply* network_reply)
{
  if(network_reply)
  {
    QByteArray network_reply_data = network_reply->readAll();
    ui->textBrowser->setPlainText(network_reply_data);
  }
}
