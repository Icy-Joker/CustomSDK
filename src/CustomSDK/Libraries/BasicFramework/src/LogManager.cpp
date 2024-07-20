#include "stdafx.h"

#include "LogManager.h"

#include <ConfigManagerPrivate.h>

#include "ConfigManager.h"

#include <spdlog/spdlog.h>

struct LogManagerPrivate
{
  std::shared_ptr<spdlog::logger> logger;
};

LogManager::LogManager():
  _p(new LogManagerPrivate())
{
}

LogManager::~LogManager()
{
  if(_p)
  {
    delete _p;
    _p = nullptr;
  }
}

LogManager* LogManager::getInstance()
{
  static LogManager instance;
  return &instance;
}

void LogManager::initialize()
{
  // 获取配置文件中的日志器设置
  std::vector<spdlog::sink_ptr> loggers = ConfigManager::getInstance()->private_ptr->getLoggers();
  _p->logger = std::make_shared<spdlog::logger>("multi_sink",loggers.begin(),loggers.end());
  // 设置全局日志级别为 TRACE
  //_p->logger->set_level(spdlog::level::trace);
  spdlog::set_level(spdlog::level::trace);
  spdlog::set_default_logger(_p->logger);
}

void LogManager::trace(const char* log_content)
{
  // if(_p->logger)
  // {
  //   _p->logger->trace(log_content);
  // }
  spdlog::trace(log_content);
}

void LogManager::debug(const char* log_content)
{
  // if(_p->logger)
  // {
  //   _p->logger->debug(log_content);
  // }
  spdlog::debug(log_content);
}

void LogManager::info(const char* log_content)
{
  // if(_p->logger)
  // {
  //   _p->logger->info(log_content);
  // }
  spdlog::info(log_content);
}

void LogManager::warn(const char* log_content)
{
  // if(_p->logger)
  // {
  //   _p->logger->warn(log_content);
  // }
  spdlog::warn(log_content);
}

void LogManager::error(const char* log_content)
{
  // if(_p->logger)
  // {
  //   _p->logger->error(log_content);
  // }
  spdlog::error(log_content);
}

void LogManager::critical(const char* log_content)
{
  // if(_p->logger)
  // {
  //   _p->logger->critical(log_content);
  // }
  spdlog::critical(log_content);
}
