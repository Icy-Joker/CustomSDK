#include "stdafx.h"

#include "ProgressBarDelegate.h"

#include <QApplication>
#include <QPainter>

ProgressBarDelegate::ProgressBarDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

ProgressBarDelegate::~ProgressBarDelegate()
{
}

QWidget* ProgressBarDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  return editor;
}

void ProgressBarDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  if(index.isValid())
  {
    int progress = index.data(Qt::DisplayRole).toInt();// 从模型中获取进度值

    QStyleOptionProgressBar progress_bar_option;
    progress_bar_option.rect = option.rect;
    progress_bar_option.direction = option.direction;
    progress_bar_option.minimum = 0;
    progress_bar_option.maximum = 100;
    progress_bar_option.progress = progress;
    progress_bar_option.text = QString::number(progress) + "%";
    progress_bar_option.textAlignment = option.displayAlignment;
    progress_bar_option.textVisible = true;

    painter->save();
#ifdef Q_OS_MACOS
    painter->translate(option.rect.topLeft());
#else
#endif
    qobject_cast<QWidget*>(option.styleObject)->style()->drawControl(QStyle::CE_ProgressBar,&progress_bar_option,painter,qobject_cast<QWidget*>(option.styleObject));
    painter->restore();
  }
}
