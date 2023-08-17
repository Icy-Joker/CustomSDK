#include "LogLevel.h"

const char * LogLevel::toString(LogLevel::Level level)
{
	switch (level)
	{
		case LogLevel::TRACE:
			return "TRACE";
		case LogLevel::DEBUG:
			return "DEBUG";
		case LogLevel::INFO:
			return "INFO";
		case LogLevel::WARN:
			return "WARN";
		case LogLevel::ERROR:
			return "ERROR";
		case LogLevel::FATAL:
			return "FATAL";
		default:
		case LogLevel::OFF:
			return "OFF";
	}
}

LogLevel::Level LogLevel::fromString(const std::string & level)
{
	return LogLevel::Level();
}
