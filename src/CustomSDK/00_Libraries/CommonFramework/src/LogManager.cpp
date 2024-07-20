#include "stdafx.h"

#include "LogManager.h"
#include "LogManagerPrivate.h"

LogManager::LogManager() :
  Singleton<LogManager>(),
  private_ptr(new LogManagerPrivate())
{
}

LogManager::~LogManager()
{
  if(private_ptr)
  {
    delete private_ptr;
    private_ptr = nullptr;
  }
}

bool LogManager::initializeWithConfig(const std::string& config_file_path)
{
  bool result = false;

  if(private_ptr)
  {
    result = private_ptr->initializeWithConfig(config_file_path);
  }

  return result;
}

void LogManager::trace(const std::string& log_content)
{
  if(private_ptr)
  {
    private_ptr->trace(log_content);
  }
}

void LogManager::debug(const std::string& log_content)
{
  if(private_ptr)
  {
    private_ptr->debug(log_content);
  }
}

void LogManager::info(const std::string& log_content)
{
  if(private_ptr)
  {
    private_ptr->info(log_content);
  }
}

void LogManager::warn(const std::string& log_content)
{
  if(private_ptr)
  {
    private_ptr->warn(log_content);
  }
}

void LogManager::error(const std::string& log_content)
{
  if(private_ptr)
  {
    private_ptr->error(log_content);
  }
}

void LogManager::critical(const std::string& log_content)
{
  if(private_ptr)
  {
    private_ptr->critical(log_content);
  }
}
