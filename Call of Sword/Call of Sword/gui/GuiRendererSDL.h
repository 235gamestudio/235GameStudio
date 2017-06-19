#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <FreeImage.h>
#include "BFF_Font.h"

#include "GuiRenderer.h"

class GuiRendererSDL : public GuiRenderer
{
	SDL_Window *window;
	SDL_Renderer *renderer;

public:
	GuiRendererSDL(SDL_Window *window, SDL_Renderer *renderer);

	void setViewport(glm::vec2 p, glm::vec2 s);
	void setRenderTarget(GuiTexture *texture);

	GuiTexture *createTexture(glm::vec2 size);
	void destroyTexture(GuiTexture *texture);
	GuiTexture *loadTexture(std::string path);
	glm::vec2 getTextureSize(GuiTexture *texture);

	GuiFont *loadFont(std::string path);

	void drawRect(glm::vec2 p, glm::vec2 s, int r, int g, int b);
	void drawFillRect(glm::vec2 p, glm::vec2 s, int r, int g, int b);

	void clear(glm::ivec4 color);
	void setColorMod(glm::vec4 c);
	void render(GuiTexture *texture, glm::vec2 p, glm::vec2 s, glm::vec4 c = glm::vec4(255.0f, 255.0f, 255.0f, 0.0f));
	void render(GuiTexture *texture, glm::vec2 uv0, glm::vec2 uv1, glm::vec2 p, glm::vec2 s, glm::vec4 c = glm::vec4(255.0f, 255.0f, 255.0f, 0.0f));
	void print(GuiFont *font, glm::vec2 p, std::string text, glm::vec4 c = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f));
};