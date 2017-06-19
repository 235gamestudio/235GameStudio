#pragma once

#define super __super

#define gui GuiManager::get()
#define input GuiInput::get()

/**
 * \mainpage
 * GUI library. Work in progress.\n
 */

/**
 * \page own_layout Create your own layout

 * Tutorial how to create your own GUI component.

 * \section own_layout_guilayout GuiLayout overview
 * GuiLayout is a base class for each GUI component.\n
 * The common thing to create your own GUI component is to override GuiLayout methods: onInput(SDL_Event), onUpdate(float),
 * onDraw().\n
 * GuiManager calls those methods in right order that you dont need to worry about sorting or checking if another layout is at
 * foreground.\n

 * \subsection own_layout_oninput onInput(SDL_Event e)
 * onInput method is called every time when there is any SDL event to handle. It is called before onInput and only if
 * event is a SDL_BUTTON_DOWN or SDL_BUTTON_UP event and mouse is on the layout. For example if onInput is called with mouse button down event,
 * you know that user has clicked on your layout.\n
 * e - SDL event to handle.

 * \subsection own_layout_onupdate onUpdate(float dt)
 * onUpdate method is called every frame.\n
 * dt - duration of last frame in seconds (delta time).

 * \subsection own_layout_ondraw onDraw()
 * onDraw method is called every frame after onUpdate method. Layouts are rendered from last to first, where "first" is at foreground.
 */