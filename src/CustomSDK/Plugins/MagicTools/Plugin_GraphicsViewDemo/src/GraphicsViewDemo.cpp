#include "stdafx.h"

#include "GraphicsViewDemo/GraphicsViewDemo.h"
#include "ui_GraphicsViewDemo.h"

#include <QGraphicsScene>
#include <QEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QBuffer>
#include <QGraphicsRectItem>

GraphicsViewDemo::GraphicsViewDemo(QWidget* parent /*= nullptr*/,Qt::WindowFlags flags /*= Qt::WindowFlags()*/):
  QMainWindow(parent,flags),
  ui(new Ui::GraphicsViewDemo())
{
  ui->setupUi(this);

  if(QGraphicsScene* graphics_scene = new QGraphicsScene(this))
  {
    graphics_scene->setSceneRect(0,0,800,600);

    ui->graphicsView->setScene(graphics_scene);
  }
}

GraphicsViewDemo::~GraphicsViewDemo()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void GraphicsViewDemo::mousePressEvent(QMouseEvent* event)
{
  if(event->button() == Qt::LeftButton)
  {
    if(QWidget* pressed_widget = childAt(event->pos()))
    {
      if(QLabel* pressed_label = qobject_cast<QLabel*>(pressed_widget))
      {
        QByteArray output;
        QBuffer output_buffer(&output);
        output_buffer.open(QIODevice::WriteOnly);

        if(QDrag* drag = new QDrag(this))
        {
          if(QMimeData* mime_data = new QMimeData())
          {
            mime_data->setData("application/x-dnditemdata",output);
            mime_data->setText(pressed_label->text());
            drag->setMimeData(mime_data);
          }
          drag->exec(Qt::DropActions(Qt::DropAction::CopyAction));
        }
      }
    }
  }
}

void GraphicsViewDemo::on_graphicsView_customContextMenuRequested(const QPoint& pos)
{
  qDebug() << "GraphicsViewDemo::on_graphicsView_customContextMenuRequested()";
  if(QGraphicsItem* graphics_item = ui->graphicsView->scene()->itemAt(ui->graphicsView->mapToScene(pos),ui->graphicsView->transform()))
  {
    QMenu custom_menu;

    custom_menu.addAction("Delete",[=](){
      ui->graphicsView->scene()->removeItem(graphics_item->topLevelItem());
      delete graphics_item->topLevelItem();
    });

    custom_menu.exec(QCursor::pos());
  }
}
