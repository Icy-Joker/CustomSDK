#pragma once

#ifndef ABSTRACTUIPLUGIN_H
# define ABSTRACTUIPLUGIN_H

#include <QIcon>

#include <CommonFramework/AbstractPlugin.h>

class BasicUIFramework_API AbstractUIPlugin : public AbstractPlugin
{
public:
  AbstractUIPlugin() = default;
  ~AbstractUIPlugin() override = 0;
public:
  virtual const std::string& getType() const = 0;
  virtual QIcon getIcon() const = 0;
public:
  virtual QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const = 0;
};

#endif//!ABSTRACTUIPLUGIN_H
