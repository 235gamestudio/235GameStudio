#include "GuiWindow.h"

#include "GuiManager.h"

GuiTexture *GuiWindow::defaultTexture = 0;
GuiButton *GuiWindow::defaultButtonX = 0;
GuiText *GuiWindow::defaultTitleText = 0;

GuiWindow::GuiWindow(glm::vec2 p, glm::vec2 s) :
GuiWindow(defaultTitleText->getText(), p, s)
{

}
GuiWindow::GuiWindow(std::string t, glm::vec2 p, glm::vec2 s) :
GuiLayout(p, s),
mouseOffset(glm::vec2(0.0f)),
texture(defaultTexture)
{
	setID(0x02);

	setLabel("window");

	if (getSize().x < 0.0f || getSize().y < 0.0f)
		setSize(gui.getRenderer()->getTextureSize(texture));

	addLayout(buttonX = new GuiButton(*defaultButtonX));
	addLayout(title = new GuiText(*defaultTitleText));
	buttonX->setSavable(false);
	buttonX->setLabel("windowbuttonx");
	title->setSavable(false);
	title->setText(t);
	title->setLabel("windowtitle");

	setViewport(glm::vec4(25.f, 38.f, 25.f, 25.f));
}
GuiWindow::GuiWindow(const GuiWindow &c)
: GuiLayout(c)
, texture(c.texture)
, mouseOffset(c.mouseOffset)
{
	buttonX = new GuiButton(*c.buttonX);
	title = new GuiText(*c.title);
}
GuiWindow::~GuiWindow()
{

}

void GuiWindow::onInput()
{
	super::onInput();

	if (input.isButtonDown(SDL_BUTTON_LEFT))
	{
		mouseOffset = input.mouse - getPosition();
	}
}
void GuiWindow::onUpdate(float dt)
{
	super::onUpdate(dt);

	if (buttonX->isClicked())
		this->destroy();

	if (!input.isButton(SDL_BUTTON_LEFT))
		mouseOffset = glm::vec2(-1.0f);

	if (input.isButton(SDL_BUTTON_LEFT) && mouseOffset.x > 0.0f)
		setPosition(input.mouse - mouseOffset);
}
void GuiWindow::onDraw()
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

void GuiWindow::setButtonX(GuiButton *button)
{
	if (buttonX)
		delete buttonX;
	buttonX = button;
}
GuiButton *GuiWindow::getButtonX()
{
	return buttonX;
}
void GuiWindow::setTitle(GuiText *text)
{
	if (title)
		delete title;
	title = text;
}
GuiText *GuiWindow::getTitle()
{
	return title;
}

void GuiWindow::load(FILE *file)
{
	super::load(file);

	std::string path;

	fread(&path._Mysize(), sizeof(int), 1, file);
	path.reserve(path._Mysize());
	fread(&path[0], sizeof(char), path._Mysize(), file);
	texture = gui.getTexture(path);

	buttonX->load(file);
	title->load(file);
}
void GuiWindow::save(FILE *file)
{
	super::save(file);

	std::string path = gui.getTexturePath(texture);
	fwrite(&path._Mysize(), sizeof(int), 1, file);
	fwrite(&path[0], sizeof(char), path._Mysize(), file);

	buttonX->save(file);
	title->save(file);
}

void GuiWindow::setDefaultTexture(GuiTexture *t)
{
	if (defaultTexture)
		;/* TODO: delete texture */
	defaultTexture = t;
}
GuiTexture *GuiWindow::getDefaultTexture()
{
	return defaultTexture;
}
void GuiWindow::setDefaultButtonX(GuiButton *b)
{
	if (defaultButtonX)
		delete defaultButtonX;
	defaultButtonX = b;
}
GuiButton *GuiWindow::getDefaultButtonX()
{
	return defaultButtonX;
}
void GuiWindow::setDefaultTitleText(GuiText *t)
{
	if (defaultTitleText)
		delete defaultTitleText;
	defaultTitleText = t;
}
GuiText *GuiWindow::getDefaultTitleText()
{
	return defaultTitleText;
}


GuiLayout *GuiWindowFactory::create()
{
	return new GuiWindow();
}
GuiLayout *GuiWindowFactory::copy(GuiLayout *c)
{
	return new GuiWindow(*(GuiWindow*)c);
}