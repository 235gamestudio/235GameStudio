#include "GuiEditor.h"

#include "GuiManager.h"

GuiEditor::GuiEditor()
: edit(eGuiEditNone)
, mouseRel(glm::vec2(0.0f))
{

}
GuiEditor::~GuiEditor()
{

}

void GuiEditor::onInput()
{
	/* Add move per event (input.mouseRel) to move per frame (mouseRel) */
	mouseRel += input.mouseRel;
}
void GuiEditor::onUpdate(float dt)
{
	
}
void GuiEditor::onDraw()
{
	mouseRel = glm::vec2(0.0f);
}

void GuiEditor::onLayoutInput(GuiLayout *layout, int mode)
{
	/* Return if edit mode is disabled or other layout has been handled */
	if (!(mode & SGUI_MODE_EDIT_MODE))
		return;

	glm::vec2 position = layout->getAbsolutePosition();

	/* Stop editing when left mouse button is released */
	if (!input.isButton(SDL_BUTTON_LEFT))
		edit = eGuiEditNone;

	/* Clicked on layout */
	if (input.isButtonDown(SDL_BUTTON_LEFT))
	{
		/* Clicked on selected layout */
		if (layout->isSelected())
		{
			/* Mouse clicked on resize layout area */
			if (gui.isPointInRect(input.mouse, position + layout->getSize() - glm::vec2(7.0f), glm::vec2(7.0f)))
			{
				edit = eGuiEditSize;
			}
			/* Mouse clicked on layout */
			else
			{
				edit = eGuiEditPosition;
			}
		}
		/* Clicked on unselected layout */
		else
		{
			edit = eGuiEditSelection;
			layout->setSelected(true);
		}
	}
}
void GuiEditor::onLayoutUpdate(GuiLayout *layout, int mode)
{
	/* Unselect layout */
	if (!gui.isPointInRect(input.mouse, layout->getAbsolutePosition(), layout->getSize())
		|| gui.getFocusLayout() != layout)
	if (input.isButton(SDL_BUTTON_LEFT))
	if (!input.isKey(SDL_SCANCODE_LCTRL))
	if (edit == EGuiEditMode::eGuiEditNone || edit == EGuiEditMode::eGuiEditSelection)
	{
		layout->setSelected(false);
	}

	/* Edit layout */
	if (layout->isSelected())
	{
		if (edit == eGuiEditPosition)
		{
			layout->move(mouseRel);
		}
		else
		if (edit == eGuiEditSize)
		{
			layout->setSize(layout->getSize() + mouseRel);
		}
	}
}
void GuiEditor::onLayoutDraw(GuiLayout *layout, int mode)
{
	/* Render layout size */
	if (mode & SGUI_MODE_SHOW_SIZE ||
		(mode & SGUI_MODE_EDIT_MODE && layout->isEditable() && layout->isSelected()))
		GuiManager::get().getRenderer()->drawRect(layout->getAbsolutePosition(), layout->getSize(), 150, 0, 0);

	/* Render edit mode */
	if (mode & SGUI_MODE_EDIT_MODE)
	if (layout->isSelected())
	if (layout->isEditable())
	{
		glm::vec2 s(7.0f);
		GuiManager::get().getRenderer()->drawFillRect(
			layout->getAbsolutePosition() + layout->getSize()*glm::vec2(0.0f, 0.0f),
			s,
			0, 200, 0);
		GuiManager::get().getRenderer()->drawFillRect(
			layout->getAbsolutePosition() + layout->getSize()*glm::vec2(1.0f, 0.0f) - glm::vec2(s.x, 0.0f),
			s,
			0, 200, 0);
		GuiManager::get().getRenderer()->drawFillRect(
			layout->getAbsolutePosition() + layout->getSize()*glm::vec2(1.0f, 1.0f) - s,
			s,
			0, 200, 0);
		GuiManager::get().getRenderer()->drawFillRect(
			layout->getAbsolutePosition() + layout->getSize()*glm::vec2(0.0f, 1.0f) - glm::vec2(0.0f, s.y),
			s,
			0, 200, 0);
	}
}