#pragma once

#ifndef __LOGMANAGER_H__
# define __LOGMANAGER_H__

class LogManagerPrivate;
class BasicFramework_API LogManager
{
private:
  LogManager();
  ~LogManager();
public:
  static LogManager* getInstance();
public:
  bool initializeWithConfig(const char* config_file_path);
public:
  void trace(const char* log_content);
  void debug(const char* log_content);
  void info(const char* log_content);
  void warn(const char* log_content);
  void error(const char* log_content);
  void critical(const char* log_content);
private:
  LogManagerPrivate* private_ptr;
};

#define LOG_TRACE(LOG_CONTENT) \
LogManager::getInstance()->trace(LOG_CONTENT);

#define LOG_DEBUG(LOG_CONTENT) \
LogManager::getInstance()->debug(LOG_CONTENT);

#define LOG_INFO(LOG_CONTENT) \
LogManager::getInstance()->info(LOG_CONTENT);

#define LOG_WARN(LOG_CONTENT) \
LogManager::getInstance()->warn(LOG_CONTENT);

#define LOG_ERROR(LOG_CONTENT) \
LogManager::getInstance()->error(LOG_CONTENT);

#define LOG_CRITICAL(LOG_CONTENT) \
LogManager::getInstance()->critical(LOG_CONTENT);

#endif // !__LOGMANAGER_H__
