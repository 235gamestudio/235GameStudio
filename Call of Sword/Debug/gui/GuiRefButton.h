#pragma once

#include "GuiButton.h"

class GuiRefButton : public GuiButton
{
	std::string refPath;

public:
	GuiRefButton(std::string path, glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	GuiRefButton(std::string path, GuiTexture *texture, glm::vec2 p = glm::vec2(0.0f), glm::vec2 s = glm::vec2(-1.0f));
	void setRefPath(std::string path);
	std::string getRefPath();

	virtual void onUpdate(float dt);

	virtual void save(FILE *file);
	virtual void load(FILE *file);
};

class GuiRefButtonFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};