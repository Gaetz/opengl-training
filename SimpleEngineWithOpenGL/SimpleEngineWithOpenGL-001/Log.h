#pragma once
#include <Sdl.h>
#include <string>
using std::string;

class Log {
public:
	static void info(string message);
	static void error(string message);
};

void Log::info(string message)
{
	SDL_Log("INFO %s", message);
}

void Log::error(string message)
{
	SDL_Log("ERROR %s: %s", message, SDL_GetError());
}