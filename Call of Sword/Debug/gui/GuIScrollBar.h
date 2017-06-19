#pragma once

#include "GuiLayout.h"
#include "GuiButton.h"

class GuiScrollBar : public GuiLayout
{
	GuiButton *buttonUp, *buttonDown, *buttonBar;
	GuiTexture *texture;

	static GuiButton *defaultButtonUp;
	static GuiButton *defaultButtonDown;
	static GuiButton *defaultButtonBar;
	static GuiTexture *defaultTexture;

public:
	GuiScrollBar(glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(0.0f));
	~GuiScrollBar();

	virtual void setButtonUp(GuiButton *b);
	virtual void setButtonDown(GuiButton *b);
	virtual void setButtonBar(GuiButton *b);
	virtual void setTexture(GuiTexture *t);
	virtual GuiButton *getButtonUp();
	virtual GuiButton *getButtonDown();
	virtual GuiButton *getButtonBar();
	virtual GuiTexture *getTexture();

	virtual void setSize(glm::vec2 s);

	virtual void onDraw();

	static void setDefaultButtonUp(GuiButton *b);
	static void setDefaultButtonDown(GuiButton *b);
	static void setDefaultButtonBar(GuiButton *b);
	static void setDefaultTexture(GuiTexture *t);
	static GuiButton *getDefaultButtonUp();
	static GuiButton *getDefaultButtonDown();
	static GuiButton *getDefaultButtonBar();
	static GuiTexture *getDefaultTexture();
};