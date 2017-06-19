#pragma once
#include <string>
#pragma comment (lib, "SDL2")
#pragma comment (lib, "SDL2_image")
#include <SDL_image.h>
#include <SDL.h>

class GameWindow
{
private:
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;
	SDL_Surface *gWindowIcon = NULL;
	std::string gWindowName;
	bool isOpened = false;
	int width;
	int height;

public:
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	std::string getWindowName();
	int getWidth();
	int getHeight();
	bool opened();					// this function is checking if game is already opened

	GameWindow(std::string gWindowName, int WindowWidth, int WindowHeight);
	~GameWindow();

};