#pragma once

#include <QWidget>

namespace Ui
{
	class RegularExpressionValidator;
}

class RegularExpressionValidator_API RegularExpressionValidator : public QWidget
{
	Q_OBJECT
public:
	explicit RegularExpressionValidator(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
	~RegularExpressionValidator();
private slots:
	void on_lineEdit_RegularExpression_editingFinished();
	void on_comboBox_MatchRules_activated(int index);
	void on_pushButton_Validate_clicked();
private:
	Ui::RegularExpressionValidator* ui;
};
