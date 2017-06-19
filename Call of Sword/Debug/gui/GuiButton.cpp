#include "GuiButton.h"

#include "GuiManager.h"

GuiTexture *GuiButton::defaultTexture = 0;
GuiText *GuiButton::defaultText = 0;

GuiButton::GuiButton(std::string text, glm::vec2 p, glm::vec2 s) :
GuiButton(defaultTexture, text, p, s)
{

}
GuiButton::GuiButton(GuiTexture *t, std::string text, glm::vec2 p, glm::vec2 s)
: GuiLayout(p, s)
, texture(t)
, pressed(false)
, clicked(false)
{
	setID(0x03);

	setLabel("button");

	if (getSize().x < 0.0f || getSize().y < 0.0f)
		setSize(gui.getRenderer()->getTextureSize(texture));

	addLayout(this->text = new GuiText(*defaultText));
	this->text->setText(text);
	this->text->setSavable(false);
}
GuiButton::GuiButton(const GuiButton &c)
: GuiLayout(c)
, texture(c.texture)
, pressed(c.pressed)
, clicked(c.clicked)
{
	addLayout(this->text = new GuiText(*c.text));
	this->text->setText(c.text->getText());
}

bool GuiButton::isPressed()
{
	return pressed;
}
bool GuiButton::isClicked()
{
	bool c = clicked;
	clicked = false;
	return c;
}

void GuiButton::setTexture(GuiTexture *texture)
{
	this->texture = texture;
	if (texture)
		setSize(gui.getRenderer()->getTextureSize(texture));
}
GuiTexture *GuiButton::getTexture()
{
	return texture;
}
void GuiButton::setText(GuiText *t)
{
	if (text)
		delete text;
	text = t;
}
GuiText *GuiButton::getText()
{
	return text;
}

void GuiButton::onInput()
{
	super::onInput();

	if (input.isButtonUp(SDL_BUTTON_LEFT)
		&& gui.isPointInRect(input.mouse, getAbsolutePosition(), getSize()))
		clicked = true;
}
void GuiButton::onUpdate(float dt)
{
	super::onUpdate(dt);


}
void GuiButton::onDraw()
{
	glm::vec2 position = getAbsolutePosition();

	glm::vec2 texSize = gui.getRenderer()->getTextureSize(texture);

	gui.getRenderer()->render(
		texture,
		glm::vec2(0.0f, 0.0f),
		texSize,
		position,
		texSize);
	/*gui.getRenderer()->render(
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
		texSize / 3.0f);*/

	super::onDraw();
}

void GuiButton::load(FILE *file)
{
	super::load(file);

	std::string path;
	fread(&path._Mysize(), sizeof(int), 1, file);
	path.reserve(path._Mysize());
	fread(&path[0], sizeof(char), path._Mysize(), file);
	if (path.size() > 0)
		texture = gui.getTexture(path);

	text->load(file);
}
void GuiButton::save(FILE *file)
{
	super::save(file);

	std::string path = gui.getTexturePath(texture);
	fwrite(&path._Mysize(), sizeof(int), 1, file);
	fwrite(&path[0], sizeof(char), path._Mysize(), file);

	text->save(file);
}

void GuiButton::setDefaultTexture(GuiTexture *texture)
{
	defaultTexture = texture;
}
GuiTexture *GuiButton::getDefaultTexture()
{
	return defaultTexture;
}
void GuiButton::setDefaultText(GuiText *text)
{
	defaultText = text;
}
GuiText *GuiButton::getDefaultText()
{
	return defaultText;
}


GuiLayout *GuiButtonFactory::create()
{
	return new GuiButton();
}
GuiLayout *GuiButtonFactory::copy(GuiLayout *c)
{
	return new GuiButton(*(GuiButton*)c);
}