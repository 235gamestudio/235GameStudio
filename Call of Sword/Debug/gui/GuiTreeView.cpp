#include "GuiTreeView.h"

#include "GuiManager.h"

GuiTexture *GuiTreeView::defaultTexture = 0;

GuiTreeView::GuiTreeView(glm::vec2 p, glm::vec2 s)
: GuiLayout(p, s)
, texture(defaultTexture)
, multiselect(true)
{
	setID(0x07);

	setLabel("treeview");
}
GuiTreeView::GuiTreeView(GuiTreeView &c)
: GuiLayout(c)
, multiselect(c.multiselect)
, texture(c.texture)
{
	for (unsigned int i = 0; i < c.getNumNodes(); i++)
		addNode(new GuiTreeViewNode(*c.getNode(i)));
}
GuiTreeView::~GuiTreeView()
{

}

GuiTreeViewNode *GuiTreeView::addNode(GuiTreeViewNode *node)
{
	if (!node)
		return 0;
	addLayout(node);
	nodes.push_back(node);
	node->setTree(this);
	node->setSize(node->getText()->getSize() + node->getText()->getPosition());
	return node;
}
GuiTreeViewNode *GuiTreeView::addNode(std::string text)
{
	GuiTreeViewNode *node = new GuiTreeViewNode();
	node->getText()->setText(text);
	return addNode(node);
}
GuiTreeViewNode *GuiTreeView::getNode(unsigned int i)
{
	return nodes.at(i);
}
unsigned int GuiTreeView::getNumNodes()
{
	return nodes.size();
}

void GuiTreeView::setMultiselect(bool s)
{
	multiselect = s;
}
bool GuiTreeView::isMultiselect()
{
	return multiselect;
}

std::vector<GuiTreeViewNode*> GuiTreeView::getSelectedNodes()
{
	return selectedNodes;
}

void GuiTreeView::onInput()
{
	super::onInput();


}
void GuiTreeView::onUpdate(float dt)
{
	super::onUpdate(dt);

	selectedNodes.clear();
	glm::vec2 pos = glm::vec2(0.0f);
	for (unsigned int i = 0; i < nodes.size(); i++)
		updateNode(nodes.at(i), dt, pos);
}
void GuiTreeView::onDraw()
{
	glm::vec2 position = getAbsolutePosition();

	glm::vec2 texSize = gui.getRenderer()->getTextureSize(texture);

	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(0.0f, 0.0f),
		(texSize / 3.0f),
		position,
		texSize / 3.0f);
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(1.0f, 0.0f),
		(texSize / 3.0f),
		position + (texSize / 3.0f) * glm::vec2(1.0f, 0.0f),
		glm::vec2(getSize().x - texSize.x*2.0f / 3.0f, texSize.y / 3.0f));
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(2.0f, 0.0f),
		(texSize / 3.0f),
		position + glm::vec2(getSize().x - texSize.x / 3.0f, 0.0f),
		texSize / 3.0f);
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(0.0f, 1.0f),
		(texSize / 3.0f),
		position + glm::vec2(0.0f, texSize.y / 3.0f),
		glm::vec2(texSize.x / 3.0f, getSize().y - 2.0f * texSize.y / 3.0f));
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(1.0f, 1.0f),
		(texSize / 3.0f),
		position + texSize / 3.0f,
		getSize() - 2.0f * texSize / 3.0f);
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(2.0f, 1.0f),
		(texSize / 3.0f),
		position + glm::vec2(getSize().x - texSize.x / 3.0f, texSize.y / 3.0f),
		glm::vec2(texSize.x / 3.0f, getSize().y - 2.0f * texSize.y / 3.0f));
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(0.0f, 2.0f),
		(texSize / 3.0f),
		position + glm::vec2(0.0f, getSize().y - texSize.y / 3.0f),
		texSize / 3.0f);
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(1.0f, 2.0f),
		(texSize / 3.0f),
		position + glm::vec2(texSize.x / 3.0f, getSize().y - texSize.y / 3.0f),
		glm::vec2(getSize().x - 2.0f * texSize.x / 3.0f, texSize.y / 3.0f));
	gui.getRenderer()->render(
		texture,
		(texSize / 3.0f) * glm::vec2(2.0f, 2.0f),
		(texSize / 3.0f),
		position + getSize() - texSize / 3.0f,
		texSize / 3.0f);

	super::onDraw();
}

void GuiTreeView::updateNode(GuiTreeViewNode *node, float dt, glm::vec2 &pos)
{
	if (!node)
		return;

	node->setPosition(pos);

	if (node->isSelected())
		selectedNodes.push_back(node);

	/* Move position */
	pos.y += node->getSize().y + 1.0f;

	/* Return, if subnodes are not visible */
	if (!node->isOpen())
		return;

	/* Move position and update subnodes */
	pos.x += 15.f;
	for (unsigned int i = 0; i < node->getNumNodes(); i++)
	if (node->getNode(i)->isEnabled())
		updateNode(node->getNode(i), dt, pos);
	pos.x -= 15.f;
}

void GuiTreeView::load(FILE *file)
{
	super::load(file);

	std::string path;
	fread(&path._Mysize(), sizeof(int), 1, file);
	path.reserve(path._Mysize());
	fread(&path[0], sizeof(char), path._Mysize(), file);
	texture = gui.getTexture(path);

	unsigned int n = 0;
	fread(&n, sizeof(unsigned int), 1, file);
	for (unsigned int i = 0; i < n; i++) {
		nodes.push_back(new GuiTreeViewNode());
		nodes.at(nodes.size() - 1)->setTree(this);
		nodes.at(nodes.size()-1)->load(file);
	}
}
void GuiTreeView::save(FILE *file)
{
	super::save(file);

	std::string path = gui.getTexturePath(texture);
	fwrite(&path._Mysize(), sizeof(int), 1, file);
	fwrite(&path[0], sizeof(char), path._Mysize(), file);

	unsigned int n = nodes.size();
	fwrite(&n, sizeof(unsigned int), 1, file);
	for (unsigned int i = 0; i < n; i++)
		nodes.at(i)->save(file);
}

void GuiTreeView::setDefaultTexture(GuiTexture *t)
{
	defaultTexture = t;
}
GuiTexture *GuiTreeView::getDefaultTexture()
{
	return defaultTexture;
}


GuiLayout *GuiTreeViewFactory::create()
{
	return new GuiTreeView();
}
GuiLayout *GuiTreeViewFactory::copy(GuiLayout *c)
{
	return new GuiTreeView(*(GuiTreeView*)c);
}