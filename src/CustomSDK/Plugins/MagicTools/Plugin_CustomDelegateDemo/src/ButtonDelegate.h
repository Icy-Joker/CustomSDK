#pragma once

#ifndef __BUTTONDELEGATE_H__
# define __BUTTONDELEGATE_H__

#include <QStyledItemDelegate>
#include <QPushButton>

class ButtonDelegate : public QStyledItemDelegate
{
public:
  explicit ButtonDelegate(QObject* parent = nullptr);
  ~ButtonDelegate();
public:
  QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  bool editorEvent(QEvent* event,QAbstractItemModel* model,const QStyleOptionViewItem& option,const QModelIndex& index) override;
public:
};

#endif // !__BUTTONDELEGATE_H__
