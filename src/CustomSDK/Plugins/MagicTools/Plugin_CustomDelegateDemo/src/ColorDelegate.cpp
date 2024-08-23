#include "stdafx.h"

#include "ColorDelegate.h"

#include <QColorDialog>
#include <QPainter>

ColorDelegate::ColorDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

ColorDelegate::~ColorDelegate()
{
}

QWidget* ColorDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  if(QColorDialog* color_dialog = new QColorDialog(parent))
  {
    color_dialog->setOption(QColorDialog::ColorDialogOption::ShowAlphaChannel,true);

    editor = color_dialog;
  }

  return editor;
}

void ColorDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const
{
  if(QColorDialog* color_dialog = qobject_cast<QColorDialog*>(editor))
  {
    color_dialog->setCurrentColor(QColor(index.data(Qt::EditRole).toString()));
  }
}

void ColorDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const
{
  if(QColorDialog* color_dialog = qobject_cast<QColorDialog*>(editor))
  {
    QColor selected_color = color_dialog->selectedColor();

    if(color_dialog->result() == QDialog::Accepted)
    {
      model->blockSignals(true);
      model->setData(index,selected_color.name(QColor::HexArgb).toUpper(),Qt::DisplayRole);
      model->setData(index,selected_color,Qt::BackgroundRole);
      model->blockSignals(false);
    }
  }
}

void ColorDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  if(index.isValid())
  {
    QString color_name = index.data(Qt::DisplayRole).toString();
    QColor current_color(color_name);
    QColor inverted_color(255 - current_color.red(),255 - current_color.green(),255 - current_color.blue());

    painter->save();
    painter->setBrush(current_color);
    painter->drawRect(option.rect);
    painter->setPen(inverted_color);
    painter->drawText(option.rect,Qt::AlignCenter,color_name);
    painter->restore();
  }
}
