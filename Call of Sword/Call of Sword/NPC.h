#pragma once
#include <SDL.h>
#include <SDL_image.h>
#pragma comment(lib, "SDL2_image")
#pragma comment(lib, "SDL2")
#include <string>
#include <cmath>

class NPC
{
protected:
	float posX;
	float posY;

	SDL_Texture *texture = NULL;
	int sizeW;
	int sizeH;

public:
	SDL_Rect render;
	SDL_Rect playerRect;
	SDL_Rect walkingAnim;

	NPC(std::string pathAnim, float _posX, float _posY, int _sizeW, int _sizeH, SDL_Renderer *_renderer);
	~NPC();

	SDL_Texture* getTexture();

	float getPosX();
	float getPosY();
	void setPosX(float x);
	void setPosY(float y);

	int getSizeW();
	int getSizeH();

};