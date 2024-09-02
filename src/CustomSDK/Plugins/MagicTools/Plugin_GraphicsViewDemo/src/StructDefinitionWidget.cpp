#include "stdafx.h"

#include "StructDefinitionWidget.h"
#include "ui_StructDefinitionWidget.h"

StructDefinitionWidget::StructDefinitionWidget(QWidget *parent /*= nullptr*/):
  QWidget(parent),
  ui(new Ui::StructDefinitionWidget())
{
  ui->setupUi(this);
}

StructDefinitionWidget::~StructDefinitionWidget()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}
