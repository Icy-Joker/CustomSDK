#include "stdafx.h"

#include "SliderDelegate.h"

SliderDelegate::SliderDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

SliderDelegate::~SliderDelegate()
{
}

QWidget* SliderDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  if(QSlider* slider = new QSlider(Qt::Horizontal,parent))
  {
    slider->setMinimum(0);
    slider->setMaximum(100);

    editor = slider;
  }

  return editor;
}

void SliderDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const
{
  if(QSlider* slider = qobject_cast<QSlider*>(editor))
  {
    slider->setValue(index.model()->data(index,Qt::EditRole).toInt());
  }
}

void SliderDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const
{
  if(QSlider* slider = qobject_cast<QSlider*>(editor))
  {
    int slider_value = slider->value();

    model->blockSignals(true);
    model->setData(index,slider_value,Qt::DisplayRole);
    model->blockSignals(false);
  }
}

// void SliderDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
// {
//   QStyleOptionSlider slider_option;
//   slider_option.rect = option.rect;
//   slider_option.direction = option.direction;
//   slider_option.minimum = 0;
//   slider_option.maximum = 100;
//   slider_option.orientation = Qt::Horizontal;
//
//   painter->save();
//   painter->translate(option.rect.left(),0);
//   qobject_cast<QWidget*>(option.styleObject)->style()->drawComplexControl(QStyle::CC_Slider,&slider_option,painter);
//   painter->restore();
// }
