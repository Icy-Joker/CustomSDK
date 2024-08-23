#pragma once

#ifndef __DATETIMEDELEGATE_H__
# define __DATETIMEDELEGATE_H__

#include <QStyledItemDelegate>

class DateTimeDelegate : public QStyledItemDelegate
{
public:
  explicit DateTimeDelegate(QObject* parent = nullptr);
  ~DateTimeDelegate();
public:
  QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  void setEditorData(QWidget* editor,const QModelIndex& index) const override;
  void setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const override;
};

#endif // !__DATETIMEDELEGATE_H__
