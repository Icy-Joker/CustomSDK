#include "stdafx.h"
#include "VisualDefinateTool.h"
#include "ui_VisualDefinateTool.h"
#include "CustomItemModel.h"

#include "EnumeratedDataType.h"
#include "StructuredDataType.h"
#include "Package.h"
#include "EnumeratedDataTypeInformation.h"

#include "StructuredDataTypeInformation.h"
#include "PackageInformation.h"

#include <QMenu>
#include <QAction>

#define ITEM_USER_DATA_ROLE Qt::ItemDataRole::UserRole
#define ITEM_TREE_NODE_TYPE_ROLE ITEM_USER_DATA_ROLE + 1

enum TREE_NODE_TYPE
{
  UNKNOWN,
  PACKAGE,
  ENUMERATEDDATATYPE,
  STRUCTUREDDATATYPE,
  PACKAGE_GROUP,
  ENUMERATEDDATATYPE_GROUP,
  STRUCTUREDDATATYPE_GROUP
};

Q_DECLARE_METATYPE(boost::shared_ptr<EnumeratedDataType>)
Q_DECLARE_METATYPE(boost::shared_ptr<StructuredDataType>)
Q_DECLARE_METATYPE(boost::shared_ptr<Package>)

Q_DECLARE_METATYPE(TREE_NODE_TYPE)

VisualDefinateTool::VisualDefinateTool(QWidget* parent):
  QWidget(parent),
  ui(new Ui::VisualDefinateTool())
{
  initializeUI();
  initializeFunction();
}

VisualDefinateTool::~VisualDefinateTool()
{
}

void VisualDefinateTool::initializeUI()
{
  ui->setupUi(this);
  
  CustomItemModel* model_parse_tree = new CustomItemModel(this);
  ui->treeView_DefinationParseTree->setModel(model_parse_tree);
}

void VisualDefinateTool::initializeFunction()
{
  connect(ui->treeView_DefinationParseTree->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),this,SLOT(slot_parseTree_currentRowChanged(const QModelIndex&,const QModelIndex&)));

  {//测试
    appendPackage(((QStandardItemModel*)(ui->treeView_DefinationParseTree->model()))->invisibleRootItem());
  }
}

QStandardItem* VisualDefinateTool::appendEnumeratedDataType(QStandardItem* item_group_enumerated_data_type)
{
  QStandardItem* item_enumerated_data_type=nullptr;

  if(item_group_enumerated_data_type)
  {
    item_enumerated_data_type = new QStandardItem();
    item_enumerated_data_type->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::ENUMERATEDDATATYPE),ITEM_TREE_NODE_TYPE_ROLE);

    boost::shared_ptr<EnumeratedDataType> current_enumerated_data_type_shared_ptr=boost::make_shared<EnumeratedDataType>();
    if(QStandardItem* item_parent_package=item_group_enumerated_data_type->parent())
    {
      if(boost::shared_ptr<Package> parent_package_shared_ptr=item_parent_package->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<Package>>())
      {
        current_enumerated_data_type_shared_ptr->setParentPackage(parent_package_shared_ptr);

        parent_package_shared_ptr->appendEnumeratedDataType(current_enumerated_data_type_shared_ptr);
      }
    }
    item_enumerated_data_type->setData(QVariant::fromValue<boost::shared_ptr<EnumeratedDataType>>(current_enumerated_data_type_shared_ptr),ITEM_USER_DATA_ROLE);

    item_group_enumerated_data_type->appendRow(item_enumerated_data_type);
  }

  return item_enumerated_data_type;
}

QStandardItem* VisualDefinateTool::appendStructuredDataType(QStandardItem* item_group_structured_data_type)
{
  QStandardItem* item_structured_data_type=nullptr;

  if(item_group_structured_data_type)
  {
    item_structured_data_type = new QStandardItem();
    item_structured_data_type->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::STRUCTUREDDATATYPE),ITEM_TREE_NODE_TYPE_ROLE);

    boost::shared_ptr<StructuredDataType> current_structured_data_type_shared_ptr=boost::make_shared<StructuredDataType>();
    if(QStandardItem* item_parent_package=item_group_structured_data_type->parent())
    {
      if(boost::shared_ptr<Package> parent_package_shared_ptr=item_parent_package->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<Package>>())
      {
        current_structured_data_type_shared_ptr->setParentPackage(parent_package_shared_ptr);

        parent_package_shared_ptr->appendStructuredDataType(current_structured_data_type_shared_ptr);
      }
    }
    item_structured_data_type->setData(QVariant::fromValue<boost::shared_ptr<StructuredDataType>>(current_structured_data_type_shared_ptr),ITEM_USER_DATA_ROLE);

    item_group_structured_data_type->appendRow(item_structured_data_type);
  }

  return item_structured_data_type;
}

QStandardItem* VisualDefinateTool::appendPackage(QStandardItem* item_group_package)
{
  QStandardItem* item_package=nullptr;

  if(item_group_package)
  {
    item_package = new QStandardItem();
    item_package->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::PACKAGE),ITEM_TREE_NODE_TYPE_ROLE);

    boost::shared_ptr<Package> current_package_shared_ptr=boost::make_shared<Package>();
    if(QStandardItem* item_parent_package=item_group_package->parent())
    {
      if(boost::shared_ptr<Package> parent_package_shared_ptr=item_parent_package->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<Package>>())
      {
        current_package_shared_ptr->setParentPackage(parent_package_shared_ptr);

        parent_package_shared_ptr->appendPackage(current_package_shared_ptr);
      }
    }
    item_package->setData(QVariant::fromValue<boost::shared_ptr<Package>>(current_package_shared_ptr),ITEM_USER_DATA_ROLE);

    {
      QStandardItem* item_group_child_enumerated_data_type=new QStandardItem(QString::fromLocal8Bit("枚举"));
      QStandardItem* item_group_child_structured_data_type=new QStandardItem(QString::fromLocal8Bit("结构体"));
      QStandardItem* item_group_child_package=new QStandardItem(QString::fromLocal8Bit("包空间"));

      item_group_child_enumerated_data_type->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::ENUMERATEDDATATYPE_GROUP),ITEM_TREE_NODE_TYPE_ROLE);
      item_group_child_structured_data_type->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::STRUCTUREDDATATYPE_GROUP),ITEM_TREE_NODE_TYPE_ROLE);
      item_group_child_package->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::PACKAGE_GROUP),ITEM_TREE_NODE_TYPE_ROLE);

      item_package->appendRow(item_group_child_enumerated_data_type);
      item_package->appendRow(item_group_child_structured_data_type);
      item_package->appendRow(item_group_child_package);
    }

    item_group_package->appendRow(item_package);
  }

  return item_package;
}

void VisualDefinateTool::appendEnumeratedDataType()
{
  QModelIndex index_current_selected=ui->treeView_DefinationParseTree->currentIndex();
  if(index_current_selected.isValid())
  {
    if(QStandardItemModel* model_parse_tree = (QStandardItemModel*)ui->treeView_DefinationParseTree->model())
    {
      if(QStandardItem* item_current_selected=model_parse_tree->itemFromIndex(index_current_selected))
      {
        QStandardItem* item_group_enumerated_data_type=nullptr;
        switch(index_current_selected.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>()) 
        {
          case PACKAGE:
          {
            item_group_enumerated_data_type=item_current_selected->child(0);
            break;
          }
          case ENUMERATEDDATATYPE_GROUP:
          {
            item_group_enumerated_data_type=model_parse_tree->itemFromIndex(index_current_selected);
            break;
          }
          default:
          {
            break;
          }
        }

        if(item_group_enumerated_data_type)
        {
          if(QStandardItem* item_enumerated_data_type=appendEnumeratedDataType(item_group_enumerated_data_type))
          {
            ui->treeView_DefinationParseTree->setCurrentIndex(item_enumerated_data_type->index());
          }
        }
      }
    }
  }
};

void VisualDefinateTool::appendStructuredDataType()
{
  QModelIndex index_current_selected=ui->treeView_DefinationParseTree->currentIndex();
  if(index_current_selected.isValid())
  {
    if(QStandardItemModel* model_parse_tree = (QStandardItemModel*)ui->treeView_DefinationParseTree->model())
    {
      if(QStandardItem* item_current_selected=model_parse_tree->itemFromIndex(index_current_selected))
      {
        QStandardItem* item_group_structured_data_type=nullptr;
        switch(index_current_selected.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>()) 
        {
          case PACKAGE:
          {
            item_group_structured_data_type=item_current_selected->child(1);
            break;
          }
          case STRUCTUREDDATATYPE_GROUP:
          {
            item_group_structured_data_type=model_parse_tree->itemFromIndex(index_current_selected);
            break;
          }
          default:
          {
            break;
          }
        }

        if(item_group_structured_data_type)
        {
          if(QStandardItem* item_structured_data_type=appendStructuredDataType(item_group_structured_data_type))
          {
            ui->treeView_DefinationParseTree->setCurrentIndex(item_structured_data_type->index());
          }
        }
      }
    }
  }
};

void VisualDefinateTool::appendPackage()
{
  QModelIndex index_current_selected=ui->treeView_DefinationParseTree->currentIndex();
  if(index_current_selected.isValid())
  {
    if(QStandardItemModel* model_parse_tree = (QStandardItemModel*)ui->treeView_DefinationParseTree->model())
    {
      if(QStandardItem* item_current_selected=model_parse_tree->itemFromIndex(index_current_selected))
      {
        QStandardItem* item_group_package=nullptr;
        switch(index_current_selected.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>()) 
        {
          case PACKAGE:
          {
            item_group_package=item_current_selected->child(2);
            break;
          }
          case PACKAGE_GROUP:
          {
            item_group_package=model_parse_tree->itemFromIndex(index_current_selected);
            break;
          }
          default:
          {
            break;
          }
        }

        if(item_group_package)
        {
          if(QStandardItem* item_package=appendPackage(item_group_package))
          {
            ui->treeView_DefinationParseTree->setCurrentIndex(item_package->index());
          }
        }
      }
    }
  }
};

void VisualDefinateTool::previewDefination()
{
  ui->textBrowser->clear();
  if(QStandardItemModel* model_parse_tree = (QStandardItemModel*)ui->treeView_DefinationParseTree->model())
  {
    if(QStandardItem* item_invisible_root = model_parse_tree->invisibleRootItem())
    {
      if(item_invisible_root->hasChildren())
      {
        if(QStandardItem* item_global_package = item_invisible_root->child(0))
        {
          if(boost::shared_ptr<Package> global_package_shared_ptr = item_global_package->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<Package>>())
          {
            ui->textBrowser->setText(QString::fromStdString(global_package_shared_ptr->toText()));
          }
        }
      }
    }
  }
}

void VisualDefinateTool::showEmptyPage()
{
  ui->stackedWidget->setCurrentWidget(ui->page_EmptyPage);
}

void VisualDefinateTool::showEnumeratedDataTypeInformation(boost::shared_ptr<EnumeratedDataType> enumerated_data_type_shared_ptr)
{
  if(enumerated_data_type_shared_ptr)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_EnumeratedDataTypeInformation);
    ui->page_EnumeratedDataTypeInformation->showEnumeratedDataTypeInformation(enumerated_data_type_shared_ptr);
  }
}

void VisualDefinateTool::showStructuredDataTypeInformation(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr)
{
  if(structured_data_type_shared_ptr)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_StructuredDataTypeInformation);
    ui->page_StructuredDataTypeInformation->showStructuredDataTypeInformation(structured_data_type_shared_ptr);
  }
}

void VisualDefinateTool::showPackageInformation(boost::shared_ptr<Package> package_shared_ptr)
{
  if(package_shared_ptr)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_PackageInformation);
    ui->page_PackageInformation->showPackageInformation(package_shared_ptr);
  }
}


void VisualDefinateTool::on_treeView_DefinationParseTree_customContextMenuRequested(const QPoint& pos)
{
  QMenu custom_menu;
  QList<QAction*> list_custom_action;

  QModelIndex index_current_selected=ui->treeView_DefinationParseTree->indexAt(pos);

  QAction* action_AppendEnumeratedDataType=new QAction(QString::fromLocal8Bit("添加枚举"),&custom_menu);
  QAction* action_AppendStructuredDataType=new QAction(QString::fromLocal8Bit("添加结构体"),&custom_menu);
  QAction* action_AppendPackage=new QAction(QString::fromLocal8Bit("添加包空间"),&custom_menu);
  QAction* action_PreviewDefination=new QAction(QString::fromLocal8Bit("预览定义"),&custom_menu);

  action_AppendEnumeratedDataType->setObjectName("action_AppendEnumeratedDataType");
  action_AppendStructuredDataType->setObjectName("action_AppendStructuredDataType");
  action_AppendPackage->setObjectName("action_AppendPackage");
  action_PreviewDefination->setObjectName("action_PreviewDefination");

  connect(action_AppendEnumeratedDataType,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  connect(action_AppendStructuredDataType,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  connect(action_AppendPackage,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  connect(action_PreviewDefination,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));

  switch(index_current_selected.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>())
  {
    case ENUMERATEDDATATYPE_GROUP:
    {
      list_custom_action<< action_AppendEnumeratedDataType;
      break;
    }
    case STRUCTUREDDATATYPE_GROUP:
    {
      list_custom_action<< action_AppendStructuredDataType;
      break;
    }
    case PACKAGE_GROUP:
    {
      list_custom_action<< action_AppendPackage;
      break;
    }
    case PACKAGE:
    {
      list_custom_action<< action_AppendEnumeratedDataType<< action_AppendStructuredDataType<< action_AppendPackage;
      break;
    }
    default:
    {
      list_custom_action<< action_PreviewDefination;
      break;
    }
  }

  custom_menu.exec(list_custom_action,QCursor::pos());
}

void VisualDefinateTool::slot_parseTree_currentRowChanged(const QModelIndex& index_current,const QModelIndex& index_previous)
{
  if(index_previous.isValid())
  {
    switch(index_previous.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>())
    {
      case ENUMERATEDDATATYPE:
      {
        break;
      }
      case STRUCTUREDDATATYPE:
      {
        break;
      }
      case PACKAGE:
      {
        break;
      }
      default:
      {
        break;
      }
    }
  }

  if(index_current.isValid())
  {
    QVariant variant_item_user_data= index_current.data(ITEM_USER_DATA_ROLE);
    switch(index_current.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>())
    {
      case ENUMERATEDDATATYPE:
      {
        showEnumeratedDataTypeInformation(variant_item_user_data.value<boost::shared_ptr<EnumeratedDataType>>());
        break;
      }
      case STRUCTUREDDATATYPE:
      {
        showStructuredDataTypeInformation(variant_item_user_data.value<boost::shared_ptr<StructuredDataType>>());
        break;
      }
      case PACKAGE:
      {
        showPackageInformation(variant_item_user_data.value<boost::shared_ptr<Package>>());
        break;
      }
      default:
      {
        showEmptyPage();
        break;
      }
    }
  }
}

void VisualDefinateTool::slot_customAction_triggered()
{
  if(QAction* action=dynamic_cast<QAction*>(sender()))
  {
    if(action->objectName()=="action_AppendEnumeratedDataType")
    {
      appendEnumeratedDataType();
    }
    else if(action->objectName()=="action_AppendStructuredDataType")
    {
      appendStructuredDataType();
    }
    else if(action->objectName()=="action_AppendPackage")
    {
      appendPackage();
    }
    else if(action->objectName()=="action_PreviewDefination")
    {
      previewDefination();
    }
    else
    {
    }
  }
}
