#include "stdafx.h"

#include "IDLFileDefinitionInformation.h"

#include <TopicDefinition.h>

#include "ui_IDLFileDefinitionInformation.h"

#include "IDLFileDefinition.h"
#include "EnumeratedDataType.h"
#include "StructuredDataType.h"

#include <QStandardItemModel>

IDLFileDefinitionInformation::IDLFileDefinitionInformation(QWidget* parent /*= nullptr*/):
  QWidget(parent),
  ui(new Ui::IDLFileDefinitionInformation())
{
  ui->setupUi(this);

  if(QStandardItemModel* model = new QStandardItemModel(this))
  {
    model->setHorizontalHeaderLabels(QStringList() << QString::fromUtf8("主题名称") << QString::fromUtf8("对应结构体"));

    ui->tableView->setModel(model);
  }
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
  this->file_definition_weak_ptr = file_definition_shared_ptr;

  if(file_definition_shared_ptr)
  {
    //显示
    this->showName();
    this->showCompleteName();
    this->showFileReferences();
    this->showChildDataTypeDefinition();
    this->showTopicDefinition();
  }
  else
  {
    showIDLFileDefinitionInformation(boost::make_shared<IDLFileDefinition>());
  }
}

void IDLFileDefinitionInformation::showName()
{
  if(const boost::shared_ptr<IDLFileDefinition> file_definition_shared_ptr = this->file_definition_weak_ptr.lock())
  {
    const QString& current_file_name = QString::fromStdString(file_definition_shared_ptr->getName());

    ui->lineEdit_FileName->setText(current_file_name);
    ui->lineEdit_FileName->setEnabled(false);
  }
}

void IDLFileDefinitionInformation::showCompleteName()
{
  if(const boost::shared_ptr<IDLFileDefinition> file_definition_shared_ptr = this->file_definition_weak_ptr.lock())
  {
    const QString& current_file_complete_name = QString::fromStdString(file_definition_shared_ptr->getFilePath());

    ui->lineEdit_FileCompleteName->setText(current_file_complete_name);
    ui->lineEdit_FileCompleteName->setEnabled(false);
  }
}

void IDLFileDefinitionInformation::showFileReferences()
{
  ui->comboBox_2->clear();

  if(const boost::shared_ptr<IDLFileDefinition> file_definition_shared_ptr = this->file_definition_weak_ptr.lock())
  {
    const std::vector<boost::shared_ptr<IDLFileDefinition>>& file_references = file_definition_shared_ptr->getFileReferences();
    std::for_each(file_references.begin(),file_references.end(),[&](boost::shared_ptr<IDLFileDefinition> file_reference_definition_shared_ptr)
    {
      if(file_reference_definition_shared_ptr)
      {
        const std::string& file_reference_complete_path = file_reference_definition_shared_ptr->getFilePath();

        ui->comboBox_2->addItem(QString::fromStdString(file_reference_complete_path),QVariant::fromValue<boost::shared_ptr<IDLFileDefinition>>(file_reference_definition_shared_ptr));
      }
    });
  }
}

void IDLFileDefinitionInformation::showChildDataTypeDefinition()
{
  ui->comboBox_DataTypeDefinition->clear();

  if(const boost::shared_ptr<IDLFileDefinition> file_definition_shared_ptr = this->file_definition_weak_ptr.lock())
  {
    const std::vector<boost::weak_ptr<EnumeratedDataType>> vector_enumerated_data_type = file_definition_shared_ptr->collectEnumeratedDataType();
    //const std::vector<boost::weak_ptr<EnumeratedDataType>> vector_enumerated_data_type=package_shared_ptr->getAvailableEnumeratedDataType();
    const std::vector<boost::weak_ptr<StructuredDataType>> vector_structured_data_type = file_definition_shared_ptr->collectStructuredDataType();
    //const std::vector<boost::weak_ptr<StructuredDataType>> vector_structured_data_type=package_shared_ptr->getAvailableStructuredDataType();

    if(!vector_enumerated_data_type.empty())
    {
      ui->comboBox_DataTypeDefinition->addItem(QString::fromStdString("枚举"));

      std::for_each(vector_enumerated_data_type.begin(),vector_enumerated_data_type.end(),[&](const boost::weak_ptr<EnumeratedDataType> enumerated_data_type_weak_ptr)
      {
        if(boost::shared_ptr<EnumeratedDataType> enumerated_data_type_shared_ptr = enumerated_data_type_weak_ptr.lock())
        {
          ui->comboBox_DataTypeDefinition->addItem(QApplication::style()->standardIcon(QStyle::SP_TrashIcon),QString::fromStdString(enumerated_data_type_shared_ptr->getCompleteName()),QVariant::fromValue<boost::weak_ptr<EnumeratedDataType>>(enumerated_data_type_shared_ptr));
        }
      });
    }
    if(!vector_structured_data_type.empty())
    {
      ui->comboBox_DataTypeDefinition->addItem(QString::fromStdString("结构体"));

      std::for_each(vector_structured_data_type.begin(),vector_structured_data_type.end(),[&](const boost::weak_ptr<StructuredDataType> structured_data_type_weak_ptr)
      {
        if(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr = structured_data_type_weak_ptr.lock())
        {
          ui->comboBox_DataTypeDefinition->addItem(QApplication::style()->standardIcon(QStyle::SP_FileIcon),QString::fromStdString(structured_data_type_shared_ptr->getCompleteName()),QVariant::fromValue<boost::weak_ptr<StructuredDataType>>(structured_data_type_shared_ptr));
        }
      });
    }
  }
}

void IDLFileDefinitionInformation::showTopicDefinition()
{
  if(const boost::shared_ptr<IDLFileDefinition> file_definition_shared_ptr = this->file_definition_weak_ptr.lock())
  {
    if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model()))
    {
      const std::vector<boost::shared_ptr<TopicDefinition>>& topics = file_definition_shared_ptr->getTopicDefinitions();
      std::for_each(topics.begin(),topics.end(),[&](const boost::shared_ptr<TopicDefinition>& topic_definition_shared_ptr)
      {
        if(topic_definition_shared_ptr)
        {
          const std::string& topic_name = topic_definition_shared_ptr->getName();
          const std::string& topic_structure_complete_name = topic_definition_shared_ptr->getStructureCompleteName();

          QList<QStandardItem*> items;

          QStandardItem* item_topic_name = new QStandardItem(QString::fromStdString(topic_definition_shared_ptr->getName()));
          QStandardItem* item_topic_structure_complete_name = new QStandardItem(QString::fromStdString(topic_definition_shared_ptr->getStructureCompleteName()));

          items << item_topic_name << item_topic_structure_complete_name;

          model->appendRow(items);
        }
      });
    }
  }
}
