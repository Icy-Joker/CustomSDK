#pragma once

#ifndef __NETWORKTOOL_H__
# define __NETWORKTOOL_H__

#include <QMainWindow>

namespace Ui
{
  class NetworkTool;
}

class NetworkTool : public QMainWindow
{
  Q_OBJECT
public:
  explicit NetworkTool(QWidget *parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~NetworkTool() override;
private:
  Ui::NetworkTool *ui;
};

#endif // !__NETWORKTOOL_H__
