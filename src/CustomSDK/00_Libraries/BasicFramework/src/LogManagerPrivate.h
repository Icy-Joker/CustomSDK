#pragma once

#ifndef __LOGMANAGERPRIVATE_H__
# define __LOGMANAGERPRIVATE_H__

class LogManagerPrivate
{
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

#endif // !__LOGMANAGERPRIVATE_H__
