#pragma once

#ifndef LOGMANAGERPRIVATE_H
# define LOGMANAGERPRIVATE_H

class LogManagerPrivate
{
private:
  LogManagerPrivate();
  ~LogManagerPrivate();
private:
  bool initializeWithConfig(const char* config_path);
private:
  void trace(const char* log_content);
  void debug(const char* log_content);
  void info(const char* log_content);
  void warn(const char* log_content);
  void error(const char* log_content);
  void critical(const char* log_content);
private:
  friend class LogManager;
};

#endif//!LOGMANAGERPRIVATE_H
