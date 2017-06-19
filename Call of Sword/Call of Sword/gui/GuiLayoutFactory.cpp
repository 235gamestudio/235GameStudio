#include "GuiLayoutFactory.h"

GuiLayout *GuiLayoutFactory::create()
{
	return new GuiLayout();
}
GuiLayout *GuiLayoutFactory::copy(GuiLayout *c)
{
	return new GuiLayout(*c);
}