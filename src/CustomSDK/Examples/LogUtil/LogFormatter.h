#pragma once

#include "LogLevel.h"

#include <sstream>
#include <memory>

class LogFormatter;
static const std::shared_ptr<LogFormatter> DEFAULT_LOG_FORMATTER = std::make_shared<LogFormatter>("");

class LogFormatter
{
public:
	LogFormatter(const char* format_pattern);
public:
	std::stringstream format(LogLevel::Level, const char*);
private:
	std::string log_format_pattern;
};
