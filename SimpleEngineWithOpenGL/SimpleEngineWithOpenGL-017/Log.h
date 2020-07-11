#pragma once
#include <string>
using std::string;

class Log {
public:
	Log() = delete;
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

	static void info(const string& message);
	static void error(int category, const string& message);
};
