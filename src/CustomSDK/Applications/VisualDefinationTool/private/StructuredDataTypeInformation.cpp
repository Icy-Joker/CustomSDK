#include "stdafx.h"
#include "StructuredDataTypeInformation.h"
#include "ui_StructuredDataTypeInformation.h"

#include "StructuredDataType.h"

StructuredDataTypeInformation::StructuredDataTypeInformation(QWidget* parent):
  QWidget(parent),
  ui(new Ui::StructuredDataTypeInformation())
{
  initializeUI();
  initializeFunction();
}

StructuredDataTypeInformation::~StructuredDataTypeInformation()
{
  if(ui)
  {
    delete ui;
    ui=nullptr;
  }
}

void StructuredDataTypeInformation::showStructuredDataTypeInformation(const boost::shared_ptr<StructuredDataType>& structured_data_type_shared_ptr)
{
  this->structured_data_type_weak_ptr = structured_data_type_shared_ptr;
  if(structured_data_type_shared_ptr)
  {
    //获取数据
    const QString& current_structured_data_type_name=QString::fromStdString(structured_data_type_shared_ptr->getStructuredDataTypeName());
    {//显示
      ui->lineEdit_StructuredDataTypeName->setText(current_structured_data_type_name);
    }
  }
  else
  {
    showStructuredDataTypeInformation(boost::make_shared<StructuredDataType>());
  }
}

void StructuredDataTypeInformation::initializeUI()
{
  ui->setupUi(this);
}

void StructuredDataTypeInformation::initializeFunction()
{

}

void StructuredDataTypeInformation::on_lineEdit_StructuredDataTypeName_textChanged(const QString& current_structured_data_type_name)
{
  if(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr = structured_data_type_weak_ptr.lock())
  {
    const QString& parent_package_complete_name = QString::fromStdString(structured_data_type_shared_ptr->getParentPackageCompleteName());
    const QString& current_structured_data_type_complete_name= parent_package_complete_name.isEmpty() ? current_structured_data_type_name : QString("%1::%2").arg(parent_package_complete_name).arg(current_structured_data_type_name);

    ui->lineEdit_StructuredDataTypeCompleteName->setText(current_structured_data_type_complete_name);
  }
}
