#include "GuiTreeViewNode.h"

#include "GuiManager.h"

GuiTexture *GuiTreeViewNode::defaultTextureSelected = 0;
GuiButton *GuiTreeViewNode::defaultButtonOpen = 0;
GuiText *GuiTreeViewNode::defaultText = 0;

GuiTreeViewNode::GuiTreeViewNode(glm::vec2 p)
: GuiLayout(p, glm::vec2(0.0f))
, textureSelected(defaultTextureSelected)
, open(false)
, tree(0)
, nodeParent(0)
{
	addLayout(buttonOpen = new GuiButton(*defaultButtonOpen));
	addLayout(text = new GuiText(*defaultText));

	buttonOpen->setSavable(false);
	buttonOpen->setLabel("treenodebutton");
	text->setSavable(false);

	setLabel("gui_treeviewnode");
}
GuiTreeViewNode::GuiTreeViewNode(GuiTreeViewNode &c)
: GuiLayout(c)
, open(c.open)
, selected(c.selected)
, textureSelected(c.textureSelected)
{
	addLayout(buttonOpen = new GuiButton(*c.getButtonOpen()));
	addLayout(text = new GuiText(*c.getText()));

	for (int i = 0; i < c.getNumNodes(); i++)
		addNode(new GuiTreeViewNode(*c.getNode(i)));
}
GuiTreeViewNode::~GuiTreeViewNode()
{

}

GuiTreeViewNode *GuiTreeViewNode::addNode(GuiTreeViewNode *node)
{
	tree->addLayout(node);
	nodes.push_back(node);
	node->setNodeParent(this);
	if (node->getNodeParent()->isOpen())
		node->setEnabled(true);
	else
		node->setEnabled(false);
	node->setTree(tree);
	node->setSize(node->getText()->getSize() + node->getText()->getPosition());
	return node;
}
GuiTreeViewNode *GuiTreeViewNode::addNode(std::string text)
{
	GuiTreeViewNode *node = new GuiTreeViewNode();
	node->getText()->setText(text);
	return addNode(node);
}
GuiTreeViewNode *GuiTreeViewNode::getNode(unsigned int i)
{
	return nodes.at(i);
}
unsigned int GuiTreeViewNode::getNumNodes()
{
	return nodes.size();
}

bool GuiTreeViewNode::isOpen()
{
	return open;
}
void GuiTreeViewNode::setOpen(bool b)
{
	if (open == b)
		return;
	open = b;
	if (b)
		getButtonOpen()->getText()->setText("-");
	else
		getButtonOpen()->getText()->setText("+");
}
bool GuiTreeViewNode::isSelected()
{
	return selected;
}
void GuiTreeViewNode::setSelected(bool b)
{
	selected = b;
}

void GuiTreeViewNode::setEnabled(bool b)
{
	super::setEnabled(b);

	for (unsigned int i = 0; i < getNumNodes(); i++)
	{
		if (b == false || (b == true && this->isOpen()))
			getNode(i)->setEnabled(b);
	}
}

void GuiTreeViewNode::setNodeParent(GuiTreeViewNode *p)
{
	nodeParent = p;
}
GuiTreeViewNode *GuiTreeViewNode::getNodeParent()
{
	return nodeParent;
}
void GuiTreeViewNode::setTree(GuiTreeView *t)
{
	tree = t;
}
GuiTreeView *GuiTreeViewNode::getTree()
{
	return tree;
}
void GuiTreeViewNode::setButtonOpen(GuiButton *b)
{
	buttonOpen = b;
}
GuiButton *GuiTreeViewNode::getButtonOpen()
{
	return buttonOpen;
}
void GuiTreeViewNode::setText(GuiText *t)
{
	text = t;
}
GuiText *GuiTreeViewNode::getText()
{
	return text;
}

void GuiTreeViewNode::onInput()
{
	super::onInput();

	if (input.isButtonDown(SDL_BUTTON_LEFT) || input.isButtonDown(SDL_BUTTON_RIGHT))
	{
		if (gui.isPointInRect(input.mouse, getAbsolutePosition(), getSize()))
		{
			if (input.isKey(SDL_SCANCODE_LCTRL))
				selected = !selected;
			else
				selected = true;
		}
	}
}
void GuiTreeViewNode::onUpdate(float dt)
{
	super::onUpdate(dt);

	if (input.isButton(SDL_BUTTON_LEFT))
	if (!input.isKey(SDL_SCANCODE_LCTRL) || !tree->isMultiselect())
	if (!gui.isPointInRect(input.mouse, getAbsolutePosition(), getSize()))
	if (gui.isPointInRect(input.mouse, tree->getAbsolutePosition(), tree->getSize()))
		selected = false;

	if (buttonOpen->isClicked())
	{
		if (isOpen())
		{
			setOpen(false);
			for (unsigned int i = 0; i < getNumNodes(); i++)
				getNode(i)->setEnabled(false);
		}
		else
		{
			setOpen(true);
			for (unsigned int i = 0; i < getNumNodes(); i++)
				getNode(i)->setEnabled(true);
		}
	}
}
void GuiTreeViewNode::onDraw()
{
	glm::vec2 position = getAbsolutePosition();

	glm::vec2 texSize = gui.getRenderer()->getTextureSize(textureSelected);

	if (selected)
		gui.getRenderer()->render(
		textureSelected,
		glm::vec2(tree->getAbsolutePosition().x, position.y),
		glm::vec2(tree->getSize().x, getSize().y));

	super::onDraw();
}

void GuiTreeViewNode::load(FILE *file)
{
	super::load(file);

	std::string path;
	fread(&path._Mysize(), sizeof(int), 1, file);
	path.reserve(path._Mysize());
	fread(&path[0], sizeof(char), path._Mysize(), file);
	if (path.size() > 0)
		textureSelected = gui.getTexture(path);

	buttonOpen->load(file);
	text->load(file);
}
void GuiTreeViewNode::save(FILE *file)
{
	super::save(file);

	std::string path = gui.getTexturePath(textureSelected);
	fwrite(&path._Mysize(), sizeof(int), 1, file);
	fwrite(&path[0], sizeof(char), path._Mysize(), file);

	buttonOpen->save(file);
	text->save(file);
}

void GuiTreeViewNode::setDefaultTextureSelected(GuiTexture *t)
{
	defaultTextureSelected = t;
}
GuiTexture *GuiTreeViewNode::getDefaultTextureSelected()
{
	return defaultTextureSelected;
}
void GuiTreeViewNode::setDefaultButtonOpen(GuiButton *b)
{
	defaultButtonOpen = b;
}
GuiButton *GuiTreeViewNode::getDefaultButtonOpen()
{
	return defaultButtonOpen;
}
void GuiTreeViewNode::setDefaultText(GuiText *t)
{
	defaultText = t;
}
GuiText *GuiTreeViewNode::getDefaultText()
{
	return defaultText;
}