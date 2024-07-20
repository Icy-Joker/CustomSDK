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
};

#endif//!MICROUTILS_H
