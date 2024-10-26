#pragma once

#ifndef __PLUGIN_MARKDOWNEDITOR_H__
# define __PLUGIN_MARKDOWNEDITOR_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_MarkDownEditor : public MagicTool
{
public:
  Plugin_MarkDownEditor();
  ~Plugin_MarkDownEditor() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_MARKDOWNEDITOR_H__
