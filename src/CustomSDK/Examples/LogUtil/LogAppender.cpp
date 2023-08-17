#include "LogAppender.h"
#include "LogEvent.h"
#include <LogFormatter.h>

#include <iostream>

LogAppender::LogAppender(LogLevel::Level level) :
	log_level(level),
	log_formatter(DEFAULT_LOG_FORMATTER)
{
}

void LogAppender::log(LogLevel::Level level, const char * content)
{
	if (level>=log_level)
	{
		
		if (log_formatter)
		{
			std::stringstream ss(log_formatter->format(level,content));
			append(ss);
		}
		else
		{
			std::stringstream ss(content);
			append(ss);
		}
		
	}
}

void LogAppender::setFormatter(std::shared_ptr<LogFormatter> formatter)
{
	log_formatter = formatter;
}

ConsoleAppender::ConsoleAppender(LogLevel::Level level):
	LogAppender(level)
{
}

void ConsoleAppender::append(std::stringstream & ss)
{
	std::cout << ss.rdbuf();
}

FileAppender::FileAppender(const char* path,LogLevel::Level level):
	file_path(path),
	LogAppender(level)
{
}

void FileAppender::append(std::stringstream & ss)
{
	std::ofstream out(file_path,std::ios::app|std::ios::binary);
	if (out.is_open())
	{
		out << ss.rdbuf();
		out.close();
	}
}
