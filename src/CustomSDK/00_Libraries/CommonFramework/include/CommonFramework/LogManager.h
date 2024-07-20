#pragma once

#ifndef LOGMANAGER_H
# define LOGMANAGER_H

#include <string>

#include <BasicSupport/Singleton.h>

class CommonFramework_API LogManager : public Singleton<LogManager>
{
public:
  LogManager(const LogManager&) = delete;
  LogManager& operator=(const LogManager&) = delete;
private:
  LogManager();
  ~LogManager() override;
public:
  bool initializeWithConfig(const std::string& config_file_path);
public:
  void trace(const std::string& log_content);
  void debug(const std::string& log_content);
  void info(const std::string& log_content);
  void warn(const std::string& log_content);
  void error(const std::string& log_content);
  void critical(const std::string& log_content);
public:
  //@formatter:off
#ifndef SWIG
# ifdef FMT_VERSION
  template<typename ... Args>
  void trace(fmt::format_string<Args ...> fmt_content,Args&& ... args)
  {
    this->trace(fmt::format(fmt_content,std::forward<Args>(args) ...));
  }

  template<typename ... Args>
  void debug(fmt::format_string<Args ...> fmt_content,Args&& ... args)
  {
    this->trace(fmt::format(fmt_content,std::forward<Args>(args) ...));
  }

  template<typename ... Args>
  void info(fmt::format_string<Args ...> fmt_content,Args&& ... args)
  {
    this->info(fmt::format(fmt_content,std::forward<Args>(args) ...));
  }

  template<typename ... Args>
  void warn(fmt::format_string<Args ...> fmt_content,Args&& ... args)
  {
    this->warn(fmt::format(fmt_content,std::forward<Args>(args) ...));
  }

  template<typename ... Args>
  void error(fmt::format_string<Args ...> fmt_content,Args&& ... args)
  {
    this->error(fmt::format(fmt_content,std::forward<Args>(args) ...));
  }

  template<typename ... Args>
  void critical(fmt::format_string<Args ...> fmt_content,Args&& ... args)
  {
    this->critical(fmt::format(fmt_content,std::forward<Args>(args) ...));
  }
# endif
  //@formatter:on
#endif
private:
  class LogManagerPrivate* private_ptr;
private:
  friend class Singleton<LogManager>;
};

//@formatter:off
#if !defined(SWIG)  && defined(FMT_VERSION)
# define LOG_TRACE(LOG_CONTENT,...) \
LogManager::instance()->trace(LOG_CONTENT,##__VA_ARGS__);

# define LOG_DEBUG(LOG_CONTENT,...) \
LogManager::instance()->debug(LOG_CONTENT,##__VA_ARGS__);

# define LOG_INFO(LOG_CONTENT,...) \
LogManager::instance()->info(LOG_CONTENT,##__VA_ARGS__);

# define LOG_WARN(LOG_CONTENT,...) \
LogManager::instance()->warn(LOG_CONTENT,##__VA_ARGS__);

# define LOG_ERROR(LOG_CONTENT,...) \
LogManager::instance()->error(LOG_CONTENT,##__VA_ARGS__);

# define LOG_CRITICAL(LOG_CONTENT,...) \
LogManager::instance()->critical(LOG_CONTENT,##__VA_ARGS__);
#else
# define LOG_TRACE(LOG_CONTENT) \
LogManager::instance()->trace(LOG_CONTENT);

# define LOG_DEBUG(LOG_CONTENT) \
LogManager::instance()->debug(LOG_CONTENT);

# define LOG_INFO(LOG_CONTENT) \
LogManager::instance()->info(LOG_CONTENT);

# define LOG_WARN(LOG_CONTENT) \
LogManager::instance()->warn(LOG_CONTENT);

# define LOG_ERROR(LOG_CONTENT) \
LogManager::instance()->error(LOG_CONTENT);

# define LOG_CRITICAL(LOG_CONTENT) \
LogManager::instance()->critical(LOG_CONTENT);
#endif
//@formatter:on

#endif//!LOGMANAGER_H
