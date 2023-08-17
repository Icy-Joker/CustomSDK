#pragma once

#include "LogLevel.h"

#include <vector>
#include <memory>

class Logger;

class LogManager
{
public:
	void initialize();
	void finalize();
public:
	void log_warn(const char*);
	void log_debug(const char*);
	void log_trace(const char*);
private:
	void log(LogLevel::Level, const char*);
protected:
private:
	std::vector<std::shared_ptr<Logger>> vector_loggers;
};