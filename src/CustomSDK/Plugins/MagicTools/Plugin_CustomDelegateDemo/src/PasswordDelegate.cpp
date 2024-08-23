#include "stdafx.h"

#include "PasswordDelegate.h"

#include <QLineEdit>

PasswordDelegate::PasswordDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

PasswordDelegate::~PasswordDelegate()
{
}

QWidget* PasswordDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  if(QLineEdit* line_editor = new QLineEdit(parent))
  {
    line_editor->setEchoMode(QLineEdit::Password);// 设置为密码输入模式

    editor = line_editor;
  }

  return editor;
}

void PasswordDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const
{
  if(QLineEdit* line_editor = qobject_cast<QLineEdit*>(editor))
  {
    line_editor->setText(index.model()->data(index,Qt::EditRole).toString());
  }
}

void PasswordDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const
{
  if(QLineEdit* line_editor = qobject_cast<QLineEdit*>(editor))
  {
    QString password_text = line_editor->text();

    model->blockSignals(true);
    model->setData(index,password_text,Qt::DisplayRole);
    model->blockSignals(false);
  }
}

QString PasswordDelegate::displayText(const QVariant& value,const QLocale& locale) const
{
  return QStyledItemDelegate::displayText("******",locale);
}
