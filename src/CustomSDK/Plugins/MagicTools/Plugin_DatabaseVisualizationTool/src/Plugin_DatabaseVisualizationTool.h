#pragma once

#ifndef __PLUGIN_DATABASEVISUALIZATIONTOOL_H__
# define __PLUGIN_DATABASEVISUALIZATIONTOOL_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_DatabaseVisualizationTool : public MagicTool
{
public:
  Plugin_DatabaseVisualizationTool();
  ~Plugin_DatabaseVisualizationTool() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_DATABASEVISUALIZATIONTOOL_H__
