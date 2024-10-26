#include "stdafx.h"

#include "Plugin_MarkDownEditor.h"

#include <MarkDownEditor/MarkDownEditor.h>

Plugin_MarkDownEditor::Plugin_MarkDownEditor():
  MagicTool()
{
  setName("MarkDownEditor");
  setDescription("MarkDownEditor");
  setIcon(QIcon(":/icons/icon.png"));
  setType("常规");
}

Plugin_MarkDownEditor::~Plugin_MarkDownEditor()
{
}

QWidget* Plugin_MarkDownEditor::createInstance(QWidget* parent,Qt::WindowFlags flags) const
{
  QWidget* result = nullptr;

  if(MarkDownEditor* widget_instance = new MarkDownEditor(parent,flags))
  {
    result = widget_instance;
  }

  return result;
}

extern "C"
{
  Plugin_MarkDownEditor* getPlugin()
  {
    static Plugin_MarkDownEditor plugin_instance;
    return &plugin_instance;
  }
}
