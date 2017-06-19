#include "GuiScrollBar.h"

#include "GuiManager.h"

GuiButton *GuiScrollBar::defaultButtonUp = 0;
GuiButton *GuiScrollBar::defaultButtonDown = 0;
GuiButton *GuiScrollBar::defaultButtonBar = 0;
GuiTexture *GuiScrollBar::defaultTexture = 0;

GuiScrollBar::GuiScrollBar(glm::vec2 p, glm::vec2 s)
: GuiLayout()
, texture(defaultTexture)
{
	addLayout(buttonUp = new GuiButton(*defaultButtonUp));
	addLayout(buttonDown = new GuiButton(*defaultButtonDown));
	addLayout(buttonBar = new GuiButton(*defaultButtonBar));
	buttonUp->setSavable(false);
	buttonDown->setSavable(false);
	buttonBar->setSavable(false);

	buttonUp->setSize(glm::vec2(s.x, s.x));
	buttonDown->setPosition(glm::vec2(0.0f, s.y - s.x));
	buttonDown->setSize(glm::vec2(s.x, s.x));
	buttonBar->setPosition(glm::vec2(0.0f, s.x));
	buttonBar->setSize(glm::vec2(s.x, s.y - 2.0f*s.x));
}
GuiScrollBar::~GuiScrollBar()
{

}

void GuiScrollBar::setButtonUp(GuiButton *b)
{
	buttonUp = b;
}
void GuiScrollBar::setButtonDown(GuiButton *b)
{
	buttonDown = b;
}
void GuiScrollBar::setButtonBar(GuiButton *b)
{
	buttonBar = b;
}
void GuiScrollBar::setTexture(GuiTexture *t)
{
	texture = t;
}
GuiButton *GuiScrollBar::getButtonUp()
{
	return buttonUp;
}
GuiButton *GuiScrollBar::getButtonDown()
{
	return buttonDown;
}
GuiButton *GuiScrollBar::getButtonBar()
{
	return buttonBar;
}
GuiTexture *GuiScrollBar::getTexture()
{
	return texture;
}

void GuiScrollBar::setSize(glm::vec2 s)
{
	super::setSize(s);

	buttonUp->setSize(glm::vec2(s.x, s.x));
	buttonDown->setPosition(glm::vec2(0.0f, s.y - s.x));
	buttonDown->setSize(glm::vec2(s.x, s.x));
	buttonBar->setPosition(glm::vec2(0.0f, s.x));
	buttonBar->setSize(glm::vec2(s.x, s.y - 2.0f*s.x));
}

void GuiScrollBar::onDraw()
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

void GuiScrollBar::setDefaultButtonUp(GuiButton *b)
{
	defaultButtonUp = b;
}
void GuiScrollBar::setDefaultButtonDown(GuiButton *b)
{
	defaultButtonDown = b;
}
void GuiScrollBar::setDefaultButtonBar(GuiButton *b)
{
	defaultButtonBar = b;
}
void GuiScrollBar::setDefaultTexture(GuiTexture *t)
{
	defaultTexture = t;
}
GuiButton *GuiScrollBar::getDefaultButtonUp()
{
	return defaultButtonUp;
}
GuiButton *GuiScrollBar::getDefaultButtonDown()
{
	return defaultButtonDown;
}
GuiButton *GuiScrollBar::getDefaultButtonBar()
{
	return defaultButtonBar;
}
GuiTexture *GuiScrollBar::getDefaultTexture()
{
	return defaultTexture;
}