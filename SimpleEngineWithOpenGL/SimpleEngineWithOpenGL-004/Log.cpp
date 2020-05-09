#include "Log.h"
#include <SDL_log.h>
#include <SDL_error.h>

void Log::info(string message)
{
	SDL_Log("INFO %s", message);
}

void Log::error(string message)
{
	SDL_Log("ERROR %s: %s", message, SDL_GetError());
}