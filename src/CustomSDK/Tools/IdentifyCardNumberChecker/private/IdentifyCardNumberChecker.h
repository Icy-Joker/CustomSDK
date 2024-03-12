#pragma once

#ifndef __IDENTIFYCARDNUMBERCHECKER_H__
# define __IDENTIFYCARDNUMBERCHECKER_H__

#include <QWidget>

namespace Ui
{
  class IdentifyCardNumberChecker;
}

class IdentifyCardNumberChecker : public QWidget
{
  Q_OBJECT
public:
  explicit IdentifyCardNumberChecker(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~IdentifyCardNumberChecker();
private slots:
  void on_pushButton_Check_clicked();
private:
  Ui::IdentifyCardNumberChecker* ui;
};

#endif // !__IDENTIFYCARDNUMBERCHECKER_H__
