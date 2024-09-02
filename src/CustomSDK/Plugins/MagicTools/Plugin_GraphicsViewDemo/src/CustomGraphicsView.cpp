#include "stdafx.h"

#include "CustomGraphicsView.h"
#include "GraphicsGenerator.h"

#include <QMimeData>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>

#include <QPushButton>
#include <QLabel>

#include "StructDefinitionWidget.h"
#include "CustomGraphicsItem.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>

CustomGraphicsView::CustomGraphicsView(QWidget* parent /*= nullptr*/):
  QGraphicsView(parent)
{
  this->setAcceptDrops(true);
}

CustomGraphicsView::~CustomGraphicsView()
{
}

void CustomGraphicsView::dragEnterEvent(QDragEnterEvent* event)
{
  if(event->mimeData()->hasFormat("application/x-dnditemdata"))
  {
    event->acceptProposedAction();
  }
}

void CustomGraphicsView::dragMoveEvent(QDragMoveEvent* event)
{
  if(event->mimeData()->hasFormat("application/x-dnditemdata"))
  {
    event->acceptProposedAction();
  }
}

void CustomGraphicsView::dropEvent(QDropEvent* event)
{
  if(event->mimeData()->hasFormat("application/x-dnditemdata"))
  {
    event->acceptProposedAction();
    //获取放置位置
    QPointF screen_pos = this->mapToScene(event->position().toPoint());

    QGraphicsItem* graphics_item = nullptr;
    if(event->mimeData()->text() == QString::fromUtf8("矩形"))
    {
      graphics_item = new QGraphicsRectItem(0,0, 50, 50);
      ((QGraphicsRectItem*)graphics_item)->setBrush(Qt::blue);
    }
    else if(event->mimeData()->text() == "圆形")
    {
      graphics_item = new QGraphicsEllipseItem(0,0, 50, 50);
      ((QGraphicsEllipseItem*)graphics_item)->setBrush(Qt::green);
    }
    else if(event->mimeData()->text() == "结构体定义")
    {
      graphics_item = new CustomGraphicsItem(new StructDefinitionWidget());
    }
    else if(event->mimeData()->text() == "文本")
    {
      graphics_item = new CustomGraphicsItem(new QLabel("BBBBBBBBBBBBB"));
    }

    if(graphics_item)
    {
      graphics_item->setPos(screen_pos);
      graphics_item->setFlag(QGraphicsItem::ItemIsMovable,true);

      // 将矩形添加到场景
      this->scene()->addItem(graphics_item);
    }
  }
  else
  {
    event->ignore();
  }
}
