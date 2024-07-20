#include "stdafx.h"

#include "LogManagerPrivate.h"

#include <pugixml.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <boost/filesystem.hpp>

#include <BasicSupport/MicroUtils.h>

LogManagerPrivate::LogManagerPrivate()
{
  spdlog::set_pattern("[%^---%L---%$] [%H:%M:%S %z] [thread %t] %v");
  spdlog::set_level(spdlog::level::trace);
  spdlog::flush_every(std::chrono::seconds(1));
}

LogManagerPrivate::~LogManagerPrivate()
{
  spdlog::shutdown();
}

bool LogManagerPrivate::initializeWithConfig(const std::string& config_path)
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
          if(node_loggers.attribute("enabled").as_bool(false))
          {
            for(auto& xpath_node_logger : node_loggers.select_nodes("Logger"))
            {
              if(xpath_node_logger.node().attribute("enabled").as_bool(false))
              {
                const std::string type = xpath_node_logger.node().attribute("type").as_string();
                const std::string level = xpath_node_logger.node().attribute("level").as_string("info");
                const std::string format = xpath_node_logger.node().attribute("format").as_string("[%^---%L---%$] [%H:%M:%S %z] [thread %t] %v");

                spdlog::sink_ptr sink = nullptr;
                if(type == "ConsoleLogger")
                {
                  sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::automatic);
                }
                else if(type == "FileLogger")
                {
                  const std::string log_file_name = xpath_node_logger.node().attribute("file_name").as_string(fmt::format("{}.log",MicroUtils::getCurrentProcessName()).c_str());
                  const std::string log_file_path = fmt::format(fmt::format("logs/{}",log_file_name));
                  sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file_path,true);
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
        logger->set_level(spdlog::level::trace);
        //logger->flush_on(spdlog::level::trace);

        spdlog::set_default_logger(logger);
        spdlog::flush_every(std::chrono::seconds(1));

        result = true;
      }
    }
  }

  return result;
}

void LogManagerPrivate::trace(const std::string& log_content)
{
  spdlog::trace(log_content);
}

void LogManagerPrivate::debug(const std::string& log_content)
{
  spdlog::debug(log_content);
}

void LogManagerPrivate::info(const std::string& log_content)
{
  spdlog::info(log_content);
}

void LogManagerPrivate::warn(const std::string& log_content)
{
  spdlog::warn(log_content);
}

void LogManagerPrivate::error(const std::string& log_content)
{
  spdlog::error(log_content);
}

void LogManagerPrivate::critical(const std::string& log_content)
{
  spdlog::critical(log_content);
}
