#pragma once

#ifndef CONFIGMANAGER_H
# define CONFIGMANAGER_H

#include <BasicSupport/Singleton.h>

#include <string>
#include <vector>

class ConfigManagerPrivate;

class ConfigManager : public Singleton<ConfigManager>
{
public:
  ConfigManager(const Singleton&) = delete;
  ConfigManager& operator=(const ConfigManager&) = delete;
private:
  ConfigManager();
  ~ConfigManager() override;
public:
  bool loadConfig(const std::string& file_path);
public:
  template<typename TYPE>
  TYPE get(const char* key,const TYPE& default_value = TYPE());
public:
  std::vector<std::string> getPreloadModules() const;
  std::vector<std::string> getModules() const;
  std::vector<std::pair<std::string,std::string>> getExtendConfigs();
private:
  ConfigManagerPrivate* private_ptr = nullptr;
private:
  friend class Singleton<ConfigManager>;
};

#endif//!CONFIGMANAGER_H
