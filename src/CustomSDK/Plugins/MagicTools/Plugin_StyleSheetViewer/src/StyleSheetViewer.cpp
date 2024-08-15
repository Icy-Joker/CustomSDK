#include "stdafx.h"

#include "StyleSheetViewer/StyleSheetViewer.h"
#include "ui_StyleSheetViewer.h"

#include <QMessageBox>
#include <QStyle>

StyleSheetViewer::StyleSheetViewer(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::StyleSheetViewer())
{
  ui->setupUi(this);
}

StyleSheetViewer::~StyleSheetViewer()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void StyleSheetViewer::on_pushButton_ShowInformationMessageBox_clicked()
{
  QMessageBox::information(this,"Information","This is an information message box");
}

void StyleSheetViewer::on_pushButton_ShowWarningMessageBox_clicked()
{
  QMessageBox::warning(this,"Warning","This is a warning message box");
}

void StyleSheetViewer::on_pushButton_ShowQuestionMessageBox_clicked()
{
  QMessageBox::question(this,"Question","This is a question message box");
}

void StyleSheetViewer::on_pushButton_ShowErrorMessageBox_clicked()
{
  QMessageBox::critical(this,"Error","This is an error message box");
}

void StyleSheetViewer::keyPressEvent(QKeyEvent* event)
{
  if(QKeySequence(QKeySequence::Save).matches(event->key() | event->modifiers()))
  {
    if(this->focusWidget() == ui->plainTextEdit_StyleSheet)
    {
      this->style()->unpolish(this);

      this->setStyleSheet(ui->plainTextEdit_StyleSheet->toPlainText());

      this->style()->polish(this);
    }
  }

  QMainWindow::keyPressEvent(event);
}
