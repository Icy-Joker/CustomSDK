#include "RegularExpressionValidator.h"
#include "ui_RegularExpressionValidator.h"

#include <BasicUIFramework/CustomControls/CustomWindowTitleBar.h>
#include <BasicUIFramework/CustomControls/CustomMessageBox.h>

#include <regex>

RegularExpressionValidator::RegularExpressionValidator(QWidget* parent, Qt::WindowFlags flags):
  QWidget(parent,flags),
  ui(new Ui::RegularExpressionValidator())
{
	ui->setupUi(this);

  if(QLayout* default_layout = this->layout())
  {
    default_layout->setMenuBar(new CustomWindowTitleBar(this));
  }

	ui->comboBox_MatchRules->addItem("Custom", "");
	ui->comboBox_MatchRules->addItem("Port", "(?:\[0-5\]?\\d\{0,4\})|(?:6\[0-4\]\\d{3})|(?:65\[0-4\]\\d{2})|(?:655\[0-2\]\\d)|(?:6553\[0-5\])");
	ui->comboBox_MatchRules->addItem("IP(v4)", "(?:(?:(?:25\[0-5\])|(?:2\[0-4\]\\d)|(?:\[0-1\]?\\d?\\d))\.)\{3\}(?:(?:25\[0-5\])|(?:2\[0-4\]\\d)|(?:\[0-1\]?\\d?\\d))");
	ui->comboBox_MatchRules->addItem("InternationAddress(v4)", "((?:(?:(?:25\[0-5\])|(?:2\[0-4\]\\d)|(?:\[0-1\]?\\d?\\d))\.)\{3\}(?:(?:25\[0-5\])|(?:2\[0-4\]\\d)|(?:\[0-1\]?\\d?\\d))):((?:\[0-5\]?\\d\{0,4\})|(?:6\[0-4\]\\d{3})|(?:65\[0-4\]\\d{2})|(?:655\[0-2\]\\d)|(?:6553\[0-5\]))");
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
    std::regex regex(match_rules);
		//if(regex.is_valid())
		{
      std::smatch smatch_content;
			if (std::regex_match(match_content,smatch_content,regex))
			{//匹配成功(完全匹配)
				QString message_content =  "Match Success!\n";
        /*
				QStringList content_captured = regex.capturedTexts();
				for (auto it_content_captured= content_captured.begin();it_content_captured!= content_captured.end();++it_content_captured)
				{
					message_content += *it_content_captured + "\n";
				}
        */
				CustomMessageBox::information(this, "Information", message_content);
			}
			else
			{//匹配失败
				CustomMessageBox::information(this, "Information", "Match Failed!");
			}
		}
		//else
		{//正则表达式非法

		}
	}
	else
	{//正则表达式和匹配内容不能为空
    CustomMessageBox::information(this, "Information", "empty input");
	}
}
