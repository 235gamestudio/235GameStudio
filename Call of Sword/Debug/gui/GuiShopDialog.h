#pragma once

#include "GuiWindow.h"

class GuiShopDialog : public GuiWindow
{
	GuiTexture *slotTexture;
	GuiButton *buttonBuy;

	static GuiTexture *defaultSlotTexture;

public:
	GuiShopDialog(glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiShopDialog(std::string t, glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	~GuiShopDialog();

	virtual void onDraw();

	static void setDefaultSlotTexture(GuiTexture *t);
	static GuiTexture *getDefaultSlotTexture();
};

class GuiShopDialogFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};