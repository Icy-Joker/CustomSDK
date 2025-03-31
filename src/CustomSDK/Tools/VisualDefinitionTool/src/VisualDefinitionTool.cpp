#include "stdafx.h"
#include "VisualDefinitionTool.h"

#include <QFileDialog>

#include "ui_VisualDefinitionTool.h"
#include "CustomItemModel.h"

#include "IDLFileDefinition.h"
#include "EnumeratedDataType.h"
#include "StructuredDataType.h"
#include "Package.h"
#include "EnumeratedDataTypeInformation.h"

#include "StructuredDataTypeInformation.h"
#include "PackageInformation.h"

#include <QMenu>
#include <QMessageBox>

VisualDefinitionTool::VisualDefinitionTool(QWidget* parent):
  QWidget(parent),
  ui(new Ui::VisualDefinitionTool())
{
  ui->setupUi(this);

  if(CustomItemModel* model = new CustomItemModel(this))
  {
    ui->treeView_DefinitionParseTree->setModel(model);
  }
  connect(ui->treeView_DefinitionParseTree->selectionModel(),
    SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),this,
    SLOT(slot_parseTree_currentRowChanged(const QModelIndex&,const QModelIndex&)));

  {
    //测试
    //appendPackage(((QStandardItemModel*)(ui->treeView_DefinitionParseTree->model()))->invisibleRootItem());
  }
}

VisualDefinitionTool::~VisualDefinitionTool()
{
}

QStandardItem* VisualDefinitionTool::appendFileDefinition(QStandardItem* item_parent)
{
  QStandardItem* item_current_file_definition = nullptr;

  if(item_parent)
  {
    item_current_file_definition = new QStandardItem();
    {
      if(boost::shared_ptr<IDLFileDefinition> current_file_definition_shared_ptr = boost::make_shared<IDLFileDefinition>())
      {
        item_current_file_definition->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::FILEDEFINITION),ITEM_TREE_NODE_TYPE_ROLE);
        item_current_file_definition->setData(QVariant::fromValue<boost::shared_ptr<AbstractDefinition>>(current_file_definition_shared_ptr),ITEM_USER_DATA_ROLE);

        item_parent->appendRow(item_current_file_definition);
      }
    }
  }

  return item_current_file_definition;
}

QStandardItem* VisualDefinitionTool::appendEnumeratedDataType(QStandardItem* item_parent)
{
  QStandardItem* item_current_enumerated_data_type = nullptr;

  if(item_parent)
  {
    if((item_current_enumerated_data_type = new QStandardItem()))
    {
      if(boost::shared_ptr<EnumeratedDataType> current_enumerated_data_type_shared_ptr = boost::make_shared<
        EnumeratedDataType>())
      {
        if(auto parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(
          item_parent->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
        {
          current_enumerated_data_type_shared_ptr->setParentNamespace(parent_package_shared_ptr);
          parent_package_shared_ptr->appendEnumeratedDataType(current_enumerated_data_type_shared_ptr);
        }

        item_current_enumerated_data_type->setData(
          QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::ENUMERATEDDATATYPE),ITEM_TREE_NODE_TYPE_ROLE);
        item_current_enumerated_data_type->setData(
          QVariant::fromValue<boost::shared_ptr<AbstractDefinition>>(current_enumerated_data_type_shared_ptr),
          ITEM_USER_DATA_ROLE);

        item_parent->appendRow(item_current_enumerated_data_type);
      }
    }
  }

  return item_current_enumerated_data_type;
}

QStandardItem* VisualDefinitionTool::appendStructuredDataType(QStandardItem* item_parent)
{
  QStandardItem* item_current_structured_data_type = nullptr;

  if(item_parent)
  {
    if((item_current_structured_data_type = new QStandardItem()))
    {
      if(boost::shared_ptr<StructuredDataType> current_structured_data_type_shared_ptr = boost::make_shared<
        StructuredDataType>())
      {
        if(auto parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(
          item_parent->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
        {
          current_structured_data_type_shared_ptr->setParentNamespace(parent_package_shared_ptr);
          parent_package_shared_ptr->appendStructuredDataType(current_structured_data_type_shared_ptr);
        }
        item_current_structured_data_type->setData(
          QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::STRUCTUREDDATATYPE),ITEM_TREE_NODE_TYPE_ROLE);
        item_current_structured_data_type->setData(
          QVariant::fromValue<boost::shared_ptr<AbstractDefinition>>(current_structured_data_type_shared_ptr),
          ITEM_USER_DATA_ROLE);

        item_parent->appendRow(item_current_structured_data_type);
      }
    }
  }

  return item_current_structured_data_type;
}

QStandardItem* VisualDefinitionTool::appendPackage(QStandardItem* item_parent)
{
  QStandardItem* item_current_package = nullptr;

  if(item_parent)
  {
    item_current_package = new QStandardItem();
    {
      if(const auto current_package_shared_ptr = boost::make_shared<Package>())
      {
        if(auto parent_package_shared_ptr = boost::dynamic_pointer_cast<Package>(item_parent->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
        {
          current_package_shared_ptr->setParentNamespace(parent_package_shared_ptr);
          parent_package_shared_ptr->appendPackage(current_package_shared_ptr);
        }
        item_current_package->setData(QVariant::fromValue<TREE_NODE_TYPE>(TREE_NODE_TYPE::PACKAGE),ITEM_TREE_NODE_TYPE_ROLE);
        item_current_package->setData(QVariant::fromValue<boost::shared_ptr<AbstractDefinition>>(current_package_shared_ptr),ITEM_USER_DATA_ROLE);

        item_parent->appendRow(item_current_package);
      }
    }
  }

  return item_current_package;
}

void VisualDefinitionTool::appendFileDefinition()
{
  if(const QStandardItemModel* model_parse_tree = qobject_cast<QStandardItemModel*>(ui->treeView_DefinitionParseTree->model()))
  {
    if(QStandardItem* item_parent = model_parse_tree->invisibleRootItem())
    {
      if(!item_parent->hasChildren())
      {
        if(QStandardItem* item_file_definition = appendFileDefinition(item_parent))
        {
          if(boost::shared_ptr<IDLFileDefinition> current_file_definition_shared_ptr = boost::dynamic_pointer_cast<IDLFileDefinition>(item_file_definition->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
          {
            boost::shared_ptr<IDLFileDefinition> file_reference_definition_shared_ptr = boost::make_shared<IDLFileDefinition>();
            file_reference_definition_shared_ptr->setFilePath("/Users/icy-joker/WorkSpace/CustomSDK/src/build/clion/relwithdebinfo/bin/RelWithDebInfo/ss.xidl");

            current_file_definition_shared_ptr->appendFileReference(file_reference_definition_shared_ptr);
          }

          ui->treeView_DefinitionParseTree->expandAll();
        }
      }
      else
      {
        // 已存在文件定义;
        {
          // todo:
          // 判断已存在文件定义是否有修改
          if(true)
          {
            QMessageBox::StandardButton button = QMessageBox::question(this,"提示","已存在文件定义，是否保存？",QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            if(button == QMessageBox::Yes)
            {
              if(boost::shared_ptr<IDLFileDefinition> current_file_definition_shared_ptr = boost::dynamic_pointer_cast<IDLFileDefinition>(item_parent->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
              {
                if(current_file_definition_shared_ptr->doSave())
                {
                }
              }
            }
          }
          else
          {
          }
        }
      }
    }
  }
}

void VisualDefinitionTool::appendEnumeratedDataType()
{
  const QModelIndex index_current_selected = ui->treeView_DefinitionParseTree->currentIndex();

  if(const auto* model_parse_tree = qobject_cast<QStandardItemModel*>(ui->treeView_DefinitionParseTree->model()))
  {
    if(QStandardItem* item_parent = index_current_selected.isValid()
                                      ? model_parse_tree->itemFromIndex(index_current_selected)
                                      : model_parse_tree->invisibleRootItem())
    {
      if(QStandardItem* item_enumerated_data_type = appendEnumeratedDataType(item_parent))
      {
        ui->treeView_DefinitionParseTree->setCurrentIndex(item_enumerated_data_type->index());
      }
    }
  }
}

void VisualDefinitionTool::appendStructuredDataType()
{
  const QModelIndex index_current_selected = ui->treeView_DefinitionParseTree->currentIndex();

  if(const auto* model_parse_tree = qobject_cast<QStandardItemModel*>(ui->treeView_DefinitionParseTree->model()))
  {
    if(QStandardItem* item_parent = index_current_selected.isValid()
                                      ? model_parse_tree->itemFromIndex(index_current_selected)
                                      : model_parse_tree->invisibleRootItem())
    {
      if(QStandardItem* item_structured_data_type = appendStructuredDataType(item_parent))
      {
        ui->treeView_DefinitionParseTree->setCurrentIndex(item_structured_data_type->index());
      }
    }
  }
}

void VisualDefinitionTool::appendPackage()
{
  const QModelIndex index_current_selected = ui->treeView_DefinitionParseTree->currentIndex();

  if(const auto* model_parse_tree = qobject_cast<QStandardItemModel*>(ui->treeView_DefinitionParseTree->model()))
  {
    if(QStandardItem* item_parent = index_current_selected.isValid() ? model_parse_tree->itemFromIndex(index_current_selected) : model_parse_tree->invisibleRootItem())
    {
      if(QStandardItem* item_package = appendPackage(item_parent))
      {
        ui->treeView_DefinitionParseTree->setCurrentIndex(item_package->index());
      }
    }
  }
};

void VisualDefinitionTool::previewDefinition()
{
  ui->tabWidget->setCurrentWidget(ui->tab_TextView);

  ui->textBrowser->clear();
  if(auto model_parse_tree = qobject_cast<QStandardItemModel*>(ui->treeView_DefinitionParseTree->model()))
  {
    if(QStandardItem* item_invisible_root = model_parse_tree->invisibleRootItem())
    {
      if(item_invisible_root->hasChildren())
      {
        if(QStandardItem* item_file_definition = item_invisible_root->child(0))
        {
          if(auto current_file_definition_shared_ptr = boost::dynamic_pointer_cast<IDLFileDefinition>(item_file_definition->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
          {
            ui->textBrowser->setText(QString::fromStdString(current_file_definition_shared_ptr->toText()));
          }
        }
      }
    }
  }
}

void VisualDefinitionTool::saveDefinition()
{
  if(auto model_parse_tree = qobject_cast<QStandardItemModel*>(ui->treeView_DefinitionParseTree->model()))
  {
    if(QStandardItem* item_invisible_root = model_parse_tree->invisibleRootItem())
    {
      if(item_invisible_root->hasChildren())
      {
        if(QStandardItem* item_file_definition = item_invisible_root->child(0))
        {
          if(auto current_file_definition_shared_ptr = boost::dynamic_pointer_cast<IDLFileDefinition>(item_file_definition->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
          {
            if(current_file_definition_shared_ptr->doSave())
            {
              QMessageBox::information(this,QString::fromUtf8("信息"),QString::fromUtf8("保存成功"));
            }
          }
        }
      }
    }
  }
}

void VisualDefinitionTool::saveDefinitionAs()
{
  if(auto model_parse_tree = qobject_cast<QStandardItemModel*>(ui->treeView_DefinitionParseTree->model()))
  {
    if(QStandardItem* item_invisible_root = model_parse_tree->invisibleRootItem())
    {
      if(item_invisible_root->hasChildren())
      {
        if(QStandardItem* item_file_definition = item_invisible_root->child(0))
        {
          if(auto current_file_definition_shared_ptr = boost::dynamic_pointer_cast<IDLFileDefinition>(item_file_definition->data(ITEM_USER_DATA_ROLE).value<boost::shared_ptr<AbstractDefinition>>()))
          {
            const std::string& save_file_path = QFileDialog::getSaveFileName(this,QString::fromUtf8("另存为"),".","*.xidl").toStdString();
            if(current_file_definition_shared_ptr->doSaveAs(save_file_path))
            {
              QMessageBox::information(this,QString::fromUtf8("信息"),QString::fromUtf8("保存成功"));
            }
          }
        }
      }
    }
  }
}

void VisualDefinitionTool::showEmptyPage()
{
  ui->stackedWidget->setCurrentWidget(ui->page_EmptyPage);
}

void VisualDefinitionTool::showIDLFileDefinitionInformation(boost::shared_ptr<IDLFileDefinition> file_definition_shared_ptr)
{
  if(file_definition_shared_ptr)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_IDLFileDefinitionInformation);
    ui->page_IDLFileDefinitionInformation->showIDLFileDefinitionInformation(file_definition_shared_ptr);
  }
}

void VisualDefinitionTool::showEnumeratedDataTypeInformation(boost::shared_ptr<EnumeratedDataType> enumerated_data_type_shared_ptr)
{
  if(enumerated_data_type_shared_ptr)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_EnumeratedDataTypeInformation);
    ui->page_EnumeratedDataTypeInformation->showEnumeratedDataTypeInformation(enumerated_data_type_shared_ptr);
  }
}

void VisualDefinitionTool::showStructuredDataTypeInformation(boost::shared_ptr<StructuredDataType> structured_data_type_shared_ptr)
{
  if(structured_data_type_shared_ptr)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_StructuredDataTypeInformation);
    ui->page_StructuredDataTypeInformation->showStructuredDataTypeInformation(structured_data_type_shared_ptr);
  }
}

void VisualDefinitionTool::showPackageInformation(boost::shared_ptr<Package> package_shared_ptr)
{
  if(package_shared_ptr)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_PackageInformation);
    ui->page_PackageInformation->showPackageInformation(package_shared_ptr);
  }
}

void VisualDefinitionTool::on_treeView_DefinitionParseTree_customContextMenuRequested(const QPoint& pos)
{
  QMenu custom_menu;
  QList<QAction*> list_custom_action;

  QModelIndex index_current_selected = ui->treeView_DefinitionParseTree->indexAt(pos);

  auto action_CreateIDLFileDefinition = new QAction(QString::fromUtf8("新建文件"),&custom_menu);
  {
    action_CreateIDLFileDefinition->setObjectName("action_CreateIDLFileDefinition");
    connect(action_CreateIDLFileDefinition,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_LoadIDLFileDefinition = new QAction(QString::fromUtf8("加载文件"),&custom_menu);
  {
    action_LoadIDLFileDefinition->setObjectName("action_LoadIDLFileDefinition");
    connect(action_LoadIDLFileDefinition,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_AppendEnumeratedDataType = new QAction(QString::fromUtf8("添加枚举"),&custom_menu);
  {
    action_AppendEnumeratedDataType->setObjectName("action_AppendEnumeratedDataType");
    connect(action_AppendEnumeratedDataType,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_AppendStructuredDataType = new QAction(QString::fromUtf8("添加结构体"),&custom_menu);
  {
    action_AppendStructuredDataType->setObjectName("action_AppendStructuredDataType");
    connect(action_AppendStructuredDataType,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_AppendPackage = new QAction(QString::fromUtf8("添加包空间"),&custom_menu);
  {
    action_AppendPackage->setObjectName("action_AppendPackage");
    connect(action_AppendPackage,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_PreviewDefinition = new QAction(QString::fromUtf8("预览定义"),&custom_menu);
  {
    action_PreviewDefinition->setObjectName("action_PreviewDefinition");
    connect(action_PreviewDefinition,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_SaveDefinition = new QAction(QString::fromUtf8("保存"),&custom_menu);
  {
    action_SaveDefinition->setObjectName("action_SaveDefinition");
    connect(action_SaveDefinition,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_SaveDefinitionAs = new QAction(QString::fromUtf8("另存为"),&custom_menu);
  {
    action_SaveDefinitionAs->setObjectName("action_SaveDefinitionAs");
    connect(action_SaveDefinitionAs,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  switch(index_current_selected.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>())
  {
    case FILEDEFINITION:
    {
      list_custom_action << action_AppendEnumeratedDataType << action_AppendStructuredDataType << action_AppendPackage << action_PreviewDefinition << action_SaveDefinition << action_SaveDefinitionAs;
      break;
    }
    case PACKAGE:
    {
      list_custom_action << action_AppendEnumeratedDataType << action_AppendStructuredDataType << action_AppendPackage;
      break;
    }
    case UNKNOWN:
    {
      list_custom_action << action_CreateIDLFileDefinition << action_LoadIDLFileDefinition;
      break;
    }
    default:
    {
      break;
    }
  }

  if(!list_custom_action.isEmpty())
  {
    custom_menu.exec(list_custom_action,QCursor::pos());
  }
}

void VisualDefinitionTool::on_treeView_DefinitionParseTree_clicked(const QModelIndex&)
{
  ui->tabWidget->setCurrentWidget(ui->tab_VisualView);
}

void VisualDefinitionTool::slot_parseTree_currentRowChanged(const QModelIndex& index_current,const QModelIndex& index_previous)
{
  if(index_previous.isValid())
  {
  }

  if(index_current.isValid())
  {
    QVariant variant_item_user_data = index_current.data(ITEM_USER_DATA_ROLE);
    switch(index_current.data(ITEM_TREE_NODE_TYPE_ROLE).value<TREE_NODE_TYPE>())
    {
      case FILEDEFINITION:
      {
        showIDLFileDefinitionInformation(boost::dynamic_pointer_cast<IDLFileDefinition>(variant_item_user_data.value<boost::shared_ptr<AbstractDefinition>>()));
        break;
      }
      case ENUMERATEDDATATYPE:
      {
        showEnumeratedDataTypeInformation(boost::dynamic_pointer_cast<EnumeratedDataType>(variant_item_user_data.value<boost::shared_ptr<AbstractDefinition>>()));
        break;
      }
      case STRUCTUREDDATATYPE:
      {
        showStructuredDataTypeInformation(boost::dynamic_pointer_cast<StructuredDataType>(variant_item_user_data.value<boost::shared_ptr<AbstractDefinition>>()));
        break;
      }
      case PACKAGE:
      {
        showPackageInformation(boost::dynamic_pointer_cast<Package>(variant_item_user_data.value<boost::shared_ptr<AbstractDefinition>>()));
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

void VisualDefinitionTool::slot_customAction_triggered()
{
  if(QAction* action = dynamic_cast<QAction*>(sender()))
  {
    if(action->objectName() == "action_CreateIDLFileDefinition")
    {
      appendFileDefinition();
    }
    else if(action->objectName() == "action_LoadIDLFileDefinition")
    {
    }
    else if(action->objectName() == "action_AppendEnumeratedDataType")
    {
      appendEnumeratedDataType();
    }
    else if(action->objectName() == "action_AppendStructuredDataType")
    {
      appendStructuredDataType();
    }
    else if(action->objectName() == "action_AppendPackage")
    {
      appendPackage();
    }
    else if(action->objectName() == "action_PreviewDefinition")
    {
      previewDefinition();
    }
    else if(action->objectName() == "action_SaveDefinition")
    {
      saveDefinition();
    }
    else if(action->objectName() == "action_SaveDefinitionAs")
    {
      saveDefinitionAs();
    }
    else
    {
    }
  }
}
