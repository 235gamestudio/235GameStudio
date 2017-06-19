#include "GuiFileDialog.h"

GuiTreeView *GuiFileDialog::defaultTreeview = 0;
GuiButton *GuiFileDialog::defaultFileButton = 0;
GuiEditBox *GuiFileDialog::defaultEditBox = 0;

GuiFileDialog::GuiFileDialog(glm::vec2 p)
: GuiWindow(p, glm::vec2(400.0f, 300.0f))
{
	setLabel("guifiledialog");

	addLayout(treeview = new GuiTreeView(*defaultTreeview));
	addLayout(fileButton = new GuiButton(*defaultFileButton));
	addLayout(editbox = new GuiEditBox(*defaultEditBox));

	for (char c = 'A'; c <= 'Z'; c++)
	{
		char buf[8];
		sprintf_s(buf, "%c:/", c);
		path pa(buf);
		if (exists(pa))
			treeview->addNode(pa.generic_string());
	}
}

void GuiFileDialog::setTreeView(GuiTreeView *treeview)
{
	this->treeview = treeview;
}
void GuiFileDialog::setFileButton(GuiButton *fileButton)
{
	this->fileButton = fileButton;
}
void GuiFileDialog::setEditBox(GuiEditBox *editbox)
{
	this->editbox = editbox;
}
GuiTreeView *GuiFileDialog::getTreeView()
{
	return treeview;
}
GuiButton *GuiFileDialog::getFileButton()
{
	return fileButton;
}
GuiEditBox *GuiFileDialog::getEditBox()
{
	return editbox;
}

std::vector<std::string> GuiFileDialog::getPathes()
{
	std::vector<std::string> pathes;
	if (fileButton->isClicked())
	{
		for (unsigned int i = 0; i < treeview->getSelectedNodes().size(); i++)
			pathes.push_back(treeview->getSelectedNodes().at(i)->getText()->getText() + editbox->getText()->getText());

		if (pathes.empty() && !editbox->getText()->getText().empty())
			pathes.push_back(editbox->getText()->getText());
	}
	return pathes;
}

void GuiFileDialog::onUpdate(float dt)
{
	super::onUpdate(dt);

	for (unsigned int i = 0; i < treeview->getNumNodes(); i++)
		updateDirectories(treeview->getNode(i));
}

void GuiFileDialog::setDefaultTreeView(GuiTreeView *treeview)
{
	defaultTreeview = treeview;
}
void GuiFileDialog::setDefaultFileButton(GuiButton *button)
{
	defaultFileButton = button;
}
void GuiFileDialog::setDefaultEditBox(GuiEditBox *editbox)
{
	defaultEditBox = editbox;
}
GuiTreeView *GuiFileDialog::getDefaultTreeView()
{
	return defaultTreeview;
}
GuiButton *GuiFileDialog::getDefaultFileButton()
{
	return defaultFileButton;
}
GuiEditBox *GuiFileDialog::getDefaultEditBox()
{
	return defaultEditBox;
}

void GuiFileDialog::updateDirectories(GuiTreeViewNode *node)
{
	if (node->isEnabled())
	if (node->isOpen())
	{
		if (node->getNumNodes() == 0)
		{
			path p(node->getText()->getText());
			if (!exists(p))
				return;
			
			if (is_directory(p))
			for (directory_entry &e : directory_iterator(p))
				node->addNode(e.path().generic_string());
		}
		else
		{
			for (unsigned int i = 0; i < node->getNumNodes(); i++)
				updateDirectories(node->getNode(i));
		}
	}
}