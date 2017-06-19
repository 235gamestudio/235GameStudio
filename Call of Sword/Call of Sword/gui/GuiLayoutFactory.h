#pragma once

#include "GuiLayout.h"

class GuiLayoutFactory : public GuiFactory
{
public:
	GuiLayout *create();
	GuiLayout *copy(GuiLayout *c);
};