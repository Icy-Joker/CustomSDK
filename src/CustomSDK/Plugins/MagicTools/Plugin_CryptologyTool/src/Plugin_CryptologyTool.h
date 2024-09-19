#pragma once

#ifndef __PLUGIN_CRYPTOLOGYTOOL_H__
# define __PLUGIN_CRYPTOLOGYTOOL_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_CryptologyTool : public MagicTool
{
public:
  Plugin_CryptologyTool();
  ~Plugin_CryptologyTool() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_CRYPTOLOGYTOOL_H__
