#include "stdafx.h"

#include "IDLFileDefinitionInformation.h"
#include "ui_IDLFileDefinitionInformation.h"

#include "IDLFileDefinition.h"

IDLFileDefinitionInformation::IDLFileDefinitionInformation(QWidget* parent /*= nullptr*/):
  QWidget(parent),
  ui(new Ui::IDLFileDefinitionInformation())
{
  ui->setupUi(this);
}

IDLFileDefinitionInformation::~IDLFileDefinitionInformation()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void IDLFileDefinitionInformation::showIDLFileDefinitionInformation(const boost::shared_ptr<IDLFileDefinition>& file_definition_shared_ptr)
{
}
