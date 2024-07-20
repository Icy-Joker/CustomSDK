#include "stdafx.h"

#include "LogManagerPrivate.h"

#include <pugixml.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <boost/filesystem.hpp>

bool LogManagerPrivate::initializeWithConfig(const char* config_path)
{
  bool result = false;

  {
    pugi::xml_document doc;
    boost::filesystem::path path = boost::filesystem::absolute(config_path).generic_path().make_preferred();
    if(boost::filesystem::is_regular_file(path) && path.extension().string() == ".xml")
    {
      if(doc.load_file(path.string().c_str()).status == pugi::xml_parse_status::status_ok)
      {
        std::vector<spdlog::sink_ptr> sinks;

        if(pugi::xml_node node_loggers = doc.select_node("Root/Loggers").node())
        {
          if(node_loggers.attribute("enabled").as_bool())
          {
            for(auto& xpath_node_logger : node_loggers.select_nodes("Logger"))
            {
              if(xpath_node_logger.node().attribute("enabled").as_bool())
              {
                const std::string type = xpath_node_logger.node().attribute("type").as_string();
                const std::string level = xpath_node_logger.node().attribute("level").as_string();
                const std::string format = xpath_node_logger.node().attribute("format").as_string();

                spdlog::sink_ptr sink = nullptr;
                if(type == "ConsoleLogger")
                {
                  sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic);
                }
                else if(type == "FileLogger")
                {
                  sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.log",true);
                }
                if(sink)
                {
                  sink->set_level(spdlog::level::from_str(level));
                  sink->set_pattern(format);

                  sinks.push_back(sink);
                }
              }
            }
          }
        }

        std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>("multi_sink",sinks.begin(),sinks.end());
        // 设置全局日志级别为 TRACE
        //_p->logger->set_level(spdlog::level::trace);
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_default_logger(logger);

        result = true;
      }
    }
  }

  return result;
}

void LogManagerPrivate::trace(const char* log_content)
{
  // if(this->logger)
  // {
  //   this->logger->trace(log_content);
  // }
  spdlog::trace(log_content);
}

void LogManagerPrivate::debug(const char* log_content)
{
  // if(this->logger)
  // {
  //   this->logger->debug(log_content);
  // }
  spdlog::trace(log_content);
}

void LogManagerPrivate::info(const char* log_content)
{
  // if(this->logger)
  // {
  //   this->logger->info(log_content);
  // }
  spdlog::info(log_content);
}

void LogManagerPrivate::warn(const char* log_content)
{
  // if(this->logger)
  // {
  //   this->logger->warn(log_content);
  // }
  spdlog::warn(log_content);
}

void LogManagerPrivate::error(const char* log_content)
{
  // if(this->logger)
  // {
  //   this->logger->error(log_content);
  // }
  spdlog::error(log_content);
}

void LogManagerPrivate::critical(const char* log_content)
{
  // if(this->logger)
  // {
  //   this->logger->critical(log_content);
  // }
  spdlog::critical(log_content);
}
