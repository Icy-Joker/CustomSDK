#include "stdafx.h"

#include "DoubleSpinBoxDelegate.h"

#include <QDoubleSpinBox>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

DoubleSpinBoxDelegate::~DoubleSpinBoxDelegate()
{
}

QWidget* DoubleSpinBoxDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  if(QDoubleSpinBox* double_spin_box = new QDoubleSpinBox(parent))
  {
    double_spin_box->setMinimum(0.00);
    double_spin_box->setMaximum(100.00);

    editor = double_spin_box;
  }

  return editor;
}

void DoubleSpinBoxDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const
{
  if(QDoubleSpinBox* double_spin_box = qobject_cast<QDoubleSpinBox*>(editor))
  {
    double_spin_box->setValue(index.model()->data(index,Qt::EditRole).toDouble());
  }
}

void DoubleSpinBoxDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const
{
  if(QDoubleSpinBox* double_spin_box = qobject_cast<QDoubleSpinBox*>(editor))
  {
    QString double_spin_box_text = QString::number(double_spin_box->value());

    model->blockSignals(true);
    model->setData(index,double_spin_box_text,Qt::DisplayRole);
    model->blockSignals(false);
  }
}

// void DoubleSpinBoxDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
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
