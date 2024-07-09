#include "stdafx.h"

#include "Plugin_SerialPortDebugger.h"

#include <SerialPortDebugger/SerialPortDebugger.h>

Plugin_SerialPortDebugger::Plugin_SerialPortDebugger():
  MagicTool()
{
  setName("SerialPortDebugger");
  setDescription("SerialPortDebugger");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_SerialPortDebugger::~Plugin_SerialPortDebugger()
{
}

QWidget* Plugin_SerialPortDebugger::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(SerialPortDebugger* widget_instance = new SerialPortDebugger(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  SerialPortDebugger_API Plugin_SerialPortDebugger* getPlugin()
  {
    static Plugin_SerialPortDebugger plugin_instance;
    return &plugin_instance;
  }
}
