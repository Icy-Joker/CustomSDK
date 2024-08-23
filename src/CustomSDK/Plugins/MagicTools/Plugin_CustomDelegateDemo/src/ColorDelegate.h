#pragma once

#ifndef __COLORDELEGATE_H__
# define __COLORDELEGATE_H__

#include <QStyledItemDelegate>

class ColorDelegate : public QStyledItemDelegate
{
public:
  explicit ColorDelegate(QObject* parent = nullptr);
  ~ColorDelegate();
public:
  QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  void setEditorData(QWidget* editor,const QModelIndex& index) const override;
  void setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const override;
  void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
};

#endif // !__COLORDELEGATE_H__
