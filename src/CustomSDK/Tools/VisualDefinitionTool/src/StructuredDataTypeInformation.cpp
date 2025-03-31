#include "stdafx.h"
#include "StructuredDataTypeInformation.h"
#include "ui_StructuredDataTypeInformation.h"

#include "CommonStructDefinition.h"
#include "StructuredDataType.h"

#include <QStandardItemModel>

StructuredDataTypeInformation::StructuredDataTypeInformation(QWidget* parent):
  QWidget(parent),
  ui(new Ui::StructuredDataTypeInformation())
{
  ui->setupUi(this);

  QStandardItemModel* model = new QStandardItemModel(this);
  {
    model->setHorizontalHeaderLabels(QStringList() << QString::fromUtf8("标识符") << QString::fromUtf8("类型名称") << QString::fromUtf8("值") << QString::fromUtf8("描述"));

    ui->tableView_MemberElements->setModel(model);
  }
}

StructuredDataTypeInformation::~StructuredDataTypeInformation()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void StructuredDataTypeInformation::showStructuredDataTypeInformation(const boost::shared_ptr<StructuredDataType>& structured_data_type_shared_ptr)
{
  this->structured_data_type_weak_ptr = structured_data_type_shared_ptr;

  if(structured_data_type_shared_ptr)
  {
    //显示
    this->showName();
    this->showCompleteName();
    this->showParentStructuredDataType();
    this->showMemberElementInformation();
  }
  else
  {
    showStructuredDataTypeInformation(boost::make_shared<StructuredDataType>());
  }
}

void StructuredDataTypeInformation::showName()
{
  if(const boost::shared_ptr<StructuredDataType>& structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    const QString& current_structured_data_type_name = QString::fromStdString(structured_data_type_shared_ptr->getName());

    ui->lineEdit_StructuredDataTypeName->setText(current_structured_data_type_name);
  }
}

void StructuredDataTypeInformation::showCompleteName()
{
  if(const boost::shared_ptr<StructuredDataType>& structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    const QString& current_structured_data_type_complete_name = QString::fromStdString(structured_data_type_shared_ptr->getCompleteName());

    ui->lineEdit_StructuredDataTypeCompleteName->setText(current_structured_data_type_complete_name);
  }
}

void StructuredDataTypeInformation::showParentStructuredDataType()
{
  ui->comboBox->clear();

  if(const boost::shared_ptr<StructuredDataType>& structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    std::vector<boost::weak_ptr<StructuredDataType>> structure_definitions = structured_data_type_shared_ptr->getAvailableStructuredDataType();
    std::for_each(structure_definitions.begin(),structure_definitions.end(),[&](boost::weak_ptr<StructuredDataType> structured_data_type_weak_ptr_existed)
    {
      if(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr_existed = structured_data_type_weak_ptr_existed.lock())
      {
        const std::string structure_definition_complete_name = structured_data_type_shared_ptr_existed->getCompleteName();

        ui->comboBox->addItem(QString::fromStdString(structure_definition_complete_name),QVariant::fromValue(structured_data_type_shared_ptr_existed));
      }
    });
  }
}

void StructuredDataTypeInformation::showMemberElementInformation()
{
  if(const boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView_MemberElements->model()))
    {
      model->setRowCount(0);

      const std::vector<boost::shared_ptr<SingleElement>>& member_elements = structured_data_type_shared_ptr->getCompleteMemberElements();
      std::for_each(member_elements.begin(),member_elements.end(),[&](const boost::shared_ptr<SingleElement>& member_element)
      {
        QList<QStandardItem*> items;

        QStandardItem* item_member_name = new QStandardItem(QString::fromStdString(member_element->identifier));
        QStandardItem* item_member_type = new QStandardItem(QString::fromStdString(member_element->data_type_name));
        QStandardItem* item_member_default_value = new QStandardItem(QString::fromStdString(member_element->annotation));
        QStandardItem* item_member_annotation = new QStandardItem(QString::fromStdString(member_element->annotation));

        items << item_member_name << item_member_type << item_member_default_value << item_member_annotation;

        model->appendRow(items);
      });
    }
  }
}

void StructuredDataTypeInformation::on_lineEdit_StructuredDataTypeName_textChanged(const QString& current_structured_data_type_name)
{
  if(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr = structured_data_type_weak_ptr.lock())
  {
    const QString& parent_package_complete_name = QString::fromStdString(structured_data_type_shared_ptr->getParentNamespaceCompleteName());
    const QString& current_structured_data_type_complete_name = parent_package_complete_name.isEmpty() ? current_structured_data_type_name : QString("%1::%2").arg(parent_package_complete_name).arg(current_structured_data_type_name);

    ui->lineEdit_StructuredDataTypeCompleteName->setText(current_structured_data_type_complete_name);
  }
}
