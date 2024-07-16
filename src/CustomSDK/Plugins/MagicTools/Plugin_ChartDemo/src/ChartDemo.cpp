#include "stdafx.h"

#include "ChartDemo/ChartDemo.h"
#include "ui_ChartDemo.h"

ChartDemo::ChartDemo(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::ChartDemo())
{
  ui->setupUi(this);
}

ChartDemo::~ChartDemo()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}
