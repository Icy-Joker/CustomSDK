#include "stdafx.h"

#include "Plugin_ChartDemo.h"

#include <ChartDemo/ChartDemo.h>

Plugin_ChartDemo::Plugin_ChartDemo():
  MagicTool()
{
  setName("ChartDemo");
  setDescription("ChartDemo");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_ChartDemo::~Plugin_ChartDemo()
{
}

QWidget* Plugin_ChartDemo::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(ChartDemo* widget_instance = new ChartDemo(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  ChartDemo_API Plugin_ChartDemo* getPlugin()
  {
    static Plugin_ChartDemo plugin_instance;
    return &plugin_instance;
  }
}
