#include "stdafx.h"

#include "RegularExpressionValidator.h"
#include "RegularExpressionValidatorPrivate.h"
#include "ui_RegularExpressionValidator.h"

#include <QMessageBox>

#include <regex>

RegularExpressionValidator::RegularExpressionValidator(QWidget* parent, Qt::WindowFlags flags):
  QWidget(parent,flags),
  _p(new RegularExpressionValidatorPrivate()),
  ui(new Ui::RegularExpressionValidator())
{
  ui->setupUi(this);

  {
    ui->comboBox_MatchRules->addItem("Custom", "");
    ui->comboBox_MatchRules->addItem("Port", "(?:[0-5]?\\d{0,4})|(?:6[0-4]\\d{3})|(?:65[0-4]\\d{2})|(?:655[0-2]\\d)|(?:6553[0-5])");
    ui->comboBox_MatchRules->addItem("IP(v4)", "(?:(?:(?:25[0-5])|(?:2[0-4]\\d)|(?:[0-1]?\\d?\\d)).){3}(?:(?:25[0-5])|(?:2[0-4]\\d)|(?:[0-1]?\\d?\\d))");
    ui->comboBox_MatchRules->addItem("InternationAddress(v4)", "((?:(?:(?:25[0-5])|(?:2[0-4]\\d)|(?:[0-1]?\\d?\\d)).){3}(?:(?:25[0-5])|(?:2[0-4]\\d)|(?:[0-1]?\\d?\\d))):((?:[0-5]?\\d{0,4})|(?:6[0-4]\\d{3})|(?:65[0-4]\\d{2})|(?:655[0-2]\\d)|(?:6553[0-5]))");
    ui->comboBox_MatchRules->addItem("IdentifyCardNumber","^([1-9]\\d{5})(\\d{4})((?:0[1-9])|(?:1[0-2]))((?:[0-2][1-9])|10|20|30|31)(\\d{2})(\\d)([Xx\\d])$");
  }
}

RegularExpressionValidator::~RegularExpressionValidator()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }

  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void RegularExpressionValidator::on_lineEdit_RegularExpression_editingFinished()
{
  QString match_rules = ui->lineEdit_RegularExpression->text();
  int index = ui->comboBox_MatchRules->findData(match_rules, Qt::ItemDataRole::UserRole, Qt::MatchFlag::MatchExactly);
  ui->comboBox_MatchRules->setCurrentIndex(index>=0?index:0);
}

void RegularExpressionValidator::on_comboBox_MatchRules_activated(int index)
{
  ui->lineEdit_RegularExpression->setText(ui->comboBox_MatchRules->itemData(index, Qt::ItemDataRole::UserRole).toString());
}

void RegularExpressionValidator::on_pushButton_Validate_clicked()
{
  const std::string match_rules = ui->lineEdit_RegularExpression->text().toStdString();
  const std::string match_content = ui->textEdit_MatchContent->toPlainText().toStdString();
  if (!match_rules.empty()&&!match_content.empty())
  {
    try
    {
      std::regex regex(match_rules);
      std::smatch smatch_content;
      if (std::regex_match(match_content,smatch_content,regex))
      {
        std::string message_content =  "Match Success!\n";
        message_content += "{\n";
        std::for_each(smatch_content.begin(),smatch_content.end(),[&](const std::string& matched_block)
        {
          message_content += " " + matched_block + "\n";
        });
        message_content += "}\n";
        QMessageBox::information(this, "Information", QString::fromStdString(message_content));
      }
      else
      {
        QMessageBox::information(this, "Information", "Match Failed!");
      }
    }
    catch (std::regex_error& e)
    {
    }
  }
  else
  {
    QMessageBox::information(this, "Information", "empty input");
  }
}
