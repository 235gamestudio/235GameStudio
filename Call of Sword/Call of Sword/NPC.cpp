#include "NPC.h"

NPC::NPC(std::string path, float _posX, float _posY, int _sizeW, int _sizeH, SDL_Renderer *_renderer)
{
	SDL_Surface *tmpSurface = IMG_Load(path.c_str());

	if (tmpSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}

	else
	{
		texture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
		posX = _posX;
		posY = _posY;
		sizeW = _sizeW;
		sizeH = _sizeH;

		walkingAnim.x = 0;
		walkingAnim.y = 0;
		walkingAnim.w = sizeW;
		walkingAnim.h = sizeH;

		render.x = (int)_posX - (_sizeW / 2);
		render.y = (int)_posY - (_sizeH / 2);
		render.w = _sizeW;
		render.h = _sizeH;

		playerRect.x = posX;
		playerRect.y = posY;
		playerRect.w = sizeW;
		playerRect.h = sizeH;

		SDL_FreeSurface(tmpSurface);
	}

}

NPC::~NPC()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* NPC::getTexture()
{
	return texture;
}

float NPC::getPosX()
{
	return posX;
}

float NPC::getPosY()
{
	return posY;
}

void NPC::setPosX(float x)
{
	posX = x;
}

void NPC::setPosY(float y)
{
	posY = y;
}


int NPC::getSizeH()
{
	return sizeH;
}

int NPC::getSizeW()
{
	return sizeW;
}