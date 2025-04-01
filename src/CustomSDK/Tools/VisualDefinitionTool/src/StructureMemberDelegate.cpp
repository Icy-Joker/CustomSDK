#include "stdafx.h"

#include "StructureMemberDelegate.h"

StructureMemberDelegate::StructureMemberDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

StructureMemberDelegate::~StructureMemberDelegate()
{
}

void StructureMemberDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QStyledItemDelegate::paint(painter,option,index);
}

QWidget* StructureMemberDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  return QStyledItemDelegate::createEditor(parent,option,index);
}

void StructureMemberDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const
{
  QStyledItemDelegate::setEditorData(editor,index);
}

void StructureMemberDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const
{
  QStyledItemDelegate::setModelData(editor,model,index);
}

void StructureMemberDelegate::updateEditorGeometry(QWidget* editor,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}
