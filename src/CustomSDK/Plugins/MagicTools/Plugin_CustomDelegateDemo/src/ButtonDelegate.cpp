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
  {
    QStyleOptionButton tool_button_a_option;
    tool_button_a_option.text = "a";
    tool_button_a_option.direction = option.direction;
    tool_button_a_option.rect = QRect(option.rect.left(),option.rect.top(),option.rect.width() / 2,option.rect.height());
    tool_button_a_option.state = QStyle::State_Enabled;

    QPushButton push_button;
    push_button.setStyleSheet("QPushButton{border-width: 0px;\
                                position: absolute;\
                                left: 0px;\
                                top: 0px;\
                                max-width: 80px;\
                                width:80px;\
                                height: 30px;\
                                background: inherit;\
                                background-color: rgba(255, 255, 255, 0);\
                                border-width: 1px;\
                                border-style: solid;\
                                border-color: red;\
                                border-radius: 10px;\
                                font-size: 11px;\
                                color: red;}\
                                QPushButton:hover{background-color:red; color:#FFFFFF;}");
    push_button.style()->drawControl(QStyle::CE_PushButton,&tool_button_a_option,painter,&push_button);
  }
  {
    QStyleOptionButton tool_button_b_option;
    tool_button_b_option.text = "b";
    tool_button_b_option.direction = option.direction;
    tool_button_b_option.rect = QRect(option.rect.left() + option.rect.width() / 2,option.rect.top(),option.rect.width() / 2,option.rect.height());
    tool_button_b_option.state = QStyle::State_Enabled;

    QPushButton push_button;
    push_button.setStyleSheet("QPushButton{border-width: 0px;\
                                position: absolute;\
                                left: 0px;\
                                top: 0px;\
                                max-width:120px; \
                                width:120px;\
                                height: 30px;\
                                background: inherit;\
                                background-color: rgba(255, 255, 255, 0);\
                                border-width: 1px;\
                                border-style: solid;\
                                border-color: rgba(2, 182, 212, 1);\
                                border-radius: 10px;\
                                font-size: 11px;\
                                color: #000000;}\
                                QPushButton:hover{background-color:rgba(2, 182, 212, 1); color:#FFFFFF;}");
    push_button.style()->drawControl(QStyle::CE_PushButton,&tool_button_b_option,painter,&push_button);
  }
}

bool ButtonDelegate::editorEvent(QEvent* event,QAbstractItemModel* model,const QStyleOptionViewItem& option,const QModelIndex& index)
{
  bool result = false;

  result = QStyledItemDelegate::editorEvent(event,model,option,index);

  return result;
}
