#include "stdafx.h"
#include "EnumerationTypeInformation.h"
#include "ui_EnumerationTypeInformation.h"

#include "EnumerationType.h"

#include <QStandardItemModel>
#include <QMenu>

EnumerationTypeInformation::EnumerationTypeInformation(QWidget* parent):
  QWidget(parent),
  ui(new Ui::EnumerationTypeInformation())
{
  ui->setupUi(this);

  ui->tableView_EnumerationMembers->setModel(new QStandardItemModel(this));
  qobject_cast<QStandardItemModel*>(ui->tableView_EnumerationMembers->model())->setHorizontalHeaderLabels(QStringList()
    << QString::fromUtf8("标识符")
    //<< QString::fromUtf8("类型名称")
    << QString::fromUtf8("值")
    << QString::fromUtf8("描述"));
}

EnumerationTypeInformation::~EnumerationTypeInformation()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void EnumerationTypeInformation::showEnumerationTypeInformation(const boost::shared_ptr<EnumerationType>& enumerated_data_type_shared_ptr)// NOLINT(misc-no-recursion)
{
  this->enumerated_data_type_weak_ptr = enumerated_data_type_shared_ptr;

  this->showEnumerationTypeInformation();
}

void EnumerationTypeInformation::showName() const
{
  if(const boost::shared_ptr<EnumerationType>& enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    const QString& current_enumerated_data_type_name = QString::fromStdString(enumerated_data_type_shared_ptr->getName());

    ui->lineEdit_EnumerationTypeName->setText(current_enumerated_data_type_name);
  }
}

void EnumerationTypeInformation::showCompleteName() const
{
  if(const boost::shared_ptr<EnumerationType>& enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    const QString& current_enumerated_data_type_complete_name = QString::fromStdString(enumerated_data_type_shared_ptr->getCompleteName());

    ui->lineEdit_EnumerationTypeCompleteName->setText(current_enumerated_data_type_complete_name);
  }
}

void EnumerationTypeInformation::showMemberElementInformation() const
{
  if(const boost::shared_ptr<EnumerationType>& enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    if(auto model = qobject_cast<QStandardItemModel*>(ui->tableView_EnumerationMembers->model()))
    {
      model->setRowCount(0);

      const std::list<boost::shared_ptr<EnumerationMember>>& enumeration_members = enumerated_data_type_shared_ptr->getEnumerationMembers();
      std::for_each(enumeration_members.begin(),enumeration_members.end(),[&](const boost::shared_ptr<EnumerationMember>& enumeration_member_shared_ptr)
      {
        this->appendEnumerationMember(enumeration_member_shared_ptr);
      });
    }
  }
}

void EnumerationTypeInformation::showEnumerationTypeInformation() const
{
  if(const boost::shared_ptr<EnumerationType>& enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    //显示
    this->showName();
    this->showCompleteName();
    this->showMemberElementInformation();
  }
}

void EnumerationTypeInformation::appendEnumerationMember() const
{
  this->appendEnumerationMember(boost::make_shared<EnumerationMember>());
}

void EnumerationTypeInformation::moveEnumerationMemberUp() const
{
  const QModelIndex index_current_selected = ui->tableView_EnumerationMembers->currentIndex();
  if(index_current_selected.isValid())
  {
    if(auto model = qobject_cast<QStandardItemModel*>(ui->tableView_EnumerationMembers->model()))
    {
      const int current_row = index_current_selected.row();

      if(current_row > 0)
      {
        QList<QStandardItem*> items = model->takeRow(current_row);
        model->insertRow(current_row - 1,items);
      }
    }
  }
}

void EnumerationTypeInformation::moveEnumerationMemberDown() const
{
  const QModelIndex index_current_selected = ui->tableView_EnumerationMembers->currentIndex();
  if(index_current_selected.isValid())
  {
    if(auto model = qobject_cast<QStandardItemModel*>(ui->tableView_EnumerationMembers->model()))
    {
      const int current_row = index_current_selected.row();

      if(current_row < model->rowCount() - 1)
      {
        QList<QStandardItem*> items = model->takeRow(current_row);
        model->insertRow(current_row + 1,items);
      }
    }
  }
}

void EnumerationTypeInformation::removeEnumerationMember() const
{
  const QModelIndex index_current_selected = ui->tableView_EnumerationMembers->currentIndex();
  if(index_current_selected.isValid())
  {
    if(auto model = qobject_cast<QStandardItemModel*>(ui->tableView_EnumerationMembers->model()))
    {
      model->removeRow(index_current_selected.row());
    }
  }
}

void EnumerationTypeInformation::appendEnumerationMember(const boost::shared_ptr<EnumerationMember>& enumeration_member_shared_ptr) const
{
  if(enumeration_member_shared_ptr)
  {
    if(auto model = qobject_cast<QStandardItemModel*>(ui->tableView_EnumerationMembers->model()))
    {
      QList<QStandardItem*> items;

      auto item_member_name = new QStandardItem(QString::fromStdString(enumeration_member_shared_ptr->identifier));// NOLINT
      // auto item_member_type = new QStandardItem(QString::fromStdString(enumeration_member_shared_ptr->data_type_name));// NOLINT
      auto item_member_default_value = new QStandardItem(QString::fromStdString(enumeration_member_shared_ptr->default_value));// NOLINT
      auto item_member_annotation = new QStandardItem(QString::fromStdString(enumeration_member_shared_ptr->annotation));// NOLINT

      items
          << item_member_name
          //<< item_member_type
          << item_member_default_value
          << item_member_annotation;

      model->appendRow(items);
    }
  }
}

void EnumerationTypeInformation::on_lineEdit_EnumerationTypeName_textChanged(const QString& current_enumerated_data_type_name) const
{
  if(boost::shared_ptr<EnumerationType> enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    const QString& parent_package_complete_name = QString::fromStdString(enumerated_data_type_shared_ptr->getParentNamespaceCompleteName());
    const QString& current_enumerated_data_type_complete_name = parent_package_complete_name.isEmpty() ? current_enumerated_data_type_name : QString("%1::%2").arg(parent_package_complete_name,current_enumerated_data_type_name);

    ui->lineEdit_EnumerationTypeCompleteName->setText(current_enumerated_data_type_complete_name);
  }
}

void EnumerationTypeInformation::on_tableView_EnumerationMembers_customContextMenuRequested(const QPoint& pos) const
{
  const QModelIndex index_current_selected = ui->tableView_EnumerationMembers->indexAt(pos);

  QList<QAction*> custom_actions;

  auto action_AppendEnumerationMember = new QAction(QString::fromUtf8("添加"));// NOLINT
  {
    action_AppendEnumerationMember->setObjectName("action_AppendEnumerationMember");
    connect(action_AppendEnumerationMember,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_MoveEnumerationMemberUp = new QAction(QString::fromUtf8("上移"));// NOLINT
  {
    action_MoveEnumerationMemberUp->setObjectName("action_MoveEnumerationMemberUp");
    connect(action_MoveEnumerationMemberUp,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_MoveEnumerationMemberDown = new QAction(QString::fromUtf8("下移"));// NOLINT
  {
    action_MoveEnumerationMemberDown->setObjectName("action_MoveEnumerationMemberDown");
    connect(action_MoveEnumerationMemberDown,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  auto action_RemoveEnumerationMember = new QAction(QString::fromUtf8("移除"));// NOLINT
  {
    action_RemoveEnumerationMember->setObjectName("action_RemoveEnumerationMember");
    connect(action_RemoveEnumerationMember,SIGNAL(triggered()),this,SLOT(slot_customAction_triggered()));
  }

  custom_actions << action_AppendEnumerationMember;// 添加枚举成员

  if(index_current_selected.isValid())
  {
    if(index_current_selected.siblingAtRow(index_current_selected.row() - 1).isValid())// 非首元素允许上移
    {
      custom_actions << action_MoveEnumerationMemberUp;
    }

    if(index_current_selected.siblingAtRow(index_current_selected.row() + 1).isValid())// 非尾元素允许下移
    {
      custom_actions << action_MoveEnumerationMemberDown;
    }

    custom_actions << action_RemoveEnumerationMember;// 移除枚举成员
  }

  if(!custom_actions.isEmpty())
  {
    QMenu::exec(custom_actions,QCursor::pos());
  }
}

void EnumerationTypeInformation::on_pushButton_Reset_clicked() const
{
  this->showEnumerationTypeInformation();
}

void EnumerationTypeInformation::on_pushButton_Apply_clicked() const
{
  const std::string enumeration_type_name = ui->lineEdit_EnumerationTypeName->text().toStdString();
  std::list<boost::shared_ptr<EnumerationMember>> enumeration_members;
  {
    if(auto model = qobject_cast<QStandardItemModel*>(ui->tableView_EnumerationMembers->model()))
    {
      for(int row = 0;row < model->rowCount();++row)
      {
        auto item_member_name = model->item(row,0);
        //auto item_member_type = model->item(row,1);
        auto item_member_default_value = model->item(row,1);
        auto item_member_annotation = model->item(row,2);

        boost::shared_ptr<EnumerationMember> enumeration_member_shared_ptr = boost::make_shared<EnumerationMember>();
        enumeration_member_shared_ptr->identifier = item_member_name->text().toStdString();
        //enumeration_member_shared_ptr->data_type_name = "int";
        enumeration_member_shared_ptr->default_value = item_member_default_value->text().toStdString();
        enumeration_member_shared_ptr->annotation = item_member_annotation->text().toStdString();

        enumeration_members.emplace_back(enumeration_member_shared_ptr);
      }
    }
  }

  // Todo:
  // 合法性校验

  if(boost::shared_ptr<EnumerationType> enumerated_data_type_shared_ptr = this->enumerated_data_type_weak_ptr.lock())
  {
    enumerated_data_type_shared_ptr->setName(enumeration_type_name);
    enumerated_data_type_shared_ptr->setEnumerationMembers(enumeration_members);
  }
}

void EnumerationTypeInformation::slot_customAction_triggered() const
{
  auto action = qobject_cast<QAction*>(sender());

  if(action->objectName() == "action_AppendEnumerationMember")
  {
    this->appendEnumerationMember();
  }
  else if(action->objectName() == "action_MoveEnumerationMemberUp")
  {
    this->moveEnumerationMemberUp();
  }
  else if(action->objectName() == "action_MoveEnumerationMemberDown")
  {
    this->moveEnumerationMemberDown();
  }
  else if(action->objectName() == "action_RemoveEnumerationMember")
  {
    this->removeEnumerationMember();
  }
}
