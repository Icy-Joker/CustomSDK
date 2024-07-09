#include "stdafx.h"

#include "NetworkTool/HttpClient.h"
#include "ui_HttpClient.h"

#include <httplib.h>

#include <QStandardItemModel>

#define MATCH_RULE_IPV4 R"((?:0|(?!0)[0-1]?\d{1,2}|2[0-4]\d|25[0-5])(?:\.(?:0|(?!0)[0-1]?\d{1,2}|2[0-4]\d|25[0-5])){3})"
#define MATCH_RULE_PORT R"(0|(?!0)[0-5]?\d{1,4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5])"
#define MATCH_RULE_PATH R"((?:/\w*)*)"
#define MATCH_RULE_PARM_STRING R"((?:\w+=\w+)(?:&(?:\w+=\w+))*)"

HttpClient::HttpClient(QWidget* parent /*= nullptr*/):
  QWidget(parent),
  ui(new Ui::HttpClient())
{
  ui->setupUi(this);

  if(QStandardItemModel* model = new QStandardItemModel(this))
  {
    ui->tableView->setModel(model);

    model->setHorizontalHeaderLabels({"Name","Value"});
  }

  {
    ui->lineEdit_RequestURL->setText("127.0.0.1:80//////?a=b&c=d");
  }
}

HttpClient::~HttpClient()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void HttpClient::on_lineEdit_RequestURL_editingFinished()
{
  std::string current_text = ui->lineEdit_RequestURL->text().toStdString();
  std::string match_rules = "(" MATCH_RULE_IPV4 ")(?:\\:(" MATCH_RULE_PORT "))?(" MATCH_RULE_PATH ")?(?:\\?(" MATCH_RULE_PARM_STRING "))?";

  std::regex regex(match_rules);
  std::smatch smatch_content;
  if(std::regex_match(current_text,smatch_content,regex))
  {
    const std::string url_host = smatch_content[1].matched ? std::regex_replace(smatch_content[1].str(),std::regex(R"(\b0+(\d+))"),"$1") : "127.0.0.1";
    const int url_port = smatch_content[2].matched ? std::stoi(std::regex_replace(smatch_content[2].str(),std::regex(R"(\b0+(\d+))"),"$1")) : 80;
    const std::string url_path = smatch_content[3].matched ? std::regex_replace(smatch_content[3].str(),std::regex(R"(/+)"),"/") : "/";
    const std::string url_parameter_string = smatch_content[4].matched ? smatch_content[4].str() : "";

    ui->lineEdit_Host->setText(QString::fromStdString(url_host));
    ui->spinBox_Port->setValue(url_port);
    ui->lineEdit_Path->setText(QString::fromStdString(url_path));
    {
      if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model()))
      {
        model->clear();;

        std::stringstream string_stream(url_parameter_string);
        std::string token;
        while(std::getline(string_stream,token,'&'))
        {
          std::stringstream string_stream_parameter(token);
          std::string left,right;

          std::getline(string_stream_parameter,left,'=');
          std::getline(string_stream_parameter,right);

          model->appendRow({new QStandardItem(QString::fromStdString(left)),new QStandardItem(QString::fromStdString(right))});
        }
      }
    }
  }
}

void HttpClient::on_pushButton_SendRequest_clicked()
{
  const std::string url_host = ui->lineEdit_Host->text().toStdString();
  const int url_port = ui->spinBox_Port->value();
  const std::string url_path = ui->lineEdit_Path->text().toStdString();

  std::string url_parameter_string;
  httplib::Params url_parameter;
  if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model()))
  {
    for(int row = 0;row < model->rowCount();++row)
    {
      if(QStandardItem* item_name = model->item(row,0))
      {
        if(QStandardItem* item_value = model->item(row,1))
        {
          url_parameter_string += item_name->text().toStdString() + "=" + item_value->text().toStdString() + "&";

          url_parameter.emplace(item_name->text().toStdString(),item_value->text().toStdString());
        }
      }
    }
  }

  httplib::Client http_client(url_host,url_port);
  // 设置超时
  http_client.set_connection_timeout(5);
  http_client.set_read_timeout(10);

  httplib::Result http_result;
  switch(ui->comboBox->currentIndex())
  {
    default:
    case 0:///GET
    {
      const std::string url_query = url_parameter_string.empty() ? url_path : (url_path + "?" + url_parameter_string.substr(0,url_parameter_string.size() - 1));
      http_result = http_client.Get(url_query);
      break;
    }
    case 1:///POST
    {
      http_result = http_client.Post(url_path,url_parameter);
      break;
    }
    case 2:///PUT
    {
      http_result = http_client.Put(url_path);
      break;
    }
    case 3:///PATCH
    {
      http_result = http_client.Patch(url_path);
      break;
    }
    case 4:///DELETE
    {
      http_result = http_client.Delete(url_path);
      break;
    }
    case 5:///HEAD
    {
      http_result = http_client.Head(url_path);
      break;
    }
    case 6:///OPTIONS
    {
      http_result = http_client.Options(url_path);
      break;
    }
  }
  if(http_result)
  {
    QString message_content = "";
    message_content += QString("STATUS: %1\n").arg(QString::number(http_result->status));
    message_content += "\n";
    message_content += QString::fromStdString(http_result->body);
    ui->textBrowser->setPlainText(message_content);
  }
}
