#pragma once

#include <filesystem.hpp>

#include "GuiWindow.h"
#include "GuiEditBox.h"
#include "GuiTreeView.h"

using namespace boost::filesystem;

class GuiFileDialog : public GuiWindow
{
	GuiTreeView *treeview;
	GuiButton *fileButton;
	GuiEditBox *editbox;

	static GuiTreeView *defaultTreeview;
	static GuiButton *defaultFileButton;
	static GuiEditBox *defaultEditBox;

	void updateDirectories(GuiTreeViewNode *node);

public:
	GuiFileDialog(glm::vec2 p = glm::vec2(0.0f)/*, glm::vec2 s = glm::vec2(0.0f)*/);

	virtual void setTreeView(GuiTreeView *treeview);
	virtual void setFileButton(GuiButton *fileButton);
	virtual void setEditBox(GuiEditBox *editbox);
	virtual GuiTreeView *getTreeView();
	virtual GuiButton *getFileButton();
	virtual GuiEditBox *getEditBox();

	virtual std::vector<std::string> getPathes();

	virtual void onUpdate(float dt);

	static void setDefaultTreeView(GuiTreeView *treeview);
	static void setDefaultFileButton(GuiButton *button);
	static void setDefaultEditBox(GuiEditBox *editbox);
	static GuiTreeView *getDefaultTreeView();
	static GuiButton *getDefaultFileButton();
	static GuiEditBox *getDefaultEditBox();
};