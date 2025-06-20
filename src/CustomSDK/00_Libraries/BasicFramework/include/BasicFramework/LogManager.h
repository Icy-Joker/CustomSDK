#pragma once

#ifndef __LOGMANAGER_H__
# define __LOGMANAGER_H__

#include <BasicSupport/Singleton.h>

class LogManagerPrivate;

class BasicFramework_API LogManager : public Singleton<LogManager>
{
public:
  LogManager(const LogManager&) = delete;
  LogManager& operator=(const LogManager&) = delete;
private:
  LogManager();
  ~LogManager() override;
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

  friend class Singleton<LogManager>;
};

#define LOG_TRACE(LOG_CONTENT) \
LogManager::instance()->trace(LOG_CONTENT);

#define LOG_DEBUG(LOG_CONTENT) \
LogManager::instance()->debug(LOG_CONTENT);

#define LOG_INFO(LOG_CONTENT) \
LogManager::instance()->info(LOG_CONTENT);

#define LOG_WARN(LOG_CONTENT) \
LogManager::instance()->warn(LOG_CONTENT);

#define LOG_ERROR(LOG_CONTENT) \
LogManager::instance()->error(LOG_CONTENT);

#define LOG_CRITICAL(LOG_CONTENT) \
LogManager::instance()->critical(LOG_CONTENT);

#endif // !__LOGMANAGER_H__
