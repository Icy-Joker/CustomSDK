#pragma once

#ifndef MICROUTILS_H
# define MICROUTILS_H

#include <string>

class BasicSupport_API MicroUtils
{
public:
  explicit MicroUtils() = default;
  ~MicroUtils() = default;
public:
  static std::string getHostName();
  static int getCurrentProcessId();
  static std::string getCurrentProcessName();
  static std::string getCurrentUser();
  static std::string getCurrentWorkingDirectory();

  static int64_t getCurrentSystemTime();
  static std::string getCurrentSystemTimeUTC();
  static std::string getCurrentSystemTimeLocal();

  static std::string generateUniqueID();
};

#endif//!MICROUTILS_H
