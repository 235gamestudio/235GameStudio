#include "GuiManager.h"

GuiManager::GuiManager()
: mode(0)
, focus(root)
{
	/* create root layout */
	root = new GuiLayout();
	root->setLabel("root_layout");
	/* create default editor */
	editor = new GuiEditor();
}
GuiManager::~GuiManager()
{
	if (root) 
		delete root;

	for (auto& texture : textures)
		renderer->destroyTexture(texture.second);

	for (auto& font : fonts)
		delete (BFF_Font*)(font.second);

	for (auto& factory : factories)
		delete factory.second;

	delete GuiButton::getDefaultText();
	delete GuiWindow::getDefaultButtonX();
	delete GuiWindow::getDefaultTitleText();
	delete GuiEditBox::getDefaultText();
	delete GuiTreeViewNode::getDefaultButtonOpen();
	delete GuiTreeViewNode::getDefaultText();
	delete GuiFileDialog::getDefaultEditBox();
	delete GuiFileDialog::getDefaultFileButton();
	delete GuiFileDialog::getDefaultTreeView();
	delete GuiScrollBar::getDefaultButtonBar();
	delete GuiScrollBar::getDefaultButtonDown();
	delete GuiScrollBar::getDefaultButtonUp();


	delete renderer;
	delete editor;
}
GuiManager &GuiManager::get()
{
	static GuiManager instance;
	return instance;
}

void GuiManager::init(GuiRenderer *renderer)
{
	setRenderer(renderer);
	/* Set default values for all layouts */
#pragma region GuiDefaultSettings
	/* GuiText */
	GuiText::setDefaultFont(
		gui.getFont("Data/Fonts/ArialUnicodeMS.bff")
		);
	/* GuiButton */

	GuiButton::setDefaultTexture(
		gui.getTexture("Data/Textures/Gui/gui_default_button02.png")
		);
	GuiButton::setDefaultText(new GuiText(
		gui.getFont("Data/Fonts/TektonProBoldCond.bff"),
		"Button",
		glm::vec2(0.0f)
		));

	GuiButton::getDefaultText()->setAlign(GuiLayout::AlignCenter, GuiLayout::AlignCenter);
	GuiButton::getDefaultText()->setJustify(GuiText::JustifyCenter, GuiText::JustifyCenter);
	/* GuiWindow */
	GuiWindow::setDefaultTexture(gui.getTexture("Data/Textures/Gui/gui_window.png"));
	GuiWindow::setDefaultButtonX(new GuiButton(
		gui.getTexture("Data/Textures/Gui/gui_window_button_x.png"),
		"",
		glm::vec2(-36.0f, 21.0f)
		));
	GuiWindow::getDefaultButtonX()->setAlign(GuiLayout::AlignRight, GuiLayout::AlignTop);
	GuiWindow::setDefaultTitleText(new GuiText(
		gui.getFont("Data/Fonts/TektonProBoldCond.bff"),
		"Untitled",
		glm::vec2(0.0f, 19.0f)
		));
	GuiWindow::getDefaultTitleText()->setAlign(GuiLayout::AlignCenter, GuiLayout::AlignTop);
	GuiWindow::getDefaultTitleText()->setJustify(GuiText::JustifyCenter, GuiText::JustifyCenter);
	GuiWindow::getDefaultTitleText()->setColor(224, 217, 177);
	/* GuiEditBox */
	GuiEditBox::setDefaultTexture(gui.getTexture("Data/Textures/Gui/gui_frame.png"));
	GuiEditBox::setDefaultText(new GuiText(
		gui.getFont("Data/Fonts/TektonProBoldCond.bff"),
		"",
		glm::vec2(3.0f, -1.0f)
		));
	GuiEditBox::getDefaultText()->setAlign(GuiLayout::AlignLeft, GuiLayout::AlignCenter);
	GuiEditBox::getDefaultText()->setJustify(GuiText::JustifyLeft, GuiText::JustifyCenter);
	/* GuiTreeView */
	GuiTreeView::setDefaultTexture(gui.getTexture("Data/Textures/Gui/gui_frame.png"));
	/* GuiTreeViewNode */
	GuiTreeViewNode::setDefaultTextureSelected(gui.getTexture("Data/Textures/Gui/gui_treenode_selected.png"));
	GuiTreeViewNode::setDefaultButtonOpen(new GuiButton(
		"+",
		glm::vec2(0.0f),
		glm::vec2(15.0f)
		));
	GuiTreeViewNode::getDefaultButtonOpen()->setTexture(0);
	GuiTreeViewNode::getDefaultButtonOpen()->getText()->move(glm::vec2(0.0f, -4.0f));
	GuiTreeViewNode::setDefaultText(new GuiText(
		gui.getFont("Data/Fonts/Arial_15.bff"),
		"Text",
		glm::vec2(23.0f, 0.0f)
		));

	/* GuiFileDialog */
	GuiFileDialog::setDefaultTreeView(new GuiTreeView(
		glm::vec2(25.0f, 40.0f),
		glm::vec2(350.0f, 210.0f)
		));
	GuiFileDialog::setDefaultFileButton(new GuiButton(
		"Load",
		glm::vec2(315.0f, 250.0f),
		glm::vec2(60.0f, 25.0f)
		));
	GuiFileDialog::setDefaultEditBox(new GuiEditBox(
		glm::vec2(25.0f, 250.0f),
		glm::vec2(290.0f, 25.0f)
		));
	/* GuiScrollBar */
	GuiScrollBar::setDefaultButtonUp(new GuiButton(
		gui.getTexture("Data/Textures/Gui/gui_default_button02.png"),
		""
		));
	GuiScrollBar::setDefaultButtonDown(new GuiButton(
		gui.getTexture("Data/Textures/Gui/gui_default_button02.png"),
		""
		));
	GuiScrollBar::setDefaultButtonBar(new GuiButton(
		gui.getTexture("Data/Textures/Gui/gui_default_button02.png"),
		""
		));
	GuiScrollBar::setDefaultTexture(
		gui.getTexture("Data/Textures/Gui/gui_frame.png")
		);
#pragma endregion
}

void GuiManager::moveAtForeground(GuiLayout *layout)
{
	if (!layout->getParent())
		return;

	/* remove layout */
	for (unsigned int i = 0; i < layout->getParent()->getNumChildrens(); i++)
	if (layout->getParent()->getChildren(i) == layout)
		layout->getParent()->removeChildren(i);

	/* add layout at the end */
	layout->getParent()->addLayout(layout);

	/* do the same to all of the parents */
	moveAtForeground(layout->getParent());
}

bool GuiManager::inputLayout(GuiLayout *layout, bool handled)
{
	/* return, if layout doesn't exist or it is disabled */
	if (!layout)
		return handled;
	if (layout->isDisabled())
		return handled;

	/* handle input, starting from the last one in the hierarchy */
	/* first, we're going at the end of the hierarchy */
	for (unsigned int i = layout->getNumChildrens(); i > 0; i--) {
		handled = inputLayout(layout->getChildren(i - 1), handled);
	}

	/* Handling nexts layouts (from the end to the beggining), */
	/* if there was any mouse event on the layout and any other layout has been handled */

	if (isPointInRect(GuiInput::get().mouse, layout->getAbsolutePosition(), layout->getSize()))
	if (GuiInput::get().isAnyButtonDown())
	if (layout->isFocusable())
	if (!handled)
	{
		moveAtForeground(layout);
		focus = layout;
		handled = true;
	}

	return handled;
}
void GuiManager::updateLayout(GuiLayout *layout, float dt)
{
	/* return, if layout doesn't exist or it is disabled */
	if (!layout)
		return;
	if (layout->isDisabled())
		return;

	/* update layout */
	if (layout->isEditable() && getMode()&SGUI_MODE_EDIT_MODE)
		editor->onLayoutUpdate(layout, mode);
	else
		layout->onUpdate(dt);

	/* and all childrens */
	for (unsigned int i = 0; i < layout->getNumChildrens(); i++)
	{
		if (!layout->getChildren(i))
			continue;

		/* destroy layout, if it has 'destroyed' flag set */
		if (layout->getChildren(i)->isDestroyed())
		{
			delete layout->getChildren(i);
			layout->removeChildren(i);
			focus = 0;
			i--;
		}
		else
		if (layout->getChildren(i)->isRemoved())
		{
			layout->setParent(0);
			layout->removeChildren(i);
			focus = 0;
			i--;
		}
		else
			updateLayout(layout->getChildren(i), dt);
	}
}
void GuiManager::drawLayout(GuiLayout *layout)
{
	/* return, if layout doesn't exist or it is disabled */
	if (!layout)
		return;
	if (layout->isDisabled())
		return;

	/* Render layout */
	layout->onDraw();

	/* Render all childrens */
	for (unsigned int i = 0; i < layout->getNumChildrens(); i++)
	{
		drawLayout(layout->getChildren(i));
	}
}

void GuiManager::saveLayout(GuiLayout *layout, FILE *file)
{
	int id = layout->getID();
	fwrite(&id, sizeof(int), 1, file);
	layout->save(file);

	for (unsigned int i = 0; i < layout->getNumChildrens(); i++)
	if (layout->getChildren(i)->isSavable())
		saveLayout(layout->getChildren(i), file);

	id = 0x00;
	fwrite(&id, sizeof(int), 1, file);
}
GuiLayout *GuiManager::loadLayout(FILE *file)
{
	int id; //layout class ID
	fread(&id, sizeof(int), 1, file);
	if (!factories[id]) {
		printf("Undefined layout ID found in file !\n");
		return 0;
	}
	GuiLayout *layout = factories[id]->create();
	layout->load(file);

	while (layout)
	{
		fread(&id, sizeof(int), 1, file);
		if (id == 0x00)
		{
			if (layout->getParent())
				layout = layout->getParent();
			else
				break;
		}
		else
		{
			if (factories[id] == 0) {
				printf("== GuiError: unregistered layout class (id=%d)!\n", id);
				return 0;
			}
			layout = layout->addLayout(factories[id]->create());
			layout->load(file);
		}
	}

	return layout;
}

bool GuiManager::isPointInRect(glm::vec2 p, glm::vec2 r1, glm::vec2 r2)
{
	if (p.x < r1.x || p.x > r1.x + r2.x || p.y < r1.y || p.y > r1.y + r2.y)
		return false;
	return true;
}

GuiLayout *GuiManager::getRootLayout()
{
	return root;
}
GuiLayout *GuiManager::getFocusLayout()
{
	return focus;
}

GuiLayout *GuiManager::addLayout(GuiLayout *layout)
{
	return root->addLayout(layout);
}
GuiLayout *GuiManager::getLayout(int i)
{
	return root->getChildren(i);
}
unsigned int GuiManager::getNumLayouts()
{
	return root->getNumChildrens();
}

void GuiManager::addTexture(std::string path)
{
	textures[path] = getRenderer()->loadTexture(path);
}
GuiTexture *GuiManager::getTexture(std::string path)
{
	if (textures[path] == 0)
		addTexture(path);

	return textures[path];
}
std::string GuiManager::getTexturePath(GuiTexture *texture)
{
	for (std::unordered_map<std::string, GuiTexture*>::iterator i = textures.begin(); i != textures.end(); i++)
	{
		if (i->second == texture)
			return i->first;
	}
	return "";
}

void GuiManager::addFont(std::string path)
{
	fonts[path] = renderer->loadFont(path);
}
GuiFont *GuiManager::getFont(std::string path)
{
	if (fonts[path] == 0)
		addFont(path);

	return fonts[path];
}
std::string GuiManager::getFontPath(GuiFont *font)
{
	for (std::unordered_map<std::string, GuiFont*>::iterator i = fonts.begin(); i != fonts.end(); i++)
	{
		if (i->second == font)
			return i->first;
	}
	return "";
}

void GuiManager::registerFactory(int chunk, GuiFactory *factory)
{
	if (factories[chunk] == 0)
		factories[chunk] = factory;
}
GuiFactory *GuiManager::getFactory(int chunk)
{
	return factories[chunk];
}

GuiLayout *GuiManager::load(std::string path)
{
	FILE *file = 0;
	GuiLayout *layout = 0;
	fopen_s(&file, path.c_str(), "rb");
	if (!file) {
		printf("Nie udalo sie otworzyc pliku \"%s\"\n", path.c_str());
		return 0;
	}

	layout = loadLayout(file);

	fclose(file);
	return layout;
}
void GuiManager::save(std::string path, GuiLayout *layout)
{
	FILE *file = 0;
	fopen_s(&file, path.c_str(), "wb");
	if (!file) {
		printf("Nie udalo sie otworzyc/utworzyc pliku \"%s\"\n", path.c_str());
		return;
	}

	saveLayout(layout, file);

	fclose(file);
}

void GuiManager::setMode(int mode)
{
	this->mode = mode;
}
void GuiManager::enableMode(int mode)
{
	this->mode |= mode;
}
void GuiManager::disableMode(int mode)
{
	this->mode &= (~mode);
}
int GuiManager::getMode()
{
	return mode;
}

void GuiManager::setRenderer(GuiRenderer *r)
{
	if (renderer)
		delete renderer;
	renderer = r;
}
GuiRenderer *GuiManager::getRenderer()
{
	return renderer;
}

void GuiManager::setEditor(GuiEditor *e)
{
	if (editor)
		delete editor;
	editor = e;
}
GuiEditor *GuiManager::getEditor()
{
	return editor;
}

void GuiManager::resize(glm::vec2 s)
{
	root->setSize(s);
}

void GuiManager::onInput()
{
	if (mode & SGUI_MODE_EDIT_MODE)
		editor->onInput();

	inputLayout(root);

	if (focus)
	{
		if (focus->isEditable() && getMode()&SGUI_MODE_EDIT_MODE)
			editor->onLayoutInput(focus, mode);
		else
			focus->onInput();
	}
}
void GuiManager::onUpdate(float dt)
{
	if (mode & SGUI_MODE_EDIT_MODE)
		editor->onUpdate(dt);

	updateLayout(root, dt);
}
void GuiManager::onDraw()
{
	if (mode & SGUI_MODE_EDIT_MODE)
		editor->onDraw();

	drawLayout(root);
}


void GuiManager::print(GuiLayout *layout, int i)
{
	for (int j = 0; j < i; j++)
		printf("  ");
	printf("0x%p ('%s')\n", layout, layout->getLabel().c_str());
	for (unsigned int j = 0; j < layout->getNumChildrens(); j++)
		print(layout->getChildren(j), i + 1);
}