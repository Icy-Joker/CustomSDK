#pragma once

#ifndef __CUSTOMWINDOWTITLEBAR_H__
# define __CUSTOMWINDOWTITLEBAR_H__

#include <QWidget>

namespace Ui
{
  class CustomWindowTitleBar;
}

class BasicUIFramework_API CustomWindowTitleBar : public QWidget
{
  Q_OBJECT
private:
  CustomWindowTitleBar();
public:
  explicit CustomWindowTitleBar(QWidget* parent,Qt::WindowFlags flags = Qt::WindowFlags());
  ~CustomWindowTitleBar();
protected:
  bool eventFilter(QObject *watched, QEvent *event);
protected:
  void mouseMoveEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
private slots:
  void on_toolButton_Minimize_clicked();
  void on_toolButton_Resize_clicked();
  void on_toolButton_Close_clicked();
private:
  Ui::CustomWindowTitleBar* ui;
};

#endif //!__CUSTOMWINDOWTITLEBAR_H__
