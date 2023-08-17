#pragma once

#include <LogLevel.h>

#include <vector>
#include <memory>

class LogAppender;

class Logger
{
public:
	void log(LogLevel::Level, const char*);
public:
	void addAppender(std::shared_ptr<LogAppender>);
protected:
private:
	std::string logger_name;
	std::vector<std::shared_ptr<LogAppender>> vector_log_appender;
};