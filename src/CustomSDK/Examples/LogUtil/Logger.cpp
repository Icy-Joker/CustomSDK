#include "Logger.h"
#include "LogAppender.h"

void Logger::log(LogLevel::Level level, const char * content)
{
	for (auto it_vector_log_appender=std::begin(vector_log_appender);it_vector_log_appender!=std::end(vector_log_appender);++it_vector_log_appender)
	{
		if (std::shared_ptr<LogAppender> appender=*it_vector_log_appender)
		{
			appender->log(level, content);
		}
	}
}

void Logger::addAppender(std::shared_ptr<LogAppender> appender)
{
	if (appender)
	{
		vector_log_appender.push_back(appender);
	}
}
