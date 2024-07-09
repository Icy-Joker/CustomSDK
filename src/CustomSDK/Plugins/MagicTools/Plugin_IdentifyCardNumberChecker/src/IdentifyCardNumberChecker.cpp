#include "stdafx.h"

#include "IdentifyCardNumberChecker/IdentifyCardNumberChecker.h"
#include "ui_IdentifyCardNumberChecker.h"

#include <boost/filesystem.hpp>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>

#include <regex>

IdentifyCardNumberChecker::IdentifyCardNumberChecker(QWidget* parent,Qt::WindowFlags flags):
  QMainWindow(parent,flags),
  ui(new Ui::IdentifyCardNumberChecker())
{
  ui->setupUi(this);

  QFile database_file(":/data/information.sql");
  if(database_file.exists())
  {
    if(database_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream in_stream(&database_file);

      if(!QSqlDatabase::database(QSqlDatabase::defaultConnection).isOpen())
      {
        QSqlDatabase sqlite_database = QSqlDatabase::addDatabase("QSQLITE");
        if(sqlite_database.isValid())
        {
          if(!sqlite_database.isOpen() && sqlite_database.open())
          {
            QString sql_statement;
            while(in_stream.readLineInto(&sql_statement))
            {
              QSqlQuery sqlite_query;
              if(!sqlite_query.exec(sql_statement))
              {
                qDebug("%s",qPrintable(QString("error while executing \"%1\"").arg(sql_statement)));
              }
            }
          }
        }
      }
      database_file.close();
    }
  }
}

IdentifyCardNumberChecker::~IdentifyCardNumberChecker()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void IdentifyCardNumberChecker::on_pushButton_Check_clicked()
{
  std::string identify_card_number = ui->lineEdit_IdentifiCardNumber->text().toStdString();

  std::smatch sub_match;
  if(std::regex_match(identify_card_number,sub_match,std::regex("^([1-9]\\d{5})(\\d{4})((?:0[1-9])|(?:1[0-2]))((?:[0-2][1-9])|10|20|30|31)(\\d{2})(\\d)([Xx\\d])$")))
  {
    std::array<char,17> array_coefficient = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    std::array<char,11> array_parity_bit = {'1','0','X','9','8','7','6','5','4','3','2'};

    int summation_of_product = 0;
    for(std::size_t i = 0;i < 17;++i)
    {
      summation_of_product += (identify_card_number[i] - '0') * array_coefficient[i];
    }
    const char valid_parity_bit = array_parity_bit[summation_of_product % 11];
    const char current_parity_bit = identify_card_number[17] == 'x' ? 'X' : identify_card_number[17];

    if(current_parity_bit == valid_parity_bit)
    {
      const std::string& administrative_code = sub_match[1];
      const std::string& birth_year = sub_match[2];
      const std::string& birth_month = sub_match[3];
      const std::string& birth_day = sub_match[4];
      //const std::string& xxx = sub_match[5];///Todo:派出所编号处理?
      const std::string& sex_bit = sub_match[6];
      const std::string& party_bit = sub_match[7];

      char birth_index = std::stoi(sex_bit) / 2 + 1;
      const std::string sex = std::stoi(sex_bit) % 2 == 0 ? "女" : "男";

      QSqlDatabase sqlite_database = QSqlDatabase::database(QSqlDatabase::defaultConnection);
      if(sqlite_database.isOpen())
      {
        QSqlQuery sqlite_query;
        sqlite_query.prepare("select province,city,county from ID_LOCATION where administrative_code = :administrative_code;");
        sqlite_query.bindValue(":administrative_code",QString::fromStdString(administrative_code));
        QString id_location = QString::fromUtf8("未知地区");
        sqlite_query.exec();
        if(sqlite_query.next())
        {
          QString province = sqlite_query.value("province").toString();
          QString city = sqlite_query.value("city").toString();
          QString county = sqlite_query.value("county").toString();

          city = city == province ? "" : city;
          county = (county == province) ? "" : (county == city) ? "" : county;

          id_location = province + city + county;
        }

        QString check_result = QString::fromUtf8("该公民可能为%1-%2-%3在%4某派出所登记的第%5个%6性")
                               .arg(QString::fromStdString(birth_year))
                               .arg(QString::fromStdString(birth_month))
                               .arg(QString::fromStdString(birth_day))
                               .arg(QString::fromStdString(id_location.toStdString()))
                               .arg(QString::number(birth_index))
                               .arg(QString::fromStdString(sex));

        ui->textBrowser_Output->setText(QString::fromUtf8("校验成功:\n%1").arg(check_result));
      }
    }
    else
    {
      ui->textBrowser_Output->setText(QString::fromUtf8("校验失败:身份证号无法识别"));
    }
  }
}
