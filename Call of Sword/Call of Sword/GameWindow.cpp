#include "GameWindow.h"


GameWindow::GameWindow(std::string gWindowName, int WindowWidth, int WindowHeight)
{
		bool initSuccess = true;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			initSuccess = false;
			throw std::string("SDL could not initialize!");
		}
		else
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				printf("Warning: Linear texture filtering not enabled!");


			gWindow = SDL_CreateWindow(gWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			width = WindowWidth;
			height = WindowHeight;

			if (gWindow == NULL)
			{
				initSuccess = false;
				throw std::string("Window could not be created!");
			}

			else
			{
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

				if (gRenderer == NULL)
				{
					initSuccess = false;
					throw std::string("Renderer could not be created!");
				}

				else
				{
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						initSuccess = false;
						throw std::string("SDL_image could not initialize! Check SDL_Image Error!");
					}
				}
			}
		}

		SDL_RWops *rwop = NULL;
		rwop = SDL_RWFromFile("images/other/pngGameIcon.png", "br");
		if (rwop == NULL)
		{
			initSuccess = false;
			throw std::string("RWop could not load game icon!");
		}
		else
		{
			gWindowIcon = IMG_LoadPNG_RW(rwop);

			if (gWindowIcon == NULL)
			{
				initSuccess = false;
				throw std::string("Icon could not be loaded!");
			}
			else
			{
				SDL_SetWindowIcon(gWindow, gWindowIcon);
				SDL_RWclose(rwop);
			}

		}
		if (initSuccess == true)
			isOpened = true;
}

GameWindow::~GameWindow()
{
	SDL_FreeSurface(gWindowIcon);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
}

SDL_Window* GameWindow::getWindow()
{
	return gWindow;
}

SDL_Renderer* GameWindow::getRenderer()
{
	return gRenderer;
}

std::string GameWindow::getWindowName()
{
	return gWindowName;
}

bool GameWindow::opened()
{
	return isOpened;
}

int GameWindow::getWidth()
{
	return width;
}

int GameWindow::getHeight()
{
	return height;
}