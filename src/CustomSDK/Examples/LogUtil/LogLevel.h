#pragma once

#include <string>

class LogLevel
{
public:
	enum Level
	{
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL,
		OFF
	};
public:
	static const char* toString(LogLevel::Level);
	static LogLevel::Level fromString(const std::string&);
protected:
private:
};