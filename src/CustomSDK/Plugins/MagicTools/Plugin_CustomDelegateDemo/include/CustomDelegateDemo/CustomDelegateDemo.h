#pragma once

#ifndef __CUSTOMDELEGATEDEMO_H__
# define __CUSTOMDELEGATEDEMO_H__

#include <QMainWindow>

namespace Ui
{
  class CustomDelegateDemo;
}

class CustomDelegateDemo : public QMainWindow
{
  Q_OBJECT
public:
  explicit CustomDelegateDemo(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~CustomDelegateDemo() override;
private:
  Ui::CustomDelegateDemo* ui;
};

#endif // !__CUSTOMDELEGATEDEMO_H__
