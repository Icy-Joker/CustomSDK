#pragma once

#ifndef __CONFIGMANAGER_H__
# define __CONFIGMANAGER_H__

#include <string>
#include <vector>

#include <spdlog/spdlog.h>

class ConfigManagerPrivate;
class ConfigManager
{
private:
  ConfigManager();
  ~ConfigManager();
public:
  static ConfigManager* getInstance();
public:
  bool loadConfig(const std::string& file_path);
public:
  std::vector<std::string> getPreloadModules() const;
  std::vector<std::string> getModules() const;
  std::vector<std::pair<std::string,std::string>> getExtendConfigs();
private:
  ConfigManagerPrivate* private_ptr = nullptr;

  friend class LogManager;
};

#endif // !__CONFIGMANAGER_H__
