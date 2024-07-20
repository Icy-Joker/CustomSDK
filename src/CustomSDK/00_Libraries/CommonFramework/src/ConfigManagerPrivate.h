#pragma once

#ifndef CONFIGMANAGERPRIVATE_H
# define CONFIGMANAGERPRIVATE_H

#include <string>
#include <vector>

#include <pugixml.hpp>

class ConfigManagerPrivate
{
private:
  ConfigManagerPrivate();
  ~ConfigManagerPrivate();
public:
  bool loadConfig(const std::string& file_path);
public:
  std::vector<std::string> getPreloadModules() const;
  std::vector<std::string> getModules() const;
  std::vector<std::pair<std::string,std::string>> getExtendConfigs();
private:
  pugi::xml_document doc;
private:
  friend class ConfigManager;
};

#endif//!CONFIGMANAGERPRIVATE_H
