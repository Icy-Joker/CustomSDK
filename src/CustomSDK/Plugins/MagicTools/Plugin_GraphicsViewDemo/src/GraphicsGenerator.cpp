#include "stdafx.h"

#include "GraphicsGenerator.h"

#include <QBrush>

GraphicsGenerator::GraphicsGenerator()
{
}

GraphicsGenerator::~GraphicsGenerator()
{
}

GraphicsGenerator* GraphicsGenerator::getInstance()
{
  static GraphicsGenerator instance;
  return &instance;
}

QGraphicsItem* GraphicsGenerator::createRectangle()
{
  QGraphicsItem* result = nullptr;

  // 在放置位置创建一个矩形
  if(QGraphicsRectItem* graphics_rect_item = new QGraphicsRectItem())
  {
    graphics_rect_item->setFlag(QGraphicsItem::ItemIsMovable,true);
    graphics_rect_item->setBrush(QBrush(Qt::blue));// 使用蓝色填充

    result = graphics_rect_item;
  }

  return result;
}

QGraphicsItem* GraphicsGenerator::createCircle()
{
  QGraphicsItem* result = nullptr;

  return result;
}

QGraphicsItem* GraphicsGenerator::createTriangle()
{
  QGraphicsItem* result = nullptr;

  return result;
}

QGraphicsItem* GraphicsGenerator::createText()
{
  QGraphicsItem* result = nullptr;

  return result;
}
