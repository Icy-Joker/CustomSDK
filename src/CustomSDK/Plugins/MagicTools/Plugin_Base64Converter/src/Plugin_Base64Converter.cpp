#include "stdafx.h"

#include "Plugin_Base64Converter.h"

#include <Base64Converter/Base64Converter.h>

Plugin_Base64Converter::Plugin_Base64Converter():
  MagicTool()
{
  setName("Base64Converter");
  setDescription("Base64Converter");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_Base64Converter::~Plugin_Base64Converter()
{
}

QWidget* Plugin_Base64Converter::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(Base64Converter* widget_instance = new Base64Converter(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  Base64Converter_API Plugin_Base64Converter* getPlugin()
  {
    static Plugin_Base64Converter plugin_instance;
    return &plugin_instance;
  }
}
