#include "stdafx.h"

#include "Plugin_DatabaseVisualizationTool.h"

#include <DatabaseVisualizationTool/DatabaseVisualizationTool.h>

Plugin_DatabaseVisualizationTool::Plugin_DatabaseVisualizationTool():
  MagicTool()
{
  setName("DatabaseVisualizationTool");
  setDescription("DatabaseVisualizationTool");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_DatabaseVisualizationTool::~Plugin_DatabaseVisualizationTool()
{
}

QWidget* Plugin_DatabaseVisualizationTool::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(DatabaseVisualizationTool* widget_instance = new DatabaseVisualizationTool(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  DatabaseVisualizationTool_API Plugin_DatabaseVisualizationTool* getPlugin()
  {
    static Plugin_DatabaseVisualizationTool plugin_instance;
    return &plugin_instance;
  }
}
