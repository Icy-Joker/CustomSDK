#pragma once

#ifndef __REGULAREXPRESSIONVALIDATOR_H__
# define __REGULAREXPRESSIONVALIDATOR_H__

#include <QWidget>

namespace Ui
{
  class RegularExpressionValidator;
}
struct RegularExpressionValidatorPrivate;

class RegularExpressionValidator : public QWidget
{
  Q_OBJECT
public:
  explicit RegularExpressionValidator(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
  ~RegularExpressionValidator();
public:
protected:
private slots:
  void on_lineEdit_RegularExpression_editingFinished();
  void on_comboBox_MatchRules_activated(int index);
  void on_pushButton_Validate_clicked();
private:
  RegularExpressionValidatorPrivate* _p;
  Ui::RegularExpressionValidator* ui;
};

#endif // !__REGULAREXPRESSIONVALIDATOR_H__
