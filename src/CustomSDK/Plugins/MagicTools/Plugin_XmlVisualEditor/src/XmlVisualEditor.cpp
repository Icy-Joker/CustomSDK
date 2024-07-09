#include "stdafx.h"

#include "XmlVisualEditor/XmlVisualEditor.h"
#include "ui_XmlVisualEditor.h"
#include "XmlVisualEditorPrivate.h"

#include <pugixml.hpp>

#include <QMessageBox>
#include <QStandardItemModel>
#include <QFile>

#include <iostream>
#include <sstream>

Q_DECLARE_METATYPE(pugi::xml_node)

XmlVisualEditor::XmlVisualEditor(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::XmlVisualEditor()),
  _p(new XmlVisualEditorPrivate())
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

  ui->plainTextEdit->setTabStopDistance(4.0);

  QFile file("../etc/MagicToolBox.xml");
  if(file.open(QIODevice::Text | QIODevice::ReadOnly))
  {
    QTextStream text_stream(&file);

    ui->plainTextEdit->setPlainText(text_stream.readAll());
  }
}

XmlVisualEditor::~XmlVisualEditor()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void doConstructTree(QStandardItem* item_parent,const pugi::xml_node& current_xml_object)
{
  if(item_parent)
  {
    if(current_xml_object && current_xml_object.type() == pugi::xml_node_type::node_element)
    {
      if(QStandardItem* item_child = new QStandardItem(current_xml_object.name()))
      {
        std::for_each(current_xml_object.children().begin(),current_xml_object.children().end(),[&](const pugi::xml_node& child_xml_object)
        {
          doConstructTree(item_child,child_xml_object);
        });

        item_child->setData(QVariant::fromValue<pugi::xml_node>(current_xml_object),Qt::UserRole);

        item_parent->appendRow(item_child);
      }
    }
  }
}

void XmlVisualEditor::doParseXml()
{
  if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->treeView->model()))
  {
    model->clear();

    const std::string xml_content = ui->plainTextEdit->toPlainText().toStdString();
    if(!xml_content.empty())
    {
      try
      {
        _p->xml_document = pugi::xml_document();
        if(_p->xml_document.load_string(xml_content.c_str()))
        {
          std::stringstream ss;
          _p->xml_document.print(ss);

          ui->plainTextEdit->setPlainText(QString::fromStdString(ss.str()));

          std::for_each(_p->xml_document.children().begin(),_p->xml_document.children().end(),[&](const pugi::xml_node& child_xml_object)
          {
            doConstructTree(model->invisibleRootItem(),child_xml_object);
          });
        }
      }
      catch(const std::exception& e)
      {
        //QMessageBox::critical(this,tr("Exception"),QString::fromStdString(e.what()));
      }
    }
  }
  if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model()))
  {
    model->clear();
  }
  ui->textBrowser->clear();
}

void XmlVisualEditor::on_treeView_clicked(const QModelIndex& index_current_selected)
{
  if(QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model()))
  {
    model->clear();

    if(index_current_selected.isValid())
    {
      if(pugi::xml_node current_xml_node = index_current_selected.data(Qt::UserRole).value<pugi::xml_node>())
      {
        if(current_xml_node.type() == pugi::xml_node_type::node_element)
        {
          std::for_each(current_xml_node.attributes().begin(),current_xml_node.attributes().end(),[&](const pugi::xml_attribute& attribute)
          {
            const char* attribute_name = attribute.name();
            const char* attribute_value = attribute.value();

            QStandardItem* item_attribute_name = new QStandardItem(attribute_name);
            QStandardItem* item_attribute_value = new QStandardItem(attribute_value);

            model->appendRow(QList<QStandardItem*>() << item_attribute_name << item_attribute_value);
          });

          ui->textBrowser->setPlainText(current_xml_node.text().as_string());
        }
      }
    }
  }
}

void XmlVisualEditor::keyPressEvent(QKeyEvent* event)
{
  if(QKeySequence(QKeySequence::Save).matches(event->key() | event->modifiers()))
  {
    if(this->focusWidget() == ui->plainTextEdit)
    {
      doParseXml();
    }
  }

  QMainWindow::keyPressEvent(event);
}
