#pragma once

#ifndef __CONFIGMANAGER_H__
# define __CONFIGMANAGER_H__

#include <string>
#include <vector>

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
  template<typename TYPE>
  TYPE get(const char* key,const TYPE& default_value = TYPE());
public:
  std::vector<std::string> getPreloadModules() const;
  std::vector<std::string> getModules() const;
  std::vector<std::pair<std::string,std::string>> getExtendConfigs();
private:
  ConfigManagerPrivate* private_ptr = nullptr;
};

#endif // !__CONFIGMANAGER_H__
