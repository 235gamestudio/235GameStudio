#pragma once

#include <SDL.h>

#include "GuiText.h"

class GuiButton : public GuiLayout
{
	GuiTexture *texture;
	bool pressed, clicked;

	GuiText *text;

	static GuiTexture *defaultTexture;
	static GuiText *defaultText;

public:
	GuiButton(std::string text = defaultText->getText(), glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiButton(GuiTexture *texture, std::string text = defaultText->getText(), glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiButton(const GuiButton &c);

	bool isPressed();
	bool isClicked();

	void setTexture(GuiTexture *t);
	GuiTexture *getTexture();
	void setText(GuiText *t);
	GuiText *getText();

	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();

	virtual void load(FILE *file);
	virtual void save(FILE *file);

	static void setDefaultTexture(GuiTexture *texture);
	static GuiTexture *getDefaultTexture();
	static void setDefaultText(GuiText *text);
	static GuiText *getDefaultText();
};

class GuiButtonFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};