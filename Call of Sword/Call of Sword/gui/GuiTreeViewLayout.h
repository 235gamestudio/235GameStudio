#pragma once

#include "GuiTreeViewNode.h"

class GuiTreeViewLayout : public GuiTreeViewNode
{
	GuiLayout *layout;

public:
	GuiTreeViewLayout(GuiLayout *layout);
	GuiTreeViewLayout(glm::vec2 p = glm::vec2(0.0f));
	GuiTreeViewLayout(GuiTreeViewLayout &c);
	~GuiTreeViewLayout();

	virtual GuiTreeViewNode *addNode(GuiLayout *layout);
	
	virtual void setLayout(GuiLayout *layout);
	virtual GuiLayout *getLayout();

	virtual GuiTreeViewLayout *findByLayout(GuiLayout *layout);

	virtual void onInput();
};