#pragma once

#include <sstream>

class LogEvent
{
private:
	const char* filename;
	unsigned int time_elapsed;
	unsigned long long time_stamp;
	std::stringstream log_content;
};