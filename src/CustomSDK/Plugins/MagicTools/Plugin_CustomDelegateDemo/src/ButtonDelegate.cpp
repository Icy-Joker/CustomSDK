#include "stdafx.h"

#include "ButtonDelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QHBoxLayout>

ButtonDelegate::ButtonDelegate(QObject* parent):
  QStyledItemDelegate(parent)
{
}

ButtonDelegate::~ButtonDelegate()
{
}

QWidget* ButtonDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  QWidget* editor = nullptr;

  return editor;
}

void ButtonDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
  painter->save();

  QStyleOptionButton tool_button_a_option;
  tool_button_a_option.text = "test";
  tool_button_a_option.direction = option.direction;
  tool_button_a_option.rect = QRect(option.rect.left(),option.rect.top(),option.rect.width() / 2,option.rect.height());
  tool_button_a_option.state = QStyle::State_Enabled;

  QStyleOptionButton tool_button_b_option;
  tool_button_b_option.text = "test2";
  tool_button_b_option.direction = option.direction;
  tool_button_b_option.rect = QRect(option.rect.left() + option.rect.width() / 2,option.rect.top(),option.rect.width() / 2,option.rect.height());
  tool_button_b_option.state = QStyle::State_Enabled;

  tool_button_a_option.state |= QStyle::State_Raised;
  tool_button_b_option.state |= QStyle::State_Raised;

  if(bool checked = index.data(Qt::ItemDataRole::CheckStateRole).value<Qt::CheckState>() == Qt::Checked)
  {
    if(tool_button_a_option.rect.contains(option.widget->mapFromGlobal(QCursor::pos())))
    {
      qDebug() << "A";
      tool_button_a_option.state |= QStyle::State_Sunken;
    }
    else if(tool_button_b_option.rect.contains(option.widget->mapFromGlobal(QCursor::pos())))
    {
      qDebug() << "B";
      tool_button_b_option.state |= QStyle::State_Sunken;
    }
    else
    {
      qDebug() << "C";
    }
    qDebug() << option.widget->rect() << "|" << tool_button_a_option.rect << option.widget->mapFromGlobal(QCursor::pos());
  }
  else
  {
  }

  qobject_cast<QWidget*>(option.styleObject)->style()->drawPrimitive(QStyle::PE_PanelButtonCommand,&tool_button_a_option,painter,qobject_cast<QWidget*>(option.styleObject));
  qobject_cast<QWidget*>(option.styleObject)->style()->drawPrimitive(QStyle::PE_FrameDefaultButton,&tool_button_a_option,painter,qobject_cast<QWidget*>(option.styleObject));
  qobject_cast<QWidget*>(option.styleObject)->style()->drawControl(QStyle::CE_PushButton,&tool_button_a_option,painter,qobject_cast<QWidget*>(option.styleObject));

  qobject_cast<QWidget*>(option.styleObject)->style()->drawPrimitive(QStyle::PE_PanelButtonCommand,&tool_button_b_option,painter,qobject_cast<QWidget*>(option.styleObject));
  qobject_cast<QWidget*>(option.styleObject)->style()->drawPrimitive(QStyle::PE_FrameDefaultButton,&tool_button_b_option,painter,qobject_cast<QWidget*>(option.styleObject));
  qobject_cast<QWidget*>(option.styleObject)->style()->drawControl(QStyle::CE_PushButton,&tool_button_b_option,painter,qobject_cast<QWidget*>(option.styleObject));

  //qDebug() << qobject_cast<QWidget*>(option.styleObject)->style()->subElementRect(QStyle::SE_PushButtonLayoutItem,&option,qobject_cast<QWidget*>(option.styleObject));

  painter->restore();
}

bool ButtonDelegate::editorEvent(QEvent* event,QAbstractItemModel* model,const QStyleOptionViewItem& option,const QModelIndex& index)
{
  bool result = false;

  if(QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event))
  {
    //model->blockSignals(true);
    switch(mouse_event->type())
    {
      case QMouseEvent::MouseButtonPress:
      {
        model->setData(index,Qt::CheckState::Checked,Qt::ItemDataRole::CheckStateRole);
        break;
      }
      case QMouseEvent::MouseButtonRelease:
      {
        model->setData(index,Qt::CheckState::Unchecked,Qt::ItemDataRole::CheckStateRole);
        break;
      }
      default:
      {
        break;
      }
    }
    //model->blockSignals(false);
  }
  //result = QStyledItemDelegate::editorEvent(event,model,option,index);

  return result;
}
