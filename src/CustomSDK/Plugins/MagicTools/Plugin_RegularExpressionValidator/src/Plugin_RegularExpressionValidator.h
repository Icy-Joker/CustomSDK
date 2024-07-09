#pragma once

#ifndef PLUGIN_REGULAREXPRESSIONVALIDATOR_H
# define PLUGIN_REGULAREXPRESSIONVALIDATOR_H

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_RegularExpressionValidator : public MagicTool
{
public:
  Plugin_RegularExpressionValidator();
  ~Plugin_RegularExpressionValidator() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !PLUGIN_REGULAREXPRESSIONVALIDATOR_H
