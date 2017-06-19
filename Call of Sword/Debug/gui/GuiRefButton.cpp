#include "GuiRefButton.h"

#include "GuiManager.h"

GuiRefButton::GuiRefButton(std::string path, GuiTexture *texture, glm::vec2 p, glm::vec2 s) :
GuiButton(texture, "sad", p, s),
refPath(path)
{
	setID(0x05);
}
GuiRefButton::GuiRefButton(std::string path, glm::vec2 p, glm::vec2 s) :
GuiRefButton(path, getDefaultTexture(), p, s)
{
}

void GuiRefButton::setRefPath(std::string path)
{
	this->refPath = path;
}
std::string GuiRefButton::getRefPath()
{
	return this->refPath;
}

void GuiRefButton::onUpdate(float dt)
{
	if (isClicked())
	if (getParent()->getParent())
	{
		GuiLayout *layout = gui.load(refPath);
		layout->setPosition(getParent()->getPosition());
		getParent()->getParent()->addLayout(layout);
		getParent()->remove();
	}
	else
	{
		getParent()->addLayout(gui.load(refPath));
		this->remove();
	}

	super::onUpdate(dt);
}

void GuiRefButton::save(FILE *file)
{
	super::save(file);

	fwrite(&refPath._Mysize(), sizeof(int), 1, file);
	fwrite(&refPath[0], sizeof(char), refPath._Mysize(), file);
}
void GuiRefButton::load(FILE *file)
{
	super::load(file);

	fread(&refPath._Mysize(), sizeof(int), 1, file);
	refPath.reserve(refPath._Mysize());
	fread(&refPath[0], sizeof(char), refPath._Mysize(), file);
}


GuiLayout *GuiRefButtonFactory::create()
{
	return new GuiRefButton("");
}
GuiLayout *GuiRefButtonFactory::copy(GuiLayout *c)
{
	return new GuiRefButton(*(GuiRefButton*)c);
}