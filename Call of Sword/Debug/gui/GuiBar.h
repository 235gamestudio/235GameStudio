#pragma once
#include <SDL.h>

#include "GuiButton.h"

class GuiBar : public GuiLayout
{
	GuiTexture *texture;
	
	GuiButton *buttonEQ;
	GuiButton *buttonMap;
	GuiButton *buttonQuests;
	GuiButton *buttonSpells;
	GuiButton *buttonStatus;
	GuiButton *buttonArrow;
	
	bool isExpanded;
	float dstPos;

	float expandedPosX;
	float hiddenPosX;

public:
	GuiBar(glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiBar(GuiTexture *texture, glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiBar(const GuiBar &c);

	void setTexture(GuiTexture *t);
	GuiTexture *getTexture();

	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();
};