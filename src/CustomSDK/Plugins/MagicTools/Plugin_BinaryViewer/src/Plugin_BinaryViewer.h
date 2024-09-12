#pragma once

#ifndef __PLUGIN_BINARYVIEWER_H__
# define __PLUGIN_BINARYVIEWER_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_BinaryViewer : public MagicTool
{
public:
  Plugin_BinaryViewer();
  ~Plugin_BinaryViewer() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_BINARYVIEWER_H__
