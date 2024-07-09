#pragma once

#ifndef PLUGIN_QRCODEGENERATOR_H
# define PLUGIN_QRCODEGENERATOR_H

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_QRCodeGenerator : public MagicTool
{
public:
  Plugin_QRCodeGenerator();
  ~Plugin_QRCodeGenerator() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !PLUGIN_QRCODEGENERATOR_H
