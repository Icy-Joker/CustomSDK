#pragma once

#ifndef __PLUGIN_XMLVISUALEDITOR_H__
# define __PLUGIN_XMLVISUALEDITOR_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_XmlVisualEditor : public MagicTool
{
public:
  Plugin_XmlVisualEditor();
  ~Plugin_XmlVisualEditor() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_XMLVISUALEDITOR_H__
