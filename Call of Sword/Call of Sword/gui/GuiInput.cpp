#include "GuiInput.h"

GuiInput::GuiInput()
{
	keys = SDL_GetKeyboardState(0);
	int mx, my;
	buttons = SDL_GetMouseState(&mx, &my);
	mouse = glm::vec2(mx, my);
	mouseRel = glm::vec2(0.0f);
}
GuiInput &GuiInput::get()
{
	static GuiInput instance;
	return instance;
}

void GuiInput::onEvent(SDL_Event &event)
{
	mouseRel = glm::vec2(0.0f, 0.0f);
	this->event = event;

	switch (event.type)
	{
	case SDL_KEYDOWN:
		break;

	case SDL_KEYUP:
		break;

	case SDL_MOUSEBUTTONDOWN:
		buttons = SDL_GetMouseState(0, 0);
		break;

	case SDL_MOUSEBUTTONUP:
		buttons = SDL_GetMouseState(0, 0);
		break;

	case SDL_MOUSEMOTION:
		mouse = glm::vec2(event.motion.x, event.motion.y);
		mouseRel = glm::vec2(event.motion.xrel, event.motion.yrel);
		break;
	}
}

bool GuiInput::isButton(unsigned int i)
{
	return (buttons & SDL_BUTTON(i)) ? true : false;
}
bool GuiInput::isButtonDown(unsigned int i)
{
	return (event.button.button == i && event.type == SDL_MOUSEBUTTONDOWN) ? true : false;
}
bool GuiInput::isButtonUp(unsigned int i)
{
	return (event.button.button == i && event.type == SDL_MOUSEBUTTONUP) ? true : false;
}
bool GuiInput::isAnyButtonDown()
{
	return event.type == SDL_MOUSEBUTTONDOWN ? true : false;
}
bool GuiInput::isAnyButtonUp()
{
	return event.type == SDL_MOUSEBUTTONUP ? true : false;
}
bool GuiInput::isKey(unsigned int i)
{
	return keys[i] ? true : false;
}
bool GuiInput::isKeyDown(unsigned int i)
{
	return (event.key.keysym.scancode == i && event.type == SDL_KEYDOWN) ? true : false;
}
bool GuiInput::isKeyUp(unsigned int i)
{
	return (event.key.keysym.scancode == i && event.type == SDL_KEYUP) ? true : false;
}
bool GuiInput::isAnyKeyDown()
{
	return event.type == SDL_KEYDOWN ? true : false;
}
bool GuiInput::isAnyKeyUp()
{
	return event.type == SDL_KEYUP ? true : false;
}