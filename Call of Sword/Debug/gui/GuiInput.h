#pragma once

#include <glm.hpp>
#include <SDL.h>

class GuiInput
{
private:
	GuiInput();
	GuiInput(GuiInput &);
	GuiInput &operator=(GuiInput &);

public:
	static GuiInput &get();

	void onEvent(SDL_Event &event);

	bool isButton(unsigned int i);
	bool isButtonDown(unsigned int i);
	bool isButtonUp(unsigned int i);
	bool isAnyButtonDown();
	bool isAnyButtonUp();
	bool isKey(unsigned int i);
	bool isKeyDown(unsigned int i);
	bool isKeyUp(unsigned int i);
	bool isAnyKeyDown();
	bool isAnyKeyUp();

	SDL_Event event;

	const Uint8 *keys;
	Uint32 buttons;
	glm::vec2 mouse, mouseRel;
};