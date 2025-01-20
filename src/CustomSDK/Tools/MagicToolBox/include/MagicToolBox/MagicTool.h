#pragma once

#ifndef __MAGICTOOL_H__
# define __MAGICTOOL_H__

#include <QWidget>

#include <string>
#include <BasicUIFramework/AbstractUIPlugin.h>

class MagicTool : public AbstractUIPlugin
{
public:
  MagicTool():
    AbstractUIPlugin()
  {
  };

  virtual ~MagicTool()
  {
  }
public:
  const char* getType() const
  {
    return this->type.c_str();
  }
public:
  void setType(const std::string& name)
  {
    this->type = name;
  }
public:
  virtual QWidget* createInstance(QWidget* parent = nullptr,Qt::WindowFlags flags = Qt::WindowFlags()) const = 0;
protected:
  std::string type;
};

#endif // !__MAGICTOOL_H__
