#include "GuiTreeViewLayout.h"

#include "GuiManager.h"

GuiTreeViewLayout::GuiTreeViewLayout(GuiLayout *layout)
: GuiTreeViewNode(glm::vec2(0.0f))
{
	this->layout = layout;
	getText()->setText(layout->getLabel());
	setLabel("gui_treeviewlayout");
}
GuiTreeViewLayout::GuiTreeViewLayout(glm::vec2 p)
: GuiTreeViewNode(p)
, layout(0)
{

}
GuiTreeViewLayout::GuiTreeViewLayout(GuiTreeViewLayout &c)
: GuiTreeViewNode(c)
, layout(c.layout)
{

}
GuiTreeViewLayout::~GuiTreeViewLayout()
{

}

GuiTreeViewNode *GuiTreeViewLayout::addNode(GuiLayout *layout)
{
	GuiTreeViewLayout *node = new GuiTreeViewLayout(layout);
	if (layout)
		node->getText()->setText(layout->getLabel());
	return GuiTreeViewNode::addNode(node);
}

void GuiTreeViewLayout::setLayout(GuiLayout *layout)
{
	this->layout = layout;
}
GuiLayout *GuiTreeViewLayout::getLayout()
{
	return layout;
}

GuiTreeViewLayout *GuiTreeViewLayout::findByLayout(GuiLayout *layout)
{
	if (this->layout == layout)
		return this;
	else
	{
		GuiTreeViewLayout *node = 0;
		for (unsigned int i = 0; i < getNumNodes(); i++)
		{
			node = dynamic_cast<GuiTreeViewLayout*>(getNode(i))->findByLayout(layout);
			if (node)
				break;
		}
		return node;
	}
}

void GuiTreeViewLayout::onInput()
{
	super::onInput();

	if (input.isButtonUp(SDL_BUTTON_LEFT))
	if (layout)
	{
		if (isSelected())
			layout->setSelected(true);
	}
}