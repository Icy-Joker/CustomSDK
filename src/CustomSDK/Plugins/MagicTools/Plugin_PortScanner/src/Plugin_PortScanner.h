#pragma once

#ifndef __PLUGIN_PORTSCANNER_H__
# define __PLUGIN_PORTSCANNER_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_PortScanner : public MagicTool
{
public:
  Plugin_PortScanner();
  ~Plugin_PortScanner() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_PORTSCANNER_H__
