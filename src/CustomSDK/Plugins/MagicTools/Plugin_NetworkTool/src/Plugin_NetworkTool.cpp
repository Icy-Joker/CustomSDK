#include "stdafx.h"

#include "Plugin_NetworkTool.h"

#include <NetworkTool/NetworkTool.h>

Plugin_NetworkTool::Plugin_NetworkTool():
  MagicTool()
{
  setName("NetworkTool");
  setDescription("NetworkTool");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_NetworkTool::~Plugin_NetworkTool()
{
}

QWidget* Plugin_NetworkTool::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(NetworkTool* widget_instance = new NetworkTool(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  NetworkTool_API Plugin_NetworkTool* getPlugin()
  {
    static Plugin_NetworkTool plugin_instance;
    return &plugin_instance;
  }
}
