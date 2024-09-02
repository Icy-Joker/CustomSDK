#pragma once

#ifndef __GRAPHICSVIEWDEMO_H__
# define __GRAPHICSVIEWDEMO_H__

#include <QMainWindow>

namespace Ui
{
  class GraphicsViewDemo;
}

class GraphicsViewDemo : public QMainWindow
{
  Q_OBJECT
public:
  explicit GraphicsViewDemo(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~GraphicsViewDemo() override;
protected:
  void mousePressEvent(QMouseEvent* event) override;
private slots:
  void on_graphicsView_customContextMenuRequested(const QPoint& pos);
private:
  Ui::GraphicsViewDemo* ui;
};

#endif // !__GRAPHICSVIEWDEMO_H__
