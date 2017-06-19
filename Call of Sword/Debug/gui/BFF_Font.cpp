#include "BFF_Font.h"

BFF_Font::BFF_Font() :
texture(0),
cellSize(glm::ivec2(0)),
characterOffset(0)
{
	memset(widths, 0, sizeof(widths));
}
BFF_Font::~BFF_Font()
{
	SDL_DestroyTexture(texture);
}
void BFF_Font::setTexture(SDL_Texture *t)
{
	texture = t;
}
SDL_Texture *BFF_Font::getTexture()
{
	return texture;
}
void BFF_Font::setCellSize(glm::ivec2 cs)
{
	cellSize = cs;
}
glm::ivec2 BFF_Font::getCellSize()
{
	return cellSize;
}
void BFF_Font::setCharacterOffset(unsigned char c)
{
	characterOffset = c;
}
unsigned char BFF_Font::getCharacterOffset()
{
	return characterOffset;
}
unsigned char *BFF_Font::getCharacterWidths()
{
	return widths;
}
void BFF_Font::setCharacterWidth(int i, unsigned char w)
{
	widths[i] = w;
}
unsigned char BFF_Font::getCharacterWidth(int i)
{
	return widths[i];
}