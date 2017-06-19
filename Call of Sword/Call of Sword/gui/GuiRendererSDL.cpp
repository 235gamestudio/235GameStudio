#include "GuiRendererSDL.h"

GuiRendererSDL::GuiRendererSDL(SDL_Window *window, SDL_Renderer *renderer)
{
	this->window = window;
	this->renderer = renderer;
}

void GuiRendererSDL::setViewport(glm::vec2 p, glm::vec2 s)
{
	SDL_Rect viewportRect;
	viewportRect.x = (int)p.x;
	viewportRect.y = (int)p.y;
	if (s.x < 0.0f)
		SDL_GetWindowSize(window, &viewportRect.w, 0);
	else
		viewportRect.w = (int)s.x;
	if (s.y < 0.0f)
		SDL_GetWindowSize(window, 0, &viewportRect.h);
	else
		viewportRect.h = (int)s.y;
	SDL_RenderSetViewport(renderer, &viewportRect);
}
void GuiRendererSDL::setRenderTarget(GuiTexture *texture)
{
	SDL_SetRenderTarget(renderer, (SDL_Texture*)texture);
}

GuiTexture *GuiRendererSDL::createTexture(glm::vec2 size)
{
	SDL_Texture *t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int)size.x, (int)size.y);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	return t;
}
void GuiRendererSDL::destroyTexture(GuiTexture *texture)
{
	SDL_DestroyTexture((SDL_Texture*)texture);
}
GuiTexture *GuiRendererSDL::loadTexture(std::string path)
{
	SDL_Surface *tSurface;
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(path.c_str());
	FIBITMAP *bitmap = FreeImage_Load(fif, path.c_str(), 0);
	if (bitmap)
	{
		FreeImage_FlipVertical(bitmap);
		int width = FreeImage_GetWidth(bitmap);
		int height = FreeImage_GetHeight(bitmap);
		int bpp = FreeImage_GetBPP(bitmap);
		int channels = bpp / 8;
		unsigned char *data = FreeImage_GetBits(bitmap);

		tSurface = SDL_CreateRGBSurfaceFrom((void*)data, width, height, bpp, width * channels, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		SDL_SetSurfaceBlendMode(tSurface, SDL_BLENDMODE_BLEND);
	}
	else
	{
		printf("Can't open file: '%s'\n", path.c_str());
		return 0;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tSurface);
	SDL_FreeSurface(tSurface);
	return texture;
}
glm::vec2 GuiRendererSDL::getTextureSize(GuiTexture *t)
{
	SDL_Texture *texture = (SDL_Texture*)t;
	int w, h;
	SDL_QueryTexture(texture, 0, 0, &w, &h);
	return glm::vec2(w, h);
}

GuiFont *GuiRendererSDL::loadFont(std::string path)
{
	BFF_Font *f = new BFF_Font();
	SDL_DestroyTexture(f->getTexture());

	unsigned char version[2] = { 0 };
	int imageSize[2] { 0 };
	char bpp = 0, channels = 0;
	unsigned char *data = 0, *RGBAdata = 0;
	glm::ivec2 cellSize;
	unsigned char characterOffset;

	FILE *file;
	fopen_s(&file, path.c_str(), "rb");
	if (!file) {
		printf("Can't open file: '%s'\n", path.c_str());
		return 0;
	}
	fread_s(version, 2, 1, 2, file);
	if (version[0] != 0xBF || version[1] != 0xF2) {
		printf("Wrong font file format !\n");
		return 0;
	}

	fread_s(imageSize, 8, 4, 2, file);

	fread_s(&cellSize[0], 8, 4, 2, file);
	f->setCellSize(cellSize);

	fread_s(&bpp, 1, 1, 1, file);
	channels = bpp / 8;

	fread_s(&characterOffset, 1, 1, 1, file);
	f->setCharacterOffset(characterOffset);

	fread_s(f->getCharacterWidths(), 256, 1, 256, file);

	unsigned int dataSize = imageSize[0] * imageSize[1] * channels;
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = imageSize[0];
	rect.h = imageSize[1];
	data = new unsigned char[dataSize];
	RGBAdata = new unsigned char[imageSize[0] * imageSize[1] * 4];
	fread_s(data, dataSize, 1, dataSize, file);
	for (int i = 0; i < imageSize[0] * imageSize[1]; i++)
	{
		RGBAdata[i * 4 + 3] = data[i * channels];
		RGBAdata[i * 4 + 1] = data[i * channels];
		RGBAdata[i * 4 + 2] = data[i * channels];
		RGBAdata[i * 4 + 0] = data[i * channels];
	}
	f->setTexture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, imageSize[0], imageSize[1]));
	SDL_SetTextureBlendMode(f->getTexture(), SDL_BLENDMODE_BLEND);
	SDL_UpdateTexture(f->getTexture(), &rect, RGBAdata, imageSize[0] * 4);
	delete data;
	delete RGBAdata;
	return f;
}

void GuiRendererSDL::drawRect(glm::vec2 p, glm::vec2 s, int r, int g, int b)
{
	SDL_Rect rect;
	rect.x = (int)p.x;
	rect.y = (int)p.y;
	rect.w = (int)s.x;
	rect.h = (int)s.y;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawRect(renderer, &rect);
}
void GuiRendererSDL::drawFillRect(glm::vec2 p, glm::vec2 s, int r, int g, int b)
{
	SDL_Rect rect;
	rect.x = (int)p.x;
	rect.y = (int)p.y;
	rect.w = (int)s.x;
	rect.h = (int)s.y;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void GuiRendererSDL::clear(glm::ivec4 color)
{
	color = glm::ivec4(0x00, 0x00, 0x00, 0xff);
	SDL_SetRenderDrawColor(renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a);
	SDL_RenderClear(renderer);
}
void GuiRendererSDL::render(GuiTexture *t, glm::vec2 p, glm::vec2 s, glm::vec4 c)
{
	SDL_Texture *texture = (SDL_Texture*)t;
	int texWidth, texHeight;
	SDL_QueryTexture(texture, 0, 0, &texWidth, &texHeight);
	SDL_Rect pos;

	pos.x = (int)p.x;
	pos.y = (int)p.y;
	if (s.x > 0)	pos.w = (int)s.x;
	else			pos.w = texWidth;
	if (s.y > 0)	pos.h = (int)s.y;
	else			pos.h = texHeight;

	SDL_SetTextureColorMod(texture, (Uint8)c.r, (Uint8)c.g, (Uint8)c.b);
	SDL_RenderCopy(renderer, texture, 0, &pos);
}
void GuiRendererSDL::render(GuiTexture *t, glm::vec2 uv0, glm::vec2 uv1, glm::vec2 p, glm::vec2 s, glm::vec4 c)
{
	SDL_Texture *texture = (SDL_Texture*)t;
	int texWidth, texHeight;
	SDL_QueryTexture(texture, 0, 0, &texWidth, &texHeight);
	SDL_Rect uv;
	SDL_Rect pos;

	uv.x = (int)uv0.x;
	uv.y = (int)uv0.y;
	if (uv1.x > 0)	uv.w = (int)uv1.x;
	else			uv.w = texWidth;
	if (uv1.y > 0)	uv.h = (int)uv1.y;
	else			uv.h = texHeight;

	pos.x = (int)p.x;
	pos.y = (int)p.y;
	if (s.x > 0)	pos.w = (int)s.x;
	else			pos.w = texWidth;
	if (s.y > 0)	pos.h = (int)s.y;
	else			pos.h = texHeight;

	SDL_SetTextureColorMod(texture, (Uint8)c.r, (Uint8)c.g, (Uint8)c.b);
	SDL_RenderCopy(renderer, texture, &uv, &pos);
}
void GuiRendererSDL::print(GuiFont *f, glm::vec2 p, std::string text, glm::vec4 c)
{
	BFF_Font *font = (BFF_Font*)f;
	glm::vec2 posOffset = glm::vec2(0.0f);
	int w, h;
	SDL_QueryTexture(font->getTexture(), 0, 0, &w, &h);
	glm::vec2 size(w, h);
	for (unsigned int i = 0; i < text.size(); i++)
	{
		glm::ivec2 asciiPos = glm::ivec2(
			text.at(i) % (int)(size.x / font->getCellSize().x),
			text.at(i) / (int)(size.y / font->getCellSize().y)
			);
		render(
			font->getTexture(),
			font->getCellSize() * asciiPos,
			font->getCellSize(),
			p + posOffset,
			font->getCellSize(),
			c);
		posOffset += glm::vec2(font->getCharacterWidth(text.at(i)), 0.0f);
	}
}