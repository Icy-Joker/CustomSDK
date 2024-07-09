#include "stdafx.h"

#include "NetworkTool/NetworkTool.h"
#include "ui_NetworkTool.h"

NetworkTool::NetworkTool(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::NetworkTool())
{
  ui->setupUi(this);
}

NetworkTool::~NetworkTool()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}
