#include "stdafx.h"

#include <BasicSupport/MicroUtils.h>

#include <sstream>
#include <iomanip>

#include <boost/predef.h>
#include <boost/filesystem.hpp>
#include <boost/uuid.hpp>

#if defined(BOOST_OS_WINDOWS_AVAILABLE)
#include <Windows.h>
#elif defined(BOOST_OS_MACOS_AVAILABLE)
#include <mach-o/dyld.h>
#include <unistd.h>
#include <libgen.h>
#elif defined(BOOST_OS_LINUX_AVAILABLE)
#include <linux/limits.h>
#include <unistd.h>
#endif

std::string MicroUtils::getHostName()
{
  std::string result = "unknown_host";

  //@formatter:off
#if defined(BOOST_OS_WINDOWS_AVAILABLE)
  char buffer[MAX_COMPUTERNAME_LENGTH + 1] = {0};
  DWORD size = sizeof(buffer);
  if(GetComputerNameA(buffer,&size))
  {
    result = std::string(buffer);
  }
#elif defined(BOOST_OS_MACOS_AVAILABLE) or defined(BOOST_OS_LINUX_AVAILABLE)
  char buffer[256] = {0};
  if(gethostname(buffer,sizeof(buffer)) == 0)
  {
    result = std::string(buffer);
  }
#endif
  //@formatter:on

  return result;
}

int MicroUtils::getCurrentProcessId()
{
  int result = -1;

  //@formatter:off
#if defined(BOOST_OS_WINDOWS_AVAILABLE)
  result = static_cast<int>(GetCurrentProcessId());
# elif defined(BOOST_OS_MACOS_AVAILABLE) or defined(BOOST_OS_LINUX_AVAILABLE)
  return static_cast<int>(getpid());
# endif
  //@formatter:on

  return result;
}

std::string MicroUtils::getCurrentProcessName()
{
  std::string result = "unknown_process";

  //@formatter:off
#if defined(BOOST_OS_WINDOWS_AVAILABLE)
  char buffer[MAX_PATH] = {0};
  GetModuleFileNameA(nullptr,buffer,MAX_PATH);
  if (buffer)
  {
    result = boost::filesystem::path(buffer).stem().string();
  }
# elif defined(BOOST_OS_MACOS_AVAILABLE)
  char buffer[PATH_MAX] = {0};
  uint32_t size = sizeof(buffer);
  if(_NSGetExecutablePath(buffer,&size) == 0)
  {
    result = boost::filesystem::path(buffer).stem().string();
  }
#elif defined(BOOST_OS_LINUX_AVAILABLE)
  char buffer[PATH_MAX] = {0};
  std::size_t len = readlink("/proc/self/exe",buffer,sizeof(buffer) - 1);
  if(len != -1)
  {
    result = boost::filesystem::path(buffer).stem().string();
  }
# endif
  //@formatter:on

  return result;
}

std::string MicroUtils::getCurrentUser()
{
  std::string result = "unknown_user";

  //@formatter:off
#if defined(BOOST_OS_WINDOWS_AVAILABLE)
  char username[256];
  DWORD size = sizeof(username);
  if(GetUserNameA(username,&size))
  {
    result = std::string(username);
  }
# elif defined(BOOST_OS_MACOS_AVAILABLE) or defined(BOOST_OS_LINUX_AVAILABLE)
  if(const char* user = getenv("USER"))
  {
    result = std::string(user);
  }
# endif
  //@formatter:on

  return result;
}

std::string MicroUtils::getCurrentWorkingDirectory()
{
  std::string result = "unknown_directory";

  //@formatter:off
#if defined(BOOST_OS_WINDOWS_AVAILABLE)
  char buffer[MAX_PATH] = {0};
  if(GetCurrentDirectoryA(MAX_PATH,buffer) > 0)
  {
    result = boost::filesystem::path(buffer).generic_string();
  }
#elif defined(BOOST_OS_MACOS_AVAILABLE) or defined(BOOST_OS_LINUX_AVAILABLE)
  char buffer[PATH_MAX] = {0};
  if(getcwd(buffer,sizeof(buffer)))
  {
    result = boost::filesystem::path(buffer).generic_string();
  }
#endif
  //@formatter:on

  return result;
}

int64_t MicroUtils::getCurrentSystemTime()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string MicroUtils::getCurrentSystemTimeUTC()
{
  int64_t system_current_time = getCurrentSystemTime();

  std::time_t seconds = system_current_time / 1000;
  uint16_t milliseconds = system_current_time % 1000;

  // 转换为 UTC 时间结构体
  std::tm* utc_tm = std::gmtime(&seconds);

  std::stringstream ss;
  ss << std::put_time(utc_tm,"%Y-%m-%d %H:%M:%S");
  ss << "." << std::setfill('0') << std::setw(3) << milliseconds;

  return ss.str();
}

std::string MicroUtils::getCurrentSystemTimeLocal()
{
  int64_t system_current_time = getCurrentSystemTime();

  std::time_t seconds = system_current_time / 1000;
  uint16_t milliseconds = system_current_time % 1000;

  // 转换为本地时间结构体
  std::tm* local_tm = std::localtime(&seconds);

  std::stringstream ss;
  ss << std::put_time(local_tm,"%Y-%m-%d %H:%M:%S");
  ss << "." << std::setfill('0') << std::setw(3) << milliseconds;

  return ss.str();
}

std::string MicroUtils::generateUniqueID()
{
  boost::uuids::random_generator generator;

  return boost::uuids::to_string(generator());
}
