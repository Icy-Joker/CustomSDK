#pragma once

#ifndef ABSTRACTPLUGIN_H
# define ABSTRACTPLUGIN_H

#include <string>

class CommonFramework_API AbstractPlugin
{
public:
  AbstractPlugin() = default;
  virtual ~AbstractPlugin() = 0;
public:
  virtual const std::string& getName() const = 0;//插件名称
  virtual const std::string& getDescription() const = 0;//插件描述
};

#endif//!ABSTRACTPLUGIN_H
