#pragma once

#include <SDL.h>
#include <vector>

#include "BFF_Font.h"
#include "GuiLayout.h"

enum class eWrapMode
{
	None,
	WrapToLayout,
	WrapToParent,
};

enum class eAdjustMode
{
	None = 0,
	Horizontal = 1,
	Vertical = 2,
	HorizontalAndVertical = 3,
};

class GuiText : public GuiLayout
{
	GuiFont *font;
	std::string text;
	GuiTexture *texture;
	glm::vec4 color;
	std::vector<std::string>lines;
	std::vector<int>lineWidths;
	eAdjustMode adjustMode;
	eWrapMode wrapMode;
	glm::vec2 justify;

	static GuiFont *defaultFont;

	void adjustLayoutSize();
	void wrapText();
	void wrapTextToEnters();
	void wrapTextToLayout(GuiLayout *layout);
	void renderText();

public:
	static const float JustifyLeft;
	static const float JustifyRight;
	static const float JustifyTop;
	static const float JustifyBottom;
	static const float JustifyCenter;

	GuiText(std::string t = "Text", glm::vec2 p = glm::vec2(0.0f));
	GuiText(GuiFont *f, std::string t = "Text", glm::vec2 p = glm::vec2(0.0f));
	GuiText(GuiText &c);

	virtual void setFont(GuiFont *f);
	virtual GuiFont *getFont();
	virtual void setText(std::string t);
	virtual std::string &getText();
	virtual void setColor(int r, int g, int b);
	virtual void setColor(glm::vec4 c);
	virtual glm::vec4 getColor();

	virtual void setAdjustMode(eAdjustMode am);
	virtual bool isAdjustMode(eAdjustMode am);
	virtual void setWrapMode(eWrapMode wm);
	virtual eWrapMode getWrapMode();
	virtual void setJustify(float x, float y);
	virtual glm::vec2 getJustify();

	virtual void setSize(glm::vec2 s);
	virtual void onDraw();

	virtual void save(FILE *file);
	virtual void load(FILE *file);

	static void setDefaultFont(GuiFont *font);
	static GuiFont *getDefaultFont();
};

class GuiTextFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};