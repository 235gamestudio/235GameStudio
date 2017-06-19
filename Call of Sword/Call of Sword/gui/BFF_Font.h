#pragma once

#include <string>
#include <glm.hpp>
#include <SDL.h>

class BFF_Font
{
	SDL_Texture *texture;
	glm::ivec2 cellSize;
	unsigned char characterOffset;
	unsigned char widths[256];

public:
	BFF_Font();
	~BFF_Font();
	void setTexture(SDL_Texture *t);
	SDL_Texture *getTexture();
	void setCellSize(glm::ivec2 cs);
	glm::ivec2 getCellSize();
	void setCharacterOffset(unsigned char c);
	unsigned char getCharacterOffset();
	unsigned char *getCharacterWidths();
	void setCharacterWidth(int i, unsigned char w);
	unsigned char getCharacterWidth(int i);
};

