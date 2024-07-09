#pragma once

#ifndef __PLUGIN_NETWORKTOOL_H__
# define __PLUGIN_NETWORKTOOL_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_NetworkTool : public MagicTool
{
public:
  Plugin_NetworkTool();
  ~Plugin_NetworkTool() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_NETWORKTOOL_H__
