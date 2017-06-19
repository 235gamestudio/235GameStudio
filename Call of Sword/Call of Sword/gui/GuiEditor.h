#pragma once

#include "GuiLayout.h"

enum EGuiEditMode
{
	eGuiEditNone,
	eGuiEditSize,
	eGuiEditPosition,
	eGuiEditSelection
};

class GuiEditor
{
	EGuiEditMode edit;
	glm::vec2 mouseRel;

public:
	GuiEditor();
	virtual ~GuiEditor();

	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();

	virtual void onLayoutInput(GuiLayout *layout, int mode);
	virtual void onLayoutUpdate(GuiLayout *layout, int mode);
	virtual void onLayoutDraw(GuiLayout *layout, int mode);
};