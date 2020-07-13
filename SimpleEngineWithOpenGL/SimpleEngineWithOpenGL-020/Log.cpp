#include "Log.h"
#include <SDL_log.h>
#include <SDL_error.h>

void Log::info(const string& message)
{
	SDL_Log(message.c_str());
}

void Log::error(int category, const string& message)
{
	SDL_LogError(category, "%s | SDL: %s", message.c_str(), SDL_GetError());
}