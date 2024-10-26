#include "stdafx.h"

#include "JsonVisualEditor/JsonVisualEditor.h"
#include "ui_JsonVisualEditor.h"

#include <nlohmann/json.hpp>

#include <QMessageBox>
#include <QStandardItemModel>

#include <iostream>

JsonVisualEditor::JsonVisualEditor(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::JsonVisualEditor())
{
  ui->setupUi(this);

  if(QStandardItemModel* model = new QStandardItemModel(this))
  {
    ui->treeView->setModel(model);
  }

  if(QStandardItemModel* model = new QStandardItemModel(this))
  {
    model->setHorizontalHeaderLabels(QStringList() << QString::fromUtf8("attribute") << QString::fromUtf8("value"));
    ui->tableView->setModel(model);
  }

  ui->plainTextEdit->setPlainText(QString::fromStdString(R"({"name":"JohnDoe","age":30,"address":{"city":"NewYork","postal_code":"10001","country":"USA"},"contacts":[{"type":"email","value":"john.doe@example.com"},{"type":"phone","value":"123-456-7890"}],"orders":[{"order_id":"12345","date":"2024-07-12","items":[{"item_id":"A001","name":"ItemA","quantity":2,"price":10.99},{"item_id":"B002","name":"ItemB","quantity":1,"price":19.99}]},{"order_id":"67890","date":"2024-07-11","items":[{"item_id":"C003","name":"ItemC","quantity":3,"price":5.99}]}]})"));
}

JsonVisualEditor::~JsonVisualEditor()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void doConstructTree(QStandardItem* item_parent,const nlohmann::ordered_json& current_json_object)
{
  if(item_parent)
  {
    try
    {
      if(current_json_object.is_object())
      {
        std::for_each(current_json_object.items().begin(),current_json_object.items().end(),[&](const auto& it)
        {
          const std::string& attribute_name = it.key();
          const nlohmann::ordered_json& child_json_object = it.value();

          if(QStandardItem* item_child = new QStandardItem(QString::fromStdString(attribute_name)))
          {
            doConstructTree(item_child,child_json_object);

            item_parent->appendRow(item_child);
          }
        });
      }
      else if(current_json_object.is_array())
      {
        std::for_each(current_json_object.begin(),current_json_object.end(),[&](const auto& child_json_object)
        {
          if(QStandardItem* item_child = new QStandardItem(QString::number(item_parent->rowCount())))
          {
            doConstructTree(item_child,child_json_object);

            item_parent->appendRow(item_child);
          }
        });
      }
      else
      {
        if(QStandardItem* item_child = new QStandardItem(QString::fromStdString(current_json_object.dump(2))))
        {
          item_parent->appendRow(item_child);
        }
      }

      item_parent->setData(QVariant::fromValue<nlohmann::ordered_json>(current_json_object),Qt::UserRole);
    }
    catch(const std::exception& e)
    {
      qDebug("%s",e.what());
    }
  }
}

void JsonVisualEditor::doParseJson()
{
  if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->treeView->model()))
  {
    model->clear();

    const std::string json_content = ui->plainTextEdit->toPlainText().toStdString();
    if(!json_content.empty())
    {
      try
      {
        nlohmann::ordered_json json_object = nlohmann::ordered_json::parse(json_content);
        if(!json_object.empty())
        {
          ui->plainTextEdit->setPlainText(json_object.dump(2).c_str());

          if(QStandardItem* item_json_root = new QStandardItem(tr("Json Root")))
          {
            doConstructTree(item_json_root,json_object);

            model->appendRow(item_json_root);
          }
        }
      }
      catch(const std::exception& e)
      {
        //QMessageBox::critical(this,tr("Exception"),QString::fromStdString(e.what()));
      }
    }
  }
}

void JsonVisualEditor::on_treeView_clicked(const QModelIndex& index_current_selected)
{
  if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model()))
  {
    model->clear();

    if(index_current_selected.isValid())
    {
      nlohmann::ordered_json current_json_object = index_current_selected.data(Qt::UserRole).value<nlohmann::ordered_json>();
      if(!current_json_object.empty())
      {
        if(current_json_object.is_object())
        {
          std::for_each(current_json_object.items().begin(),current_json_object.items().end(),[&](const auto& it)
          {
            const std::string& attribute_name = it.key();
            const nlohmann::ordered_json& child_json_object = it.value();

            const std::string attribute_value = !child_json_object.is_object() && !child_json_object.is_array() ? child_json_object.dump(2) : "...";

            QStandardItem* item_attribute_name = new QStandardItem(QString::fromStdString(attribute_name));
            QStandardItem* item_attribute_value = new QStandardItem(QString::fromStdString(attribute_value));

            model->appendRow(QList<QStandardItem*>() << item_attribute_name << item_attribute_value);
          });
        }
        else if(current_json_object.is_array())
        {
          std::for_each(current_json_object.begin(),current_json_object.end(),[&](const nlohmann::ordered_json& child_json_object)
          {
            const std::string& array_index = std::to_string((long)model->rowCount());
            const std::string& array_object = !child_json_object.is_object() && !child_json_object.is_array() ? child_json_object.dump(2) : "...";

            QStandardItem* item_array_index = new QStandardItem(QString::fromStdString(array_index));
            QStandardItem* item_array_object = new QStandardItem(QString::fromStdString(array_object));

            model->appendRow(QList<QStandardItem*>() << item_array_index << item_array_object);
          });
        }
        else
        {
          const std::string attribute_value = !current_json_object.is_object() && !current_json_object.is_array() ? current_json_object.dump(2) : "...";

          QStandardItem* item_attribute_value = new QStandardItem(QString::fromStdString(attribute_value));

          model->appendRow(QList<QStandardItem*>() << item_attribute_value);
        }
      }
    }
  }
}

void JsonVisualEditor::keyPressEvent(QKeyEvent* event)
{
  if(QKeySequence(QKeySequence::Save).matches(event->key() | event->modifiers()))
  {
    if(this->focusWidget() == ui->plainTextEdit)
    {
      doParseJson();
    }
  }

  QMainWindow::keyPressEvent(event);
}
