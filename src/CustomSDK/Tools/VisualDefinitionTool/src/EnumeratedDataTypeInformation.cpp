#include "stdafx.h"
#include "EnumeratedDataTypeInformation.h"
#include "ui_EnumeratedDataTypeInformation.h"

#include "CommonStructDefinition.h"
#include "EnumeratedDataType.h"

#include <QStandardItemModel>

EnumeratedDataTypeInformation::EnumeratedDataTypeInformation(QWidget* parent):
  QWidget(parent),
  ui(new Ui::EnumeratedDataTypeInformation())
{
  ui->setupUi(this);

  QStandardItemModel* model = new QStandardItemModel(this);
  {
    model->setHorizontalHeaderLabels(QStringList() << QString::fromUtf8("标识符") << QString::fromUtf8("类型名称") << QString::fromUtf8("值") << QString::fromUtf8("描述"));

    ui->tableView_MemberElements->setModel(model);
  }
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
  this->enumerated_data_type_weak_ptr = enumerated_data_type_shared_ptr;

  if(enumerated_data_type_shared_ptr)
  {
    //显示
    this->showName();
    this->showCompleteName();
    this->showMemberElementInformation();
  }
  else
  {
    this->showEnumeratedDataTypeInformation(boost::make_shared<EnumeratedDataType>());
  }
}

void EnumeratedDataTypeInformation::showName()
{
  if(const boost::shared_ptr<EnumeratedDataType>& enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    const QString& current_enumerated_data_type_name = QString::fromStdString(enumerated_data_type_shared_ptr->getName());

    ui->lineEdit_EnumeratedDataTypeName->setText(current_enumerated_data_type_name);
  }
}

void EnumeratedDataTypeInformation::showCompleteName()
{
  if(const boost::shared_ptr<EnumeratedDataType>& enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    const QString& current_enumerated_data_type_complete_name = QString::fromStdString(enumerated_data_type_shared_ptr->getCompleteName());

    ui->lineEdit_EnumeratedDataTypeCompleteName->setText(current_enumerated_data_type_complete_name);
  }
}

void EnumeratedDataTypeInformation::showMemberElementInformation()
{
  if(const boost::shared_ptr<EnumeratedDataType>& enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView_MemberElements->model()))
    {
      model->setRowCount(0);

      const std::vector<boost::shared_ptr<SingleElement>>& member_elements = enumerated_data_type_shared_ptr->getMemberElements();
      std::for_each(member_elements.begin(),member_elements.end(),[&](const boost::shared_ptr<SingleElement>& member_element)
      {
        QList<QStandardItem*> items;

        QStandardItem* item_member_name = new QStandardItem(QString::fromStdString(member_element->identifier));
        QStandardItem* item_member_type = new QStandardItem(QString::fromStdString(member_element->data_type_name));
        QStandardItem* item_member_default_value = new QStandardItem(QString::fromStdString(member_element->default_value));
        QStandardItem* item_member_annotation = new QStandardItem(QString::fromStdString(member_element->annotation));

        items << item_member_name << item_member_type << item_member_default_value << item_member_annotation;

        model->appendRow(items);
      });
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
