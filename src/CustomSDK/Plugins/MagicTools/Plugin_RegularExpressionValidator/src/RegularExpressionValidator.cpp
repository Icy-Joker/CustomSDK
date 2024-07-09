#include "stdafx.h"

#include "RegularExpressionValidator/RegularExpressionValidator.h"
#include "ui_RegularExpressionValidator.h"

#include <QMessageBox>

#include <regex>

RegularExpressionValidator::RegularExpressionValidator(QWidget* parent,Qt::WindowFlags flags):
  QMainWindow(parent,flags),
  ui(new Ui::RegularExpressionValidator())
{
  ui->setupUi(this);

  {
    ui->comboBox_MatchRules->addItem(QString::fromUtf8("自定义"),"");

    ui->comboBox_MatchRules->addItem(QString::fromUtf8("端口号"),R"([0-5]?\d{0,4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5])");
    ui->comboBox_MatchRules->addItem(QString::fromUtf8("域名"),R"((?:www.)?(?!-)(?:[A-Za-z0-9-]{1,63})(?:\.(?!-)(?:[A-Za-z0-9-]{1,63}))*(?:\.[A-Za-z0-9]{2,63}))");
    ui->comboBox_MatchRules->addItem(QString::fromUtf8("IP(v4)"),R"((?:(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)\.){3}(?:(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){1})");
    ui->comboBox_MatchRules->addItem(QString::fromUtf8("IP(v6)"),R"(([0-9a-fA-F]{1,4}:){1,7}([0-9a-fA-F]{1,4})?(::([0-9a-fA-F]{1,4}:){1,6}([0-9a-fA-F]{1,4}))?)");
    ui->comboBox_MatchRules->addItem(QString::fromUtf8("网络地址(域名)"),R"(((?:www.)?(?!-)(?:[A-Za-z0-9-]{1,63})(?:\.(?!-)(?:[A-Za-z0-9-]{1,63}))*(?:\.[A-Za-z0-9]{2,63})):([0-5]?\d{0,4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5]))");
    ui->comboBox_MatchRules->addItem(QString::fromUtf8("网络地址(IPv4)"),R"(((?:(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)\.){3}(?:(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){1}):([0-5]?\d{0,4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5]))");

    ui->comboBox_MatchRules->addItem(QString::fromUtf8("身份证号码"),R"(([1-9]\d{5})(\d{4})((?:0[1-9])|(?:1[0-2]))((?:[0-2][1-9])|10|20|30|31)(\d{2})(\d)([Xx\d]))");
  }
}

RegularExpressionValidator::~RegularExpressionValidator()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void RegularExpressionValidator::on_lineEdit_RegularExpression_editingFinished()
{
  QString match_rules = ui->lineEdit_RegularExpression->text();
  int index = ui->comboBox_MatchRules->findData(match_rules,Qt::ItemDataRole::UserRole,Qt::MatchFlag::MatchExactly);
  ui->comboBox_MatchRules->setCurrentIndex(index >= 0 ? index : 0);
}

void RegularExpressionValidator::on_comboBox_MatchRules_activated(int index)
{
  ui->lineEdit_RegularExpression->setText(ui->comboBox_MatchRules->itemData(index,Qt::ItemDataRole::UserRole).toString());
}

void RegularExpressionValidator::on_pushButton_Validate_clicked()
{
  const std::string match_rules = ui->lineEdit_RegularExpression->text().toStdString();
  const std::string match_content = ui->textEdit_MatchContent->toPlainText().toStdString();
  if(!match_rules.empty() && !match_content.empty())
  {
    try
    {
      std::regex regex(match_rules);
      std::smatch smatch_content;
      if(std::regex_match(match_content,smatch_content,regex))
      {
        std::string message_content = "Match Success!\n";
        message_content += "{\n";
        std::for_each(smatch_content.begin(),smatch_content.end(),[&](const std::string& matched_block)
        {
          message_content += " " + matched_block + "\n";
        });
        message_content += "}\n";
        QMessageBox::information(this,"Information",QString::fromStdString(message_content));
      }
      else
      {
        QMessageBox::information(this,"Information","Match Failed!");
      }
    }
    catch(std::regex_error& e)
    {
    }
  }
  else
  {
    QMessageBox::information(this,"Information","empty input");
  }
}
