#pragma once

#ifndef __COMBOBOXDELEGATE_H__
# define __COMBOBOXDELEGATE_H__

#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
public:
  explicit ComboBoxDelegate(QObject* parent = nullptr);
  ~ComboBoxDelegate();
public:
  QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  void setEditorData(QWidget* editor,const QModelIndex& index) const override;
  void setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const override;
  //void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
};

#endif // !__COMBOBOXDELEGATE_H__
