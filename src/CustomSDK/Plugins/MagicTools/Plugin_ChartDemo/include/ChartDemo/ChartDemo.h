#pragma once

#ifndef __CHARTDEMO_H__
# define __CHARTDEMO_H__

#include <QMainWindow>

namespace Ui
{
  class ChartDemo;
}

class ChartDemo : public QMainWindow
{
  Q_OBJECT
public:
  explicit ChartDemo(QWidget *parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~ChartDemo() override;
private:
  Ui::ChartDemo *ui;
};

#endif // !__CHARTDEMO_H__
