#include "GuiLayout.h"

#include "GuiManager.h"

const float GuiLayout::AlignLeft = 0.0f;
const float GuiLayout::AlignRight = 1.0f;
const float GuiLayout::AlignTop = 0.0f;
const float GuiLayout::AlignBottom = 1.0f;
const float GuiLayout::AlignCenter = 0.5f;

GuiLayout::GuiLayout(glm::vec2 p, glm::vec2 s) :
label("layout"),
parent(0),
position(p),
size(s),
align(glm::vec2(AlignLeft, AlignTop)),
enabled(true),
destroyed(false),
removed(false),
savable(true),
editable(false),
focusable(true)
{
	viewport = glm::vec4(0.f, 0.f, size.x, size.y);
	setID(0x01);
}
GuiLayout::GuiLayout() :
GuiLayout(glm::vec2(0.0f), glm::vec2(0.0f))
{

}
GuiLayout::GuiLayout(const GuiLayout& c)
: label(c.label)
, parent(c.parent)
, position(c.position)
, size(c.size)
, align(c.align)
, viewport(c.viewport)
, enabled(c.enabled)
, removed(c.removed)
, destroyed(c.destroyed)
, savable(c.savable)
, id(c.id)
, editable(c.editable)
, focusable(c.focusable)
{
	for (unsigned int i = 0; i < c.childs.size(); i++)
	if (c.childs[i]->isSavable())
	{
		GuiLayout *layout = gui.getFactory(c.childs[i]->id)->copy(c.childs[i]);
		addLayout(layout);
	}
}
GuiLayout::~GuiLayout()
{
	/* delete all childrens */
	for (unsigned int i = 0; i < getNumChildrens(); i++)
	if (getChildren(i))
		delete getChildren(i);
}

void GuiLayout::setLabel(std::string label)
{
	this->label = label;
}
std::string GuiLayout::getLabel()
{
	return label;
}
void GuiLayout::setPosition(glm::vec2 p)
{
	position = p;
}
glm::vec2 GuiLayout::getPosition()
{
	return position;
}
void GuiLayout::move(glm::vec2 d)
{
	position += d;
}
void GuiLayout::setSize(glm::vec2 s)
{
	size = s;
}
glm::vec2 GuiLayout::getSize()
{
	return size;
}
void GuiLayout::setAlign(float h, float v)
{
	align.x = h;
	align.y = v;
}
glm::vec2 GuiLayout::getAlign()
{
	return align;
}
void GuiLayout::setParent(GuiLayout *p)
{
	parent = p;
}
GuiLayout *GuiLayout::getParent()
{
	return parent;
}
void GuiLayout::setViewport(glm::vec4 v)
{
	viewport = v;
}
glm::vec4 GuiLayout::getViewport()
{
	return viewport;
}
void GuiLayout::setEnabled(bool s)
{
	enabled = s;
}
bool GuiLayout::isEnabled()
{
	return enabled;
}
bool GuiLayout::isDisabled()
{
	return (!enabled || destroyed || removed);
}
void GuiLayout::setSelected(bool s)
{
	selected = s;
}
bool GuiLayout::isSelected()
{
	return selected;
}
void GuiLayout::setRemoved(bool s)
{
	removed = s;
}
void GuiLayout::remove()
{
	removed = true;
}
bool GuiLayout::isRemoved()
{
	return (removed || destroyed);
}
void GuiLayout::setDestroyed(bool s)
{
	destroyed = s;
}
void GuiLayout::destroy()
{
	destroyed = true;
}
bool GuiLayout::isDestroyed()
{
	return destroyed;
}
void GuiLayout::setSavable(bool s)
{
	savable = s;
}
bool GuiLayout::isSavable()
{
	return savable;
}
void GuiLayout::setEditable(bool s)
{
	editable = s;
}
bool GuiLayout::isEditable()
{
	return editable;
}
void GuiLayout::setFocusable(bool s)
{
	focusable = s;
}
bool GuiLayout::isFocusable()
{
	return focusable;
}

glm::vec2 GuiLayout::getAbsolutePosition()
{
	if (getParent() != 0) {
		return (getPosition() + getParent()->getSize()*getAlign() + getParent()->getAbsolutePosition() - getSize()*getAlign());
	}
	else {
		return getPosition() - getSize()*getAlign();
	}
}
void GuiLayout::setAbsolutePosition(glm::vec2 p)
{
	setPosition(p - getAbsolutePosition() + getPosition());
}

GuiLayout *GuiLayout::find(std::string label)
{
	if (this->label == label)
		return this;
	else
	{
		GuiLayout *layout = 0;
		for (unsigned int i = 0; i < getNumChildrens(); i++)
		{
			if (!getChildren(i))
				continue;
			layout = getChildren(i)->find(label);
			if (layout)
				break;
		}
		return layout;
	}
}

GuiLayout *GuiLayout::addLayout(GuiLayout *layout)
{
	if (layout) {
		layout->setParent(this);
		//layout->setRemoved(false);
		//layout->setDestroyed(false);
	}
	childs.push_back(layout);
	return childs.at(childs.size()-1);
}
GuiLayout *GuiLayout::getChildren(int i)
{
	return childs.at(i);
}
void GuiLayout::removeChildren(int i)
{
	childs.erase(childs.begin() + i);
}
void GuiLayout::removeAllChildrens()
{
	for (unsigned int i = 0; i < childs.size(); i++)
		removeChildren(i);
}
unsigned int GuiLayout::getNumChildrens()
{
	return childs.size();
}

void GuiLayout::onInput()
{

}
void GuiLayout::onUpdate(float dt)
{

}
void GuiLayout::onDraw()
{
	gui.getEditor()->onLayoutDraw(this, gui.getMode());
}

void GuiLayout::setID(int i)
{
	id = i;
}
int GuiLayout::getID()
{
	return id;
}

void GuiLayout::load(FILE *file)
{
	/* Load label */
	fread(&label._Mysize(), sizeof(int), 1, file);
	label.reserve(label._Mysize());
	fread(&label[0], sizeof(char), label._Mysize(), file);
	/* Load position, size, align */
	fread(&position, sizeof(glm::vec2), 3, file);
	/* Load savable, editable */
	fread(&savable, sizeof(bool), 3, file);
}
void GuiLayout::save(FILE *file)
{
	/* Save label */
	fwrite(&label._Mysize(), sizeof(int), 1, file);
	fwrite(&label[0], sizeof(char)*label._Mysize(), 1, file);
	/* Save position, size, align */
	fwrite(&position, sizeof(glm::vec2), 3, file);
	/* Save savable, editable */
	fwrite(&savable, sizeof(bool), 3, file);
}

bool GuiLayout::layoutClick()
{
	int mousePosX, mousePosY;
	SDL_GetMouseState(&mousePosX, &mousePosY);
	glm::vec2 layoutPos;
	layoutPos = getAbsolutePosition();
	glm::vec2 layoutSize;
	layoutSize = getSize();

#define horizontal (mousePosX >= layoutPos.x && mousePosX <= layoutPos.x + layoutSize.x)
#define vertical (mousePosY >= layoutPos.y && mousePosY <= layoutPos.y + layoutSize.y)

	if (horizontal && vertical)
		return true;
	else
		return false;
}