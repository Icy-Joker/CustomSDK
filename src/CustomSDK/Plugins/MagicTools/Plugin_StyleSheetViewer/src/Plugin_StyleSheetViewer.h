#pragma once

#ifndef PLUGIN_STYLESHEETVIEWER_H
# define PLUGIN_STYLESHEETVIEWER_H

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_StyleSheetViewer : public MagicTool
{
public:
  Plugin_StyleSheetViewer();
  ~Plugin_StyleSheetViewer() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !PLUGIN_STYLESHEETVIEWER_H
