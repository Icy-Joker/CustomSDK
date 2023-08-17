#include "LogManager.h"
#include "Logger.h"
#include "LogAppender.h"

#include <mutex>

void LogManager::initialize()
{
	std::shared_ptr<Logger> logger_0=std::make_shared<Logger>();
	vector_loggers.push_back(logger_0);

	std::shared_ptr<ConsoleAppender> console_appender = std::make_shared<ConsoleAppender>(LogLevel::Level::WARN);
	logger_0->addAppender(console_appender);

	std::shared_ptr<FileAppender> file_appender = std::make_shared<FileAppender>("C:/Users/huaru/Desktop/log.txt", LogLevel::Level::DEBUG);
	logger_0->addAppender(file_appender);
}

void LogManager::finalize()
{
}

void LogManager::log_warn(const char * content)
{
	log(LogLevel::Level::WARN, content);
}

void LogManager::log_debug(const char * content)
{
	log(LogLevel::Level::DEBUG, content);
}

void LogManager::log_trace(const char * content)
{
	log(LogLevel::Level::TRACE, content);
}

void LogManager::log(LogLevel::Level level, const char * content)
{
	static std::mutex mutex;
	mutex.lock();
	for (auto it_vector_loggers=std::begin(vector_loggers);it_vector_loggers!=std::end(vector_loggers);++it_vector_loggers)
	{
		if (std::shared_ptr<Logger> logger = *it_vector_loggers)
		{
			logger->log(level, content);
		}
	}
	mutex.unlock();
}
