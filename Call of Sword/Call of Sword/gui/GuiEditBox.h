#pragma once

#include "GuiText.h"

class GuiEditBox : public GuiLayout
{
	GuiTexture *texture;
	GuiText *text;
	bool typing;

	static GuiTexture *defaultTexture;
	static GuiText *defaultText;

public:
	GuiEditBox(glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(0.0f));
	GuiEditBox(const GuiEditBox &c);

	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();

	virtual void setTexture(GuiTexture *t);
	virtual GuiTexture *getTexture();
	virtual void setText(GuiText *t);
	virtual GuiText *getText();
	virtual bool isTyping();

	virtual void load(FILE *file);
	virtual void save(FILE *file);

	static void setDefaultTexture(GuiTexture *t);
	static GuiTexture *getDefaultTexture();
	static void setDefaultText(GuiText *t);
	static GuiText *getDefaultText();
};


class GuiEditBoxFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};