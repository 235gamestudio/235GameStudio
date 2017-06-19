#pragma once

#include <glm.hpp>
#include <string>

typedef void GuiTexture;
typedef void GuiFont;

class GuiRenderer
{
public:
	virtual void setViewport(glm::vec2 p, glm::vec2 s) = 0;
	virtual void setRenderTarget(GuiTexture *texture) = 0;

	/* Textures */
	virtual GuiTexture *createTexture(glm::vec2 size) = 0;
	virtual void destroyTexture(GuiTexture *texture) = 0;
	virtual GuiTexture *loadTexture(std::string path) = 0;
	virtual glm::vec2 getTextureSize(GuiTexture *texture) = 0;

	/* Fonts */
	virtual GuiFont *loadFont(std::string path) = 0;

	/* Drawing */
	virtual void drawRect(glm::vec2 p, glm::vec2 s, int r, int g, int b) = 0;
	virtual void drawFillRect(glm::vec2 p, glm::vec2 s, int r, int g, int b) = 0;


	/* Rendering */
	virtual void clear(glm::ivec4 color) = 0;
	virtual void render(GuiTexture *texture, glm::vec2 p, glm::vec2 s, glm::vec4 c = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f)) = 0;
	virtual void render(GuiTexture *texture, glm::vec2 uv0, glm::vec2 uv1, glm::vec2 p, glm::vec2 s, glm::vec4 c = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f)) = 0;
	virtual void print(GuiFont *font, glm::vec2 p, std::string text, glm::vec4 c = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f)) = 0;
};