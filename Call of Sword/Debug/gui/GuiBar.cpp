#include "GuiBar.h"
#include "GuiManager.h"

GuiBar::GuiBar(glm::vec2 p, glm::vec2 s) :
	GuiBar( p, s)
{

}
GuiBar::GuiBar(GuiTexture *t, glm::vec2 p, glm::vec2 s)
	: GuiLayout(p, s)
	, texture(t)
{
	setLabel("bar");

	if (getSize().x < 0.0f || getSize().y < 0.0f)
		setSize(gui.getRenderer()->getTextureSize(texture));

	addLayout(buttonEQ = new GuiButton(gui.getTexture("images/other/sidebar_eq.png"),"", glm::vec2(0.0f, 0.0f)));
	addLayout(buttonMap = new GuiButton(gui.getTexture("images/other/sidebar_map.png"), "", glm::vec2(0.0f, 74.0f)));
	addLayout(buttonQuests = new GuiButton(gui.getTexture("images/other/sidebar_quests.png"), "", glm::vec2(0.0f, 148.0f)));
	addLayout(buttonSpells = new GuiButton(gui.getTexture("images/other/sidebar_spells.png"), "", glm::vec2(0.0f, 222.0f)));
	addLayout(buttonStatus = new GuiButton(gui.getTexture("images/other/sidebar_status.png"), "", glm::vec2(0.0f, 296.0f)));
	addLayout(buttonArrow = new GuiButton(gui.getTexture("images/other/sidebar_arrow_left.png"), "", glm::vec2(74.0f, 148.0f)));

	buttonEQ->setLabel("windowbuttoneq");
	buttonMap->setLabel("windowbuttonmap");
	buttonQuests->setLabel("windowbuttonquests");
	buttonSpells->setLabel("windowbuttonspells");
	buttonStatus->setLabel("windowbuttonstatus");
	buttonArrow->setLabel("windowbuttonarrow");

	isExpanded = true;
	expandedPosX = 0;
	hiddenPosX = expandedPosX - buttonEQ->getSize().x;

}
GuiBar::GuiBar(const GuiBar &c)
	: GuiLayout(c)
	, texture(c.texture)
{
	
}

void GuiBar::setTexture(GuiTexture *texture)
{
	this->texture = texture;
	if (texture)
		setSize(gui.getRenderer()->getTextureSize(texture));
}
GuiTexture *GuiBar::getTexture()
{
	return texture;
}

void GuiBar::onInput()
{
	super::onInput();
	
}
void GuiBar::onUpdate(float dt)
{
	super::onUpdate(dt);

	if (buttonArrow->isClicked())
	{
		if (isExpanded)
		{
			isExpanded = false;
			dstPos = expandedPosX - buttonEQ->getSize().x;
			buttonArrow->setTexture(gui.getTexture("images/other/sidebar_arrow_right.png"));
		}
		else
		{
			isExpanded = true;
			dstPos = hiddenPosX + buttonEQ->getSize().x;
			buttonArrow->setTexture(gui.getTexture("images/other/sidebar_arrow_left.png"));
		}
	}

	if (position.x != dstPos)
	{
		if (!isExpanded)
			position.x -= 0.5f;
		else
			position.x += 0.5f;
	}


}
void GuiBar::onDraw()
{
	glm::vec2 position = getAbsolutePosition();

	glm::vec2 texSize = gui.getRenderer()->getTextureSize(texture);

	gui.getRenderer()->render(
		texture,
		glm::vec2(0.0f, 0.0f),
		texSize,
		position,
		texSize);

	super::onDraw();
}