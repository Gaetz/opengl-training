#pragma once
#include <string>
using std::string;

class Log {
public:
	static void info(string message);
	static void error(string message);
};

