#pragma once

#ifndef __PLUGIN_CHARTDEMO_H__
# define __PLUGIN_CHARTDEMO_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_ChartDemo : public MagicTool
{
public:
  Plugin_ChartDemo();
  ~Plugin_ChartDemo() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_CHARTDEMO_H__
