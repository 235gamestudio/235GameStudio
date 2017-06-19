#include "GuiImage.h"

#include "GuiManager.h"

GuiImage::GuiImage(glm::vec2 p, glm::vec2 s) :
GuiImage(text, p, s)
{

}
GuiImage::GuiImage(GuiTexture *t, glm::vec2 p, glm::vec2 s)
: GuiLayout(p, s)
, texture(t)
{
	setLabel("image");

	if (getSize().x < 0.0f || getSize().y < 0.0f)
		setSize(gui.getRenderer()->getTextureSize(texture));

}
GuiImage::GuiImage(const GuiImage &c)
: GuiLayout(c)
, texture(c.texture)
{
	addLayout(this->text = new GuiText(*c.text));
	this->text->setText(c.text->getText());
}

void GuiImage::setTexture(GuiTexture *texture)
{
	this->texture = texture;
	if (texture)
		setSize(gui.getRenderer()->getTextureSize(texture));
}
GuiTexture *GuiImage::getTexture()
{
	return texture;
}
void GuiImage::setText(GuiText *t)
{
	if (text)
		delete text;
	text = t;
}
GuiText *GuiImage::getText()
{
	return text;
}

void GuiImage::onInput()
{
	super::onInput();
}
void GuiImage::onUpdate(float dt)
{
	super::onUpdate(dt);
}
void GuiImage::onDraw()
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