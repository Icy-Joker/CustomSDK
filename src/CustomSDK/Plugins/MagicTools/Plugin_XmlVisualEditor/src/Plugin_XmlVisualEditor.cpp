#include "stdafx.h"

#include "Plugin_XmlVisualEditor.h"

#include <XmlVisualEditor/XmlVisualEditor.h>

Plugin_XmlVisualEditor::Plugin_XmlVisualEditor():
  MagicTool()
{
  setName("XmlVisualEditor");
  setDescription("XmlVisualEditor");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_XmlVisualEditor::~Plugin_XmlVisualEditor()
{
}

QWidget* Plugin_XmlVisualEditor::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(XmlVisualEditor* widget_instance = new XmlVisualEditor(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  XmlVisualEditor_API Plugin_XmlVisualEditor* getPlugin()
  {
    static Plugin_XmlVisualEditor plugin_instance;
    return &plugin_instance;
  }
}
