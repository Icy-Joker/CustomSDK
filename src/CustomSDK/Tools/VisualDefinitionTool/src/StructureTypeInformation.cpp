#include "stdafx.h"
#include "StructureTypeInformation.h"
#include "ui_StructureTypeInformation.h"

#include "StructureType.h"
#include "ProjectDefinition.h"
#include "GlobalProjectManager.h"
#include "StructureMemberDelegate.h"

#include <QStandardItemModel>

StructureTypeInformation::StructureTypeInformation(QWidget* parent):
  QWidget(parent),
  ui(new Ui::StructureTypeInformation())
{
  ui->setupUi(this);

  ui->tableView_MemberElements->setModel(new QStandardItemModel(this));
  qobject_cast<QStandardItemModel*>(ui->tableView_MemberElements->model())->setHorizontalHeaderLabels(QStringList()
    << QString::fromUtf8("标识符")
    << QString::fromUtf8("类型名称")
    << QString::fromUtf8("是否重复(vector)")
    << QString::fromUtf8("默认值")
    << QString::fromUtf8("描述"));

  ui->tableView_MemberElements->setItemDelegate(new StructureMemberDelegate(this));
}

StructureTypeInformation::~StructureTypeInformation()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void StructureTypeInformation::showStructureTypeInformation(const boost::shared_ptr<StructureType>& structure_type_shared_ptr)// NOLINT(misc-no-recursion)
{
  if(structure_type_shared_ptr)
  {
    // 记录
    this->structured_data_type_weak_ptr = structure_type_shared_ptr;
    // 显示
    this->showName();
    this->showCompleteName();
    this->showParentStructureType();
    this->showMemberElementInformation();
  }
  else
  {
    showStructureTypeInformation(boost::make_shared<StructureType>());
  }
}

void StructureTypeInformation::showName() const
{
  if(const boost::shared_ptr<StructureType>& structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    const QString& current_structured_data_type_name = QString::fromStdString(structured_data_type_shared_ptr->getName());

    ui->lineEdit_StructureTypeName->setText(current_structured_data_type_name);
  }
}

void StructureTypeInformation::showCompleteName() const
{
  if(const boost::shared_ptr<StructureType>& structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    const QString& current_structured_data_type_complete_name = QString::fromStdString(structured_data_type_shared_ptr->getCompleteName());

    ui->lineEdit_StructureTypeCompleteName->setText(current_structured_data_type_complete_name);
  }
}

void StructureTypeInformation::showParentStructureType() const
{
  ui->comboBox->clear();

  if(const boost::shared_ptr<StructureType>& structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    if(auto project_shared_ptr = GlobalProjectManager::getInstance()->getCurrentProject())
    {
      const std::list<boost::shared_ptr<StructureType>>& structure_definitions = project_shared_ptr->getAllStructureTypeDefinitions();
      std::for_each(structure_definitions.begin(),structure_definitions.end(),[&](const boost::weak_ptr<StructureType>& structured_data_type_weak_ptr_existed)
      {
        if(boost::shared_ptr<StructureType> structured_data_type_shared_ptr_existed = structured_data_type_weak_ptr_existed.lock())
        {
          const std::string structure_definition_complete_name = structured_data_type_shared_ptr_existed->getCompleteName();

          ui->comboBox->addItem(QString::fromStdString(structure_definition_complete_name),QVariant::fromValue(structured_data_type_shared_ptr_existed));
        }
      });
    }
  }
}

void StructureTypeInformation::showMemberElementInformation() const
{
  if(const boost::shared_ptr<StructureType> structured_data_type_shared_ptr = this->structured_data_type_weak_ptr.lock())
  {
    if(auto model = qobject_cast<QStandardItemModel*>(ui->tableView_MemberElements->model()))
    {
      model->setRowCount(0);

      const std::vector<boost::shared_ptr<StructureMember>>& member_elements = structured_data_type_shared_ptr->getCompleteMemberElements();
      std::for_each(member_elements.begin(),member_elements.end(),[&](const boost::shared_ptr<StructureMember>& structure_member)
      {
        QList<QStandardItem*> items;

        auto item_member_name = new QStandardItem(QString::fromStdString(structure_member->identifier));// NOLINT
        auto item_member_type = new QStandardItem(QString::fromStdString(structure_member->data_type_name));// NOLINT
        auto item_member_repeatable = new QStandardItem(structure_member->repeatable ? QString::fromUtf8("是") : QString::fromUtf8("否"));// NOLINT
        auto item_member_default_value = new QStandardItem(QString::fromStdString(structure_member->default_value));// NOLINT
        auto item_member_annotation = new QStandardItem(QString::fromStdString(structure_member->annotation));// NOLINTw

        items
            << item_member_name
            << item_member_type
            << item_member_default_value
            << item_member_repeatable
            << item_member_annotation;

        model->appendRow(items);
      });
    }
  }
}

void StructureTypeInformation::on_lineEdit_StructureTypeName_textChanged(const QString& current_structured_data_type_name) const
{
  if(boost::shared_ptr<StructureType> structured_data_type_shared_ptr = structured_data_type_weak_ptr.lock())
  {
    const QString& parent_package_complete_name = QString::fromStdString(structured_data_type_shared_ptr->getParentNamespaceCompleteName());
    const QString& current_structured_data_type_complete_name = parent_package_complete_name.isEmpty() ? current_structured_data_type_name : QString("%1::%2").arg(parent_package_complete_name,current_structured_data_type_name);

    ui->lineEdit_StructureTypeCompleteName->setText(current_structured_data_type_complete_name);
  }
}
