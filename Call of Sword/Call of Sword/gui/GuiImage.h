#pragma once

#include <SDL.h>

#include "GuiText.h"

class GuiImage : public GuiLayout
{
	GuiTexture *texture;

	GuiText *text;

public:
	GuiImage(glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiImage(GuiTexture *texture, glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiImage(const GuiImage &c);

	void setTexture(GuiTexture *t);
	GuiTexture *getTexture();
	void setText(GuiText *t);
	GuiText *getText();

	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();
};
