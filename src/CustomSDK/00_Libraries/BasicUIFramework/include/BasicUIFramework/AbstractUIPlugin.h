#pragma once

#ifndef __ABSTRACTUIPLUGIN_H__
# define __ABSTRACTUIPLUGIN_H__

#include <BasicFramework/AbstractPlugin.h>

#include <QIcon>

class BasicUIFramework_API AbstractUIPlugin : public AbstractPlugin
{
public:
  AbstractUIPlugin();
  virtual ~AbstractUIPlugin();
public:
  const QIcon getIcon() const;
public:
  void setIcon(const QIcon& icon);
private:
  QIcon icon;
};

#endif // !__ABSTRACTUIPLUGIN_H__
