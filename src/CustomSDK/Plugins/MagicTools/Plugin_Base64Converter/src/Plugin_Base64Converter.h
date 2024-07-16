#pragma once

#ifndef __PLUGIN_BASE64CONVERTER_H__
# define __PLUGIN_BASE64CONVERTER_H__

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_Base64Converter : public MagicTool
{
public:
  Plugin_Base64Converter();
  ~Plugin_Base64Converter() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !__PLUGIN_BASE64CONVERTER_H__
