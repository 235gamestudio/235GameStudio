#pragma once
#include "NPC.h"
#include "Statistics.h"

enum E_MoveDirection
{
	e_north,
	e_east,
	e_south,
	e_west,
	e_northeast,
	e_southeast,
	e_northwest,
	e_southwest,
	e_begin
};

enum E_PlayerState
{
	e_idle,
	e_walking,
	e_running
};

class Player : public NPC, public Statistics
{
private:
	int animSpeed;
	int runningAnimSpeed;
	int walkingAnimSpeed;

	bool mouseOrder = false;
	int mouseOrderX;
	int mouseOrderY;
	float normVectorX;
	float normVectorY;
	int mouseClicks;
	float renderHP;
	float renderMP;

public:

	E_MoveDirection moveDirection;
	E_PlayerState playerState;

	Player(std::string pathAnim, float _posX, float _posY, int _sizeW, int _sizeH, SDL_Renderer *_renderer);
	~Player();

	int getAnimSpeed();
	void setAnimSpeed(int s);

	bool getMouseOrder();												
	void setMouseOrder(bool state);

	int getMouseClicks();
	void setMouseClicks(int clicks);

	void move(SDL_Event *kEvent, int key);								// player keyboard movement function
	void mouseEvent(int clicks, int cameraPosX, int cameraPosY);		// player mouse movement function

	float getRenderHP();
	float getRenderMP();
	void setRenderHP(float h);
	void setRenderMP(float m);
};