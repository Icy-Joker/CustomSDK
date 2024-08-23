#include "stdafx.h"

#include "DateTimeDelegate.h"

#include <QDateTimeEdit>

DateTimeDelegate::DateTimeDelegate(QObject* parent)
{
}

DateTimeDelegate::~DateTimeDelegate()
{
}

QWidget* DateTimeDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  if(QDateTimeEdit* date_time_editor = new QDateTimeEdit(parent))
  {
    date_time_editor->setDisplayFormat("yyyy/MM/dd");

    editor = date_time_editor;
  }

  return editor;
}

void DateTimeDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const
{
  if(QDateTimeEdit* date_time_editor = qobject_cast<QDateTimeEdit*>(editor))
  {
    date_time_editor->setDateTime(index.model()->data(index,Qt::EditRole).toDateTime());
  }
}

void DateTimeDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const
{
  if(QDateTimeEdit* date_time_editor = qobject_cast<QDateTimeEdit*>(editor))
  {
    QString date_time_text = date_time_editor->dateTime().toString(date_time_editor->displayFormat());

    model->blockSignals(true);
    model->setData(index,date_time_text,Qt::DisplayRole);
    model->blockSignals(false);
  }
}
