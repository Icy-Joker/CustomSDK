#pragma once

#ifndef LOGMANAGERPRIVATE_H
# define LOGMANAGERPRIVATE_H

#include <string>

class LogManagerPrivate
{
private:
  LogManagerPrivate();
  ~LogManagerPrivate();
private:
  bool initializeWithConfig(const std::string& config_path);
private:
  void trace(const std::string& log_content);
  void debug(const std::string& log_content);
  void info(const std::string& log_content);
  void warn(const std::string& log_content);
  void error(const std::string& log_content);
  void critical(const std::string& log_content);
private:
  friend class LogManager;
};

#endif//!LOGMANAGERPRIVATE_H
