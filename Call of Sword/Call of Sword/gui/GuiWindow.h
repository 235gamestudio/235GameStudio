#pragma once

#include <string>

#include "GuiButton.h"
#include "GuiText.h"

class GuiButton;
class GuiText;

class GuiWindow : public GuiLayout
{
	GuiTexture *texture;
	GuiButton *buttonX;
	GuiText *title;

	glm::vec2 mouseOffset;

	static GuiTexture *defaultTexture;
	static GuiButton *defaultButtonX;
	static GuiText *defaultTitleText;

public:
	GuiWindow(glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiWindow(std::string t, glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiWindow(const GuiWindow &c);
	~GuiWindow();
	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();

	void setButtonX(GuiButton *button);
	GuiButton *getButtonX();
	void setTitle(GuiText *text);
	GuiText *getTitle();

	virtual void load(FILE *file);
	virtual void save(FILE *file);

	static void setDefaultTexture(GuiTexture *t);
	static GuiTexture *getDefaultTexture();
	static void setDefaultButtonX(GuiButton *b);
	static GuiButton *getDefaultButtonX();
	static void setDefaultTitleText(GuiText *t);
	static GuiText *getDefaultTitleText();
};

class GuiWindowFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};