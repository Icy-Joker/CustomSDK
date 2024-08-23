#pragma once

#ifndef __PASSWORDDELEGATE_H__
# define __PASSWORDDELEGATE_H__

#include <QStyledItemDelegate>

class PasswordDelegate : public QStyledItemDelegate
{
public:
  explicit PasswordDelegate(QObject* parent = nullptr);
  ~PasswordDelegate();
public:
  QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  void setEditorData(QWidget* editor,const QModelIndex& index) const override;
  void setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const override;
  QString displayText(const QVariant& value,const QLocale& locale) const override;
};

#endif // !__PASSWORDDELEGATE_H__
