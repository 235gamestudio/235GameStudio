#pragma once

#include <vector>

#include "GuiTreeViewNode.h"

class GuiTreeView : public GuiLayout
{
	GuiTexture *texture;

	std::vector<GuiTreeViewNode*>nodes;
	std::vector<GuiTreeViewNode*>selectedNodes;

	bool multiselect;

	void updateNode(GuiTreeViewNode *node, float dt, glm::vec2 &pos);

	static GuiTexture *defaultTexture;

public:
	GuiTreeView(glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(0.0f));
	GuiTreeView(GuiTreeView &c);
	~GuiTreeView();

	GuiTreeViewNode *addNode(GuiTreeViewNode *node);
	GuiTreeViewNode *addNode(std::string text);
	GuiTreeViewNode *getNode(unsigned int i);
	unsigned int getNumNodes();

	void setMultiselect(bool s);
	bool isMultiselect();

	std::vector<GuiTreeViewNode*> getSelectedNodes();

	virtual void onInput();
	virtual void onUpdate(float dt);
	virtual void onDraw();

	void load(FILE *file);
	void save(FILE *file);

	static void setDefaultTexture(GuiTexture *t);
	static GuiTexture *getDefaultTexture();
};


class GuiTreeViewFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};