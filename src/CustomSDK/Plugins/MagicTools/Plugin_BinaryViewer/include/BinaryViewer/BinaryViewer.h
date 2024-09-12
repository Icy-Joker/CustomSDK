#pragma once

#ifndef __BINARYVIEWER_H__
# define __BINARYVIEWER_H__

#include <QMainWindow>

namespace Ui
{
  class BinaryViewer;
}

class BinaryViewer : public QMainWindow
{
public:
  Q_OBJECT
public:
  explicit BinaryViewer(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~BinaryViewer();
private slots:
  void on_action_Open_triggered();
private:
  Ui::BinaryViewer* ui;
};

#endif // !__BINARYVIEWER_H__
