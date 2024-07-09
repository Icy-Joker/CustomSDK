#include "stdafx.h"

#include "NetworkTool/HttpServer.h"
#include "ui_HttpServer.h"

#include <httplib.h>

#include <boost/thread.hpp>

class HttpServerPrivate
{
private:
  httplib::Server http_server;

  friend class HttpServer;
};

HttpServer::HttpServer(QWidget* parent /*= nullptr*/):
  QWidget(parent),
  ui(new Ui::HttpServer()),
  private_ptr(new HttpServerPrivate())
{
  ui->setupUi(this);

  connect(this,SIGNAL(showMessage(const QString&)),this,SLOT(slot_showMessage(const QString&)));
}

HttpServer::~HttpServer()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

bool HttpServer::start(unsigned short server_port)
{
  bool result = false;

  boost::function<void(const httplib::Request&,httplib::Response&)> doDefault = [&](const httplib::Request& req,httplib::Response& res)
  {
    std::string result = "";
    try
    {
      result += "METHOD:" + req.method + "\n";
      result += "PATH:" + req.path + "\n";
      result += "\n";
      if(!req.headers.empty())
      {
        std::for_each(req.headers.begin(),req.headers.end(),[&result](const httplib::Headers::value_type& item)
        {
          result += item.first + ":" + item.second + "\n";
        });
        result += "\n";
      }
      if(!req.params.empty())
      {
        std::for_each(req.params.begin(),req.params.end(),[&result](const httplib::Params::value_type& item)
        {
          result += item.first + ":" + item.second + "\n";
        });
      }

      res.set_content(result,"text/plain");
    }
    catch(const std::exception& e)
    {
      res.status = 500;// 返回 HTTP 500 错误
      result += "Internal Server Error";
      res.set_content(result,"text/plain");
    }

    emit showMessage(QString::fromStdString(result));
  };

  boost::thread thread_server([&]
  {
    if(!private_ptr->http_server.is_running())
    {
      private_ptr->http_server.Get(".*",doDefault);
      private_ptr->http_server.Post(".*",doDefault);
      private_ptr->http_server.Put(".*",doDefault);
      private_ptr->http_server.Patch(".*",doDefault);
      private_ptr->http_server.Delete(".*",doDefault);
      private_ptr->http_server.Options(".*",doDefault);

      private_ptr->http_server.listen("0.0.0.0",server_port);
    }
  });

  private_ptr->http_server.wait_until_ready();
  result = private_ptr->http_server.is_running();

  return result;
}

bool HttpServer::stop()
{
  bool result = false;

  private_ptr->http_server.stop();
  private_ptr->http_server.decommission();

  result = true;/// TODO: 更合理的方法判断服务关闭状态

  return result;
}

void HttpServer::on_pushButton_clicked()
{
  if(ui->pushButton->text() == QString::fromUtf8("启动"))
  {
    unsigned short server_port = ui->spinBox->value();

    if(start(server_port))
    {
      ui->pushButton->setText(QString::fromUtf8("停止"));
    }
  }
  else if(ui->pushButton->text() == QString::fromUtf8("停止"))
  {
    if(stop())
    {
      ui->pushButton->setText(QString::fromUtf8("启动"));
    }
  }
}

void HttpServer::slot_showMessage(const QString& message_content)
{
  ui->textBrowser->setPlainText(message_content);
}
