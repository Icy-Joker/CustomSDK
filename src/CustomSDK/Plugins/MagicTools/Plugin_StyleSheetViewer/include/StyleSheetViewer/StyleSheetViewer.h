#pragma once

#ifndef __STYLESHEETVIEWER_H__
# define __STYLESHEETVIEWER_H__

#include <QMainWindow>

namespace Ui
{
  class StyleSheetViewer;
}

class StyleSheetViewer : public QMainWindow
{
  Q_OBJECT
public:
  explicit StyleSheetViewer(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~StyleSheetViewer() override;
private slots:
  void on_pushButton_ShowInformationMessageBox_clicked();
  void on_pushButton_ShowWarningMessageBox_clicked();
  void on_pushButton_ShowQuestionMessageBox_clicked();
  void on_pushButton_ShowErrorMessageBox_clicked();
protected:
  void keyPressEvent(QKeyEvent* event) override;
private:
  Ui::StyleSheetViewer* ui;
};

#endif // !__STYLESHEETVIEWER_H__
