#pragma once

#ifndef ABSTRACTPLUGIN_H
# define ABSTRACTPLUGIN_H

class CommonFramework_API AbstractPlugin
{
public:
  AbstractPlugin() = default;
  virtual ~AbstractPlugin() = 0;
public:
  virtual const char* getName() const = 0;//插件名称
  virtual const char* getDescription() const = 0;//插件描述
};

#endif//!ABSTRACTPLUGIN_H
