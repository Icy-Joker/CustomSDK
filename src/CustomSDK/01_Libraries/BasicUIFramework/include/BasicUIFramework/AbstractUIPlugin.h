#pragma once

#ifndef ABSTRACTUIPLUGIN_H
# define ABSTRACTUIPLUGIN_H

# include <QIcon>

# include <CommonFramework/AbstractPlugin.h>

class BasicUIFramework_API AbstractUIPlugin : public AbstractPlugin
{
public:
  AbstractUIPlugin();
  ~AbstractUIPlugin() override = 0;
public:
  const std::string& getType() const;
  void setType(const std::string& type);

  const QIcon& getIcon() const;
  void setIcon(const QIcon& icon);
public:
  virtual QWidget* createInstance(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags()) const = 0;
private:
  class AbstractUIPluginPrivate* private_ptr;
};

#endif
