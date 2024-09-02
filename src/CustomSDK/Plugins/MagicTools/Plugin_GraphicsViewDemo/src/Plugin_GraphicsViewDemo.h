#pragma once

#ifndef __PLUGIN_GRAPHICSVIEWDEMO_H__
# define __PLUGIN_GRAPHICSVIEWDEMO_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_GraphicsViewDemo : public MagicTool
{
public:
  Plugin_GraphicsViewDemo();
  ~Plugin_GraphicsViewDemo() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_GRAPHICSVIEWDEMO_H__
