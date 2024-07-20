#pragma once

#ifndef __CONFIGMANAGERPRIVATE_H__
# define __CONFIGMANAGERPRIVATE_H__

#include <string>
#include <vector>

#include <pugixml.hpp>
#include <spdlog/spdlog.h>

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
  std::vector<spdlog::sink_ptr> getLoggers() const;
  std::vector<std::pair<std::string,std::string>> getExtendConfigs();
private:
  pugi::xml_document doc;

  friend class ConfigManager;
  friend class LogManager;
};

#endif // !__CONFIGMANAGERPRIVATE_H__
