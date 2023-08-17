#include "PortScanner.h"
#include "ui_PortScanner.h"

#include <BasicUIFramework/CustomControls/CustomWindowTitleBar.h>
#include <BasicUIFramework/CustomControls/CustomMessageBox.h>

PortScanner::PortScanner(QWidget* parent,Qt::WindowFlags flags):
  QWidget(parent,flags),
  ui(new Ui::PortScanner())
{
	ui->setupUi(this);

  if(QLayout* default_layout = this->layout())
  {
    default_layout->setMenuBar(new CustomWindowTitleBar(this));
  }
}

PortScanner::~PortScanner()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void PortScanner::on_pushButton_DoScanning_clicked()
{
  CustomMessageBox::information(this,"提示","开始扫描");
}
