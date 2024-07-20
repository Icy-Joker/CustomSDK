#pragma once

#ifndef ABSTRACTPLUGIN_H
# define ABSTRACTPLUGIN_H

# include <string>

class CommonFramework_API AbstractPlugin
{
public:
  AbstractPlugin();
  virtual ~AbstractPlugin() = 0;
public:
  const std::string& getName() const;
  void setName(const std::string& name);

  const std::string& getDescription() const;
  void setDescription(const std::string& description);
private:
  class AbstractPluginPrivate* private_ptr;
};

#endif
