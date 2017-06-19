#include "GuiShopDialog.h"

#include "GuiManager.h"

GuiTexture *GuiShopDialog::defaultSlotTexture = 0;

GuiShopDialog::GuiShopDialog(glm::vec2 p, glm::vec2 s) :
GuiShopDialog::GuiShopDialog(getDefaultTitleText()->getText(), p, s)
{

}
GuiShopDialog::GuiShopDialog(std::string t, glm::vec2 p, glm::vec2 s) :
GuiWindow(t, p, s),
slotTexture(defaultSlotTexture)
{
	setID(0x11);
	addLayout(buttonBuy = new GuiButton("Buy", glm::vec2(-24.0f, -27.0f), glm::vec2(81.0f, 32.0f)));
	buttonBuy->setAlign(AlignRight, AlignBottom);
	buttonBuy->setSavable(false);
}
GuiShopDialog::~GuiShopDialog()
{

}
void GuiShopDialog::onDraw()
{
	for (int y = 0; y < 7; y++)
	for (int x = 0; x < 5; x++)
		gui.getRenderer()->render(slotTexture, glm::vec2(getPosition().x + 25 + 33 * x, getPosition().y + 43 + 33 * y), glm::vec2(0.0f));

	super::onDraw();
}

void GuiShopDialog::setDefaultSlotTexture(GuiTexture *t)
{
	defaultSlotTexture = t;
}
GuiTexture *GuiShopDialog::getDefaultSlotTexture()
{
	return defaultSlotTexture;
}

GuiLayout *GuiShopDialogFactory::create()
{
	return new GuiShopDialog();
}
GuiLayout *GuiShopDialogFactory::copy(GuiLayout *c)
{
	return new GuiShopDialog(*(GuiShopDialog*)c);
}