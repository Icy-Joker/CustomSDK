#include "LogFormatter.h"

LogFormatter::LogFormatter(const char * format_pattern):
	log_format_pattern(format_pattern)
{
}

std::stringstream LogFormatter::format(LogLevel::Level level, const char * content)
{
	std::stringstream ss;
	ss << "[LOG_" << LogLevel::toString(level) << "]:" << content<< std::endl;
	return std::move(ss);
}
