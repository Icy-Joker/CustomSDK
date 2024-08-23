#pragma once

#ifndef __PLUGIN_CUSTOMDELEGATEDEMO_H__
# define __PLUGIN_CUSTOMDELEGATEDEMO_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_CustomDelegateDemo : public MagicTool
{
public:
  Plugin_CustomDelegateDemo();
  ~Plugin_CustomDelegateDemo() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_CUSTOMDELEGATEDEMO_H__
