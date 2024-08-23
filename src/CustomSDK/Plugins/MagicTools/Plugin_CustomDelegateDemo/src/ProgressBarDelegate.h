#pragma once

#ifndef __PROGRESSBARDELEGATE_H__
# define __PROGRESSBARDELEGATE_H__

#include <QStyledItemDelegate>

class ProgressBarDelegate : public QStyledItemDelegate
{
public:
  explicit ProgressBarDelegate(QObject* parent = nullptr);
  ~ProgressBarDelegate();
public:
  QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
  void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const override;
};

#endif // !__PROGRESSBARDELEGATE_H__
