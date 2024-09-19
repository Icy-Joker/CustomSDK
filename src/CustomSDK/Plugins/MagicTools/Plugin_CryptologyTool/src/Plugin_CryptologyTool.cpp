#include "stdafx.h"

#include "Plugin_CryptologyTool.h"

#include <CryptologyTool/CryptologyTool.h>

Plugin_CryptologyTool::Plugin_CryptologyTool():
  MagicTool()
{
  setName("CryptologyTool");
  setDescription("CryptologyTool");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_CryptologyTool::~Plugin_CryptologyTool()
{
}

QWidget* Plugin_CryptologyTool::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(CryptologyTool* widget_instance = new CryptologyTool(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  Plugin_CryptologyTool* getPlugin()
  {
    static Plugin_CryptologyTool plugin_instance;
    return &plugin_instance;
  }
}
