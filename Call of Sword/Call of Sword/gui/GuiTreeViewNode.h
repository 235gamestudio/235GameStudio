#pragma once

#include <vector>

#include "GuiButton.h"

class GuiTreeView;

class GuiTreeViewNode : public GuiLayout
{
	std::vector<GuiTreeViewNode*>nodes;

	GuiTexture *textureSelected;
	GuiButton *buttonOpen;
	GuiText *text;

	GuiTreeView *tree;
	GuiTreeViewNode *nodeParent;
	bool open, selected;

	static GuiTexture *defaultTextureSelected;
	static GuiButton *defaultButtonOpen;
	static GuiText *defaultText;

public:
	GuiTreeViewNode(glm::vec2 p = glm::vec2(0.0f));
	GuiTreeViewNode(GuiTreeViewNode &c);
	~GuiTreeViewNode();

	virtual GuiTreeViewNode *addNode(GuiTreeViewNode *node);
	virtual GuiTreeViewNode *addNode(std::string text);
	virtual GuiTreeViewNode *getNode(unsigned int i);
	virtual unsigned int getNumNodes();

	virtual bool isOpen();
	virtual void setOpen(bool b);
	virtual bool isSelected();
	virtual void setSelected(bool b);
	void setEnabled(bool b);

	virtual void setNodeParent(GuiTreeViewNode *p);
	virtual GuiTreeViewNode *getNodeParent();
	virtual void setTree(GuiTreeView *t);
	virtual GuiTreeView *getTree();
	virtual void setButtonOpen(GuiButton *b);
	virtual GuiButton *getButtonOpen();
	virtual void setText(GuiText *t);
	virtual GuiText *getText();

	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();

	virtual void load(FILE *file);
	virtual void save(FILE *file);

	static void setDefaultTextureSelected(GuiTexture *t);
	static GuiTexture *getDefaultTextureSelected();
	static void setDefaultButtonOpen(GuiButton *b);
	static GuiButton *getDefaultButtonOpen();
	static void setDefaultText(GuiText *t);
	static GuiText *getDefaultText();
};