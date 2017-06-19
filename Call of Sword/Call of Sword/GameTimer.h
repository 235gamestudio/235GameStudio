#pragma once
#include <SDL.h>
#pragma comment(lib, "SDL2")

class GameTimer
{
private:
	Uint32 startTick;
	Uint32 pausedTick;

	bool paused = false;
	bool started = false;

public:
	GameTimer();

	void start();
	void stop();
	void pause();
	void resume();

	Uint32 getTicks();				

	bool isStarted();
	bool isPaused();

};