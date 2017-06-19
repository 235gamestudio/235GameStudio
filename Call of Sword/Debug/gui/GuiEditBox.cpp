#include "GuiEditBox.h"

#include "GuiManager.h"

GuiTexture *GuiEditBox::defaultTexture = 0;
GuiText *GuiEditBox::defaultText = 0;

GuiEditBox::GuiEditBox(glm::vec2 p, glm::vec2 s)
: GuiLayout(p, s)
, texture(defaultTexture)
, typing(false)
{
	setID(0x06);

	addLayout(text = new GuiText(*defaultText));
	text->setSavable(false);

	setLabel("editbox");
}
GuiEditBox::GuiEditBox(const GuiEditBox &c)
: GuiLayout(c)
, texture(c.texture)
, typing(false)
{
	addLayout(text = new GuiText(*c.text));
}

void GuiEditBox::onInput()
{
	super::onInput();

	if (input.isButtonDown(SDL_BUTTON_LEFT))
	if (gui.isPointInRect(input.mouse, getAbsolutePosition(), getSize()))
		typing = true;

	if (input.isAnyKeyDown())
	if (typing)
	{
		std::string t = text->getText();
		if (input.isKeyDown(SDL_SCANCODE_BACKSPACE))
		{
			if (t.length() > 0)
				t.pop_back();
		}
		else
		{
			t.push_back((char)input.event.key.keysym.sym);
		}
		text->setText(t);
	}
}
void GuiEditBox::onUpdate(float dt)
{
	super::onUpdate(dt);

	if (input.isButtonDown(SDL_BUTTON_LEFT))
	if (!gui.isPointInRect(input.mouse, getAbsolutePosition(), getSize()))
		typing = false;
}
void GuiEditBox::onDraw()
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

void GuiEditBox::setTexture(GuiTexture *t)
{
	texture = t;
}
GuiTexture *GuiEditBox::getTexture()
{
	return texture;
}
void GuiEditBox::setText(GuiText *t)
{
	text = t;
}
GuiText *GuiEditBox::getText()
{
	return text;
}
bool GuiEditBox::isTyping()
{
	return typing;
}

void GuiEditBox::load(FILE *file)
{
	super::load(file);

	std::string path;
	fread(&path._Mysize(), sizeof(int), 1, file);
	path.reserve(path._Mysize());
	fread(&path[0], sizeof(char), path._Mysize(), file);
	texture = gui.getTexture(path);

	text->load(file);
}
void GuiEditBox::save(FILE *file)
{
	super::save(file);

	std::string path = gui.getTexturePath(texture);
	fwrite(&path._Mysize(), sizeof(int), 1, file);
	fwrite(&path[0], sizeof(char), path._Mysize(), file);

	text->save(file);
}

void GuiEditBox::setDefaultTexture(GuiTexture *t)
{
	defaultTexture = t;
}
GuiTexture *GuiEditBox::getDefaultTexture()
{
	return defaultTexture;
}
void GuiEditBox::setDefaultText(GuiText *t)
{
	defaultText = t;
}
GuiText *GuiEditBox::getDefaultText()
{
	return 	defaultText;
}


GuiLayout *GuiEditBoxFactory::create()
{
	return new GuiEditBox();
}
GuiLayout *GuiEditBoxFactory::copy(GuiLayout *c)
{
	return new GuiEditBox(*(GuiEditBox*)c);
}