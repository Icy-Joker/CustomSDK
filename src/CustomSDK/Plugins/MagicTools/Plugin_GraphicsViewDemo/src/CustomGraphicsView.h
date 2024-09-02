#pragma once

#ifndef __CUSTOMGRAPHICSVIEW_H__
# define __CUSTOMGRAPHICSVIEW_H__

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
  Q_OBJECT
public:
  explicit CustomGraphicsView(QWidget* parent = nullptr);
  ~CustomGraphicsView();
protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;
};

#endif // !__CUSTOMGRAPHICSVIEW_H__
