#include "stdafx.h"
#include "EnumeratedDataTypeInformation.h"
#include "ui_EnumeratedDataTypeInformation.h"
#include "EnumeratedDataType.h"

EnumeratedDataTypeInformation::EnumeratedDataTypeInformation(QWidget* parent):
  QWidget(parent),
  ui(new Ui::EnumeratedDataTypeInformation())
{
  ui->setupUi(this);

  QStandardItemModel* model_member_table = new QStandardItemModel(this);
}

EnumeratedDataTypeInformation::~EnumeratedDataTypeInformation()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void EnumeratedDataTypeInformation::showEnumeratedDataTypeInformation(const boost::shared_ptr<EnumeratedDataType>& enumerated_data_type_shared_ptr)
{
  if(enumerated_data_type_shared_ptr)
  {
    this->enumerated_data_type_weak_ptr = enumerated_data_type_shared_ptr;

    //获取数据
    const QString& current_enumerated_data_type_name = QString::fromStdString(enumerated_data_type_shared_ptr->getName());
    const QString& current_enumerated_data_type_complete_name = QString::fromStdString(enumerated_data_type_shared_ptr->getCompleteName());
    {
      //显示
      ui->lineEdit_EnumeratedDataTypeName->setText(current_enumerated_data_type_name);
      ui->lineEdit_EnumeratedDataTypeCompleteName->setText(current_enumerated_data_type_complete_name);
    }
  }
}

void EnumeratedDataTypeInformation::on_lineEdit_EnumeratedDataTypeName_textChanged(const QString& current_enumerated_data_type_name)
{
  if(boost::shared_ptr<EnumeratedDataType> enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    const QString& parent_package_complete_name = QString::fromStdString(enumerated_data_type_shared_ptr->getParentNamespaceCompleteName());
    const QString& current_enumerated_data_type_complete_name = parent_package_complete_name.isEmpty() ? current_enumerated_data_type_name : QString("%1::%2").arg(parent_package_complete_name).arg(current_enumerated_data_type_name);

    ui->lineEdit_EnumeratedDataTypeCompleteName->setText(current_enumerated_data_type_complete_name);
  }
}
