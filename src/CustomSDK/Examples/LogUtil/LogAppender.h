#pragma once

#include "LogLevel.h"

#include <memory>
#include <fstream>

class LogFormatter;
class LogEvent;

class LogAppender
{
public: 
	LogAppender(LogLevel::Level level= LogLevel::Level::OFF);
public:
	 void log(LogLevel::Level,const char*);
protected:
	void setFormatter(std::shared_ptr<LogFormatter> formatter=nullptr);
protected:
	virtual void append(std::stringstream&)=0;
private:
	LogLevel::Level log_level;
	std::shared_ptr<LogFormatter> log_formatter;
};

class ConsoleAppender : public LogAppender
{
public:
	ConsoleAppender(LogLevel::Level level = LogLevel::Level::OFF);
protected:
	void append(std::stringstream&);
};

class FileAppender : public LogAppender
{
public:
	FileAppender(const char*,LogLevel::Level level = LogLevel::Level::OFF);
private:
	void append(std::stringstream&);
private:
	std::string file_path;
};