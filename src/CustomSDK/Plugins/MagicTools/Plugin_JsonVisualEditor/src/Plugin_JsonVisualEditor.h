#pragma once

#ifndef __PLUGIN_JSONVISUALEDITOR_H__
# define __PLUGIN_JSONVISUALEDITOR_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_JsonVisualEditor : public MagicTool
{
public:
  Plugin_JsonVisualEditor();
  ~Plugin_JsonVisualEditor() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_JSONVISUALEDITOR_H__
