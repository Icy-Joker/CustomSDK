#include "stdafx.h"

#include "CustomGraphicsItem.h"

#include <QGraphicsProxyWidget>
#include <QWidget>

CustomGraphicsItem::CustomGraphicsItem(QWidget* widget,QGraphicsItem* parent):
  QGraphicsRectItem(parent)
{
  assert(widget);

  if(QGraphicsProxyWidget* proxy_widget = new QGraphicsProxyWidget(this))
  {
    proxy_widget->setWidget(widget);

    this->setRect(proxy_widget->boundingRect());
  }

  this->setFlag(QGraphicsItem::ItemIsMovable,true);
}

CustomGraphicsItem::~CustomGraphicsItem()
{
}
