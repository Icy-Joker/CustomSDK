#pragma once

#ifndef __CUSTOMGRAPHICSITEM_H__
# define __CUSTOMGRAPHICSITEM_H__

#include <QGraphicsRectItem>

class CustomGraphicsItem : public QGraphicsRectItem
{
public:
  explicit CustomGraphicsItem(QWidget* widget,QGraphicsItem* parent = nullptr);
  ~CustomGraphicsItem();
public:
};

#endif // !__CUSTOMGRAPHICSITEM_H__
