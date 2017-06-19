#include "GameTimer.h"

GameTimer::GameTimer()
{
	startTick = 0;
	pausedTick = 0;

	paused = false;
	started = false;
}

bool GameTimer::isPaused()
{
	return paused && started;
}

bool GameTimer::isStarted()
{
	return started;
}

void GameTimer::start()
{
	started = true;
	paused = false;

	startTick = SDL_GetTicks();
	pausedTick = 0;
}

void GameTimer::pause()
{
	if (started && !paused)
	{
		paused = true;
		pausedTick = SDL_GetTicks() - startTick;
		startTick = 0;
	}
}

void GameTimer::resume()
{
	if (started && paused)
	{
		paused = false;

		startTick = SDL_GetTicks() - pausedTick;
		pausedTick = 0;
	}
}

void GameTimer::stop()
{
	started = false;

	paused = false;

	startTick = 0;
	pausedTick = 0;
}

Uint32 GameTimer::getTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTick;
		}
		else
		{
			time = SDL_GetTicks() - startTick;
		}
	}

	return time;
}