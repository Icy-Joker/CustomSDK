#pragma once

#ifndef ABSTRACTPLUGIN_H
# define ABSTRACTPLUGIN_H

#include <string>

class BasicFramework_API AbstractPlugin
{
public:
  AbstractPlugin();
  virtual ~AbstractPlugin() = 0;
public:
  const char* getName() const;
  const char* getDescription() const;
public:
  void setName(const std::string& name);
  void setDescription(const std::string& description);
private:
  std::string name;
  std::string description;
};

#endif // !ABSTRACTPLUGIN_H
