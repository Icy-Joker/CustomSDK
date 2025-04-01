#pragma once

#ifndef STRUCTUREMEMBERDELEGATE_H
# define STRUCTUREMEMBERDELEGATE_H

#include <QStyledItemDelegate>

class StructureMemberDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit StructureMemberDelegate(QObject* parent = nullptr);
  ~StructureMemberDelegate();
public:
  void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  void setEditorData(QWidget* editor,const QModelIndex& index) const override;
  void setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const override;
  void updateEditorGeometry(QWidget* editor,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
};

#endif // !STRUCTUREMEMBERDELEGATE_H
