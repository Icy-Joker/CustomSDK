#include "stdafx.h"

#include "Plugin_BinaryViewer.h"

#include <BinaryViewer/BinaryViewer.h>

Plugin_BinaryViewer::Plugin_BinaryViewer():
  MagicTool()
{
  setName("BinaryViewer");
  setDescription("BinaryViewer");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_BinaryViewer::~Plugin_BinaryViewer()
{
}

QWidget* Plugin_BinaryViewer::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(BinaryViewer* widget_instance = new BinaryViewer(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  Plugin_BinaryViewer* getPlugin()
  {
    static Plugin_BinaryViewer plugin_instance;
    return &plugin_instance;
  }
}
