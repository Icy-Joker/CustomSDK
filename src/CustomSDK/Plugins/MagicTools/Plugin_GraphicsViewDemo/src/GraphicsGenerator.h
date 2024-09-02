#pragma once

#ifndef __GRAPHICSGENERATOR_H__
# define __GRAPHICSGENERATOR_H__

#include <QGraphicsItem>

class GraphicsGenerator : public QObject
{
  Q_OBJECT
private:
  GraphicsGenerator();
  ~GraphicsGenerator();
public:
  static GraphicsGenerator* getInstance();
public:
  QGraphicsItem* createRectangle();
  QGraphicsItem* createCircle();
  QGraphicsItem* createTriangle();
  QGraphicsItem* createText();
};

#endif // !__GRAPHICSGENERATOR_H__
