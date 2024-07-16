#pragma once

#ifndef __DATABASEVISUALIZATIONTOOL_H__
# define __DATABASEVISUALIZATIONTOOL_H__

#include <QMainWindow>

namespace Ui
{
  class DatabaseVisualizationTool;
}

class DatabaseVisualizationTool : public QMainWindow
{
  Q_OBJECT
public:
  explicit DatabaseVisualizationTool(QWidget *parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags());
  ~DatabaseVisualizationTool() override;
private:
  Ui::DatabaseVisualizationTool *ui;
};

#endif // !__DATABASEVISUALIZATIONTOOL_H__
