#include "stdafx.h"

#include "ComboBoxDelegate.h"

#include <QApplication>
#include <QComboBox>
#include <QEvent>
#include <QPainter>

ComboBoxDelegate::ComboBoxDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

ComboBoxDelegate::~ComboBoxDelegate()
{
}

QWidget* ComboBoxDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  if(QComboBox* combo_box = new QComboBox(parent))
  {
    combo_box->addItem("Item 0");
    combo_box->addItem("Item 1");
    combo_box->addItem("Item 2");
    combo_box->addItem("Item 3");

    editor = combo_box;
  }

  return editor;
}

void ComboBoxDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const
{
  if(QComboBox* combo_box = qobject_cast<QComboBox*>(editor))
  {
    QString current_text = index.data(Qt::EditRole).toString();

    combo_box->setCurrentIndex(combo_box->findText(current_text,Qt::MatchExactly));
  }
}

void ComboBoxDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex& index) const
{
  if(QComboBox* combo_box = qobject_cast<QComboBox*>(editor))
  {
    QString combo_box_text = combo_box->currentText();

    model->blockSignals(true);
    model->setData(index,combo_box_text,Qt::DisplayRole);
    model->blockSignals(false);
  }
}

/*
  void ComboBoxDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
  {
    QStyleOptionComboBox combo_box_option;
    combo_box_option.rect = option.rect;
    combo_box_option.editable = true;
    combo_box_option.state = option.state;
    combo_box_option.direction = QApplication::layoutDirection();
    combo_box_option.activeSubControls = QStyle::SC_ComboBoxListBoxPopup;

    painter->save();
    qobject_cast<QWidget*>(option.styleObject)->style()->drawComplexControl(QStyle::CC_ComboBox,&combo_box_option,painter);
    painter->restore();
  }
*/
