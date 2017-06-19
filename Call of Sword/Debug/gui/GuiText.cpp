#include "GuiText.h"

#include "GuiManager.h"

const float GuiText::JustifyLeft = 0.0f;
const float GuiText::JustifyRight = 1.0f;
const float GuiText::JustifyTop = 0.0f;
const float GuiText::JustifyBottom = 1.0f;
const float GuiText::JustifyCenter = 0.5f;

GuiFont *GuiText::defaultFont = 0;

GuiText::GuiText(std::string t, glm::vec2 p) :
GuiText(defaultFont, t, p)
{

}
GuiText::GuiText(GuiFont *f, std::string t, glm::vec2 p)
: GuiLayout(p, glm::vec2(0.0f))
, font(f)
, color(glm::vec4(255, 255, 255, 0))
, adjustMode(eAdjustMode::HorizontalAndVertical)
, wrapMode(eWrapMode::None)
, justify(GuiText::JustifyLeft, GuiText::JustifyTop)
{
	setID(0x04);
	setLabel("text");

	setFocusable(false);

	//texture = gui.getRenderer()->createTexture(s);
	setText(t);
}
GuiText::GuiText(GuiText &c)
: GuiLayout(c)
, font(c.font)
, color(c.color)
, lines(c.lines)
, lineWidths(c.lineWidths)
, adjustMode(c.adjustMode)
, wrapMode(c.wrapMode)
, justify(c.justify)
{
	setLabel("text");

	setFocusable(false);

	texture = gui.getRenderer()->createTexture(getSize());
	setText(c.text);
}

void GuiText::setFont(GuiFont *f)
{
	font = f;
}
GuiFont *GuiText::getFont()
{
	return font;
}
void GuiText::setText(std::string t)
{
	text = t;
	wrapText();
	adjustLayoutSize();
	renderText();
}
std::string &GuiText::getText()
{
	return text;
}

void GuiText::setColor(int r, int g, int b)
{
	setColor(glm::vec4(r, g, b, 0));
}
void GuiText::setColor(glm::vec4 c)
{
	color = c;
	renderText();
}
glm::vec4 GuiText::getColor()
{
	return color;
}

void GuiText::setAdjustMode(eAdjustMode am)
{
	adjustMode = am;
	adjustLayoutSize();
}
bool GuiText::isAdjustMode(eAdjustMode am)
{
	return ((int)adjustMode & (int)am) ? true : false;
}
void GuiText::setWrapMode(eWrapMode wm)
{
	wrapMode = wm;
	wrapText();
}
eWrapMode GuiText::getWrapMode()
{
	return wrapMode;
}
void GuiText::setJustify(float x, float y)
{
	justify = glm::vec2(x, y);
}
glm::vec2 GuiText::getJustify()
{
	return justify;
}

void GuiText::setSize(glm::vec2 s)
{
	GuiLayout::setSize(s);

	gui.getRenderer()->destroyTexture(texture);
	texture = gui.getRenderer()->createTexture(s);
	renderText();
}
void GuiText::onDraw()
{
	//renderText();
	gui.getRenderer()->render(texture, getAbsolutePosition(), getSize());

	super::onDraw();
}

void GuiText::setDefaultFont(GuiFont *font)
{
	defaultFont = font;
}
GuiFont *GuiText::getDefaultFont()
{
	return defaultFont;
}

void GuiText::renderText()
{
	if (texture == 0)
		return;
	gui.getRenderer()->setRenderTarget(texture);
	gui.getRenderer()->clear(glm::ivec4(255, 0, 255, 0));

	for (unsigned int i = 0; i < lines.size(); i++)
		gui.getRenderer()->print(
		font,
		glm::vec2(
		getJustify().x*(getSize().x - lineWidths.at(i)),
		getJustify().y*(getSize().y - lines.size() * ((BFF_Font*)font)->getCellSize().y) + i * ((BFF_Font*)font)->getCellSize().y
		),
		lines.at(i),
		color
		);
	gui.getRenderer()->setRenderTarget(NULL);
}
void GuiText::adjustLayoutSize()
{
	if (isAdjustMode(eAdjustMode::None))
		return;

	glm::vec2 size = getSize();
	if (isAdjustMode(eAdjustMode::Horizontal))
	{
		size.x = 0.0f;
		/* find the longest line and set layout size */
		for (unsigned int i = 0; i < lineWidths.size(); i++)
		{
			if (lineWidths.at(i) > size.x)
				size.x = (float)lineWidths.at(i);
		}
	}
	if (isAdjustMode(eAdjustMode::Vertical))
		size.y = (float)lineWidths.size() * ((BFF_Font*)font)->getCellSize().y;

	setSize(size);
}
void GuiText::wrapText()
{
	if (wrapMode == eWrapMode::WrapToLayout)
		wrapTextToLayout(this);
	else
	if (wrapMode == eWrapMode::WrapToParent)
		wrapTextToLayout(getParent());
	else
		wrapTextToEnters();
}
void GuiText::wrapTextToEnters()
{
	lines.clear();
	lineWidths.clear();
	if (text.empty())
		return;
	lineWidths.push_back(0);
	std::string line = "";
	int lastNewLineIndex = 0;

	for (unsigned int i = 0; i < text.length(); i++)
	{
		/* wrap if new line character */
		if (text[i] == '\n') {
			/* push back text between two new line characters */
			lines.push_back(text.substr(lastNewLineIndex, i - lastNewLineIndex));
			lastNewLineIndex = i + 1;
			lineWidths.push_back(0);
			continue;
		}
		/* add character width to line width */
		lineWidths.at(lineWidths.size() - 1) += ((BFF_Font*)font)->getCharacterWidth(text[i]);
	}

	/* push back text from last new line character to the end of string */
	lines.push_back(text.substr(lastNewLineIndex, text.length() - lastNewLineIndex));
}
void GuiText::wrapTextToLayout(GuiLayout *layout)
{
	/* TODO: Implement */
}

void GuiText::save(FILE *file)
{
	super::save(file);

	std::string path = gui.getFontPath(font);
	fwrite(&path._Mysize(), sizeof(int), 1, file);
	fwrite(&path[0], sizeof(char), path._Mysize(), file);
	fwrite(&text._Mysize(), sizeof(int), 1, file);
	fwrite(&text[0], sizeof(char), text._Mysize(), file);
	fwrite(&color[0], sizeof(glm::ivec3), 1, file);
	fwrite(&adjustMode, sizeof(int), 1, file);
	fwrite(&wrapMode, sizeof(int), 1, file);
	fwrite(&justify[0], sizeof(glm::vec2), 1, file);
}
void GuiText::load(FILE *file)
{
	super::load(file);

	std::string path;
	fread(&path._Mysize(), sizeof(int), 1, file);
	path.reserve(path._Mysize());
	fread(&path[0], sizeof(char), path._Mysize(), file);
	setFont(gui.getFont(path));
	fread(&text._Mysize(), sizeof(int), 1, file);
	text.reserve(text._Mysize());
	fread(&text[0], sizeof(char), text._Mysize(), file);
	setText(text);
	fread(&color[0], sizeof(glm::ivec3), 1, file);
	fread(&adjustMode, sizeof(int), 1, file);
	fread(&wrapMode, sizeof(int), 1, file);
	fread(&justify[0], sizeof(glm::vec2), 1, file);
}


GuiLayout *GuiTextFactory::create()
{
	return new GuiText();
}
GuiLayout *GuiTextFactory::copy(GuiLayout *c)
{
	return new GuiText(*(GuiText*)c);
}