#include "stdafx.h"

#include "VisualDesigner.h"
#include "ui_VisualDesigner.h"

#include "CustomItemModel.h"
#include "DataTypeDefinitions.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

Q_DECLARE_METATYPE(boost::weak_ptr<NamespaceDefinition>)

VisualDesigner::VisualDesigner(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
    QWidget(parent),
    ui(new Ui::VisualDesigner())
{
  ui->setupUi(this);

  if(CustomItemModel* model = new CustomItemModel(this))
  {
    ui->treeView_Project->setModel(model);

    connect(ui->treeView_Project->selectionModel(),&QItemSelectionModel::currentRowChanged,[=](const QModelIndex& index_current,const QModelIndex& index_previous)
    {
      if(index_current.isValid())
      {
        QVariant variant_user_role = model->data(index_current,Qt::UserRole);
        if(variant_user_role.isValid())
        {
          if(boost::shared_ptr<NamespaceDefinition> namespace_definition_ptr = boost::dynamic_pointer_cast<NamespaceDefinition>(variant_user_role.value<boost::weak_ptr<NamespaceDefinition>>().lock()))
          {
            if(boost::shared_ptr<EnumerationDefinition> enumeration_definition_ptr = boost::dynamic_pointer_cast<EnumerationDefinition>(namespace_definition_ptr))
            {
              ui->stackedWidget->setCurrentWidget(ui->page);
            }
            else if(boost::shared_ptr<StructureDefinition> structure_definition_ptr = boost::dynamic_pointer_cast<StructureDefinition>(namespace_definition_ptr))
            {
              ui->stackedWidget->setCurrentWidget(ui->page_2);
            }
          }
        }
      }
    });
  }
  doLoadFile("");
}

VisualDesigner::~VisualDesigner()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

boost::shared_ptr<StructureDefinition> structure_definition_ptr = nullptr;
boost::shared_ptr<EnumerationDefinition> enumeration_definition_ptr = nullptr;

void VisualDesigner::doLoadFile(const std::string& file_path)
{
  if(CustomItemModel* model = qobject_cast<CustomItemModel*>(ui->treeView_Project->model()))
  {
    model->clear();

    //试验部分
    {
      if(QStandardItem* item_project_root = new QStandardItem(QString::fromLocal8Bit("当前项目")))
      {
        model->invisibleRootItem()->appendRow(item_project_root);

        if(QStandardItem* item_import_root = new QStandardItem(QString::fromLocal8Bit("引入文件")))
        {
          structure_definition_ptr = boost::make_shared<StructureDefinition>("结构体");
          item_import_root->setData(QVariant::fromValue<boost::weak_ptr<NamespaceDefinition>>(structure_definition_ptr),Qt::UserRole);
          item_project_root->appendRow(item_import_root);
        }
        if(QStandardItem* item_current_root = new QStandardItem(QString::fromLocal8Bit("当前文件")))
        {
          enumeration_definition_ptr = boost::make_shared<EnumerationDefinition>("枚举");
          item_current_root->setData(QVariant::fromValue<boost::weak_ptr<NamespaceDefinition>>(enumeration_definition_ptr),Qt::UserRole);
          item_project_root->appendRow(item_current_root);
        }
      }
    }
  }
}