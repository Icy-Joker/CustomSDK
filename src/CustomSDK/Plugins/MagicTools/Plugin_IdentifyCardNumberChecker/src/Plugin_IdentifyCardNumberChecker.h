#pragma once

#ifndef PLUGIN_IDENTIFYCARDNUMBERCHECKER_H
# define PLUGIN_IDENTIFYCARDNUMBERCHECKER_H

#include <MagicToolBox/MagicTool.h>

#include <QWidget>

class Plugin_IdentifyCardNumberChecker : public MagicTool
{
public:
  Plugin_IdentifyCardNumberChecker();
  ~Plugin_IdentifyCardNumberChecker() override;
public:
  QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const override;
};

#endif // !PLUGIN_IDENTIFYCARDNUMBERCHECKER_H
