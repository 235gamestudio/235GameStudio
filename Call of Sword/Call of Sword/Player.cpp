#include "Player.h"

Player::Player(std::string path, float _posX, float _posY, int _sizeW, int _sizeH, SDL_Renderer *_renderer)
	: NPC::NPC(path, _posX, _posY, _sizeW, _sizeH, _renderer),
		Statistics::Statistics()
{
	SDL_Surface *animSpeedSurface = IMG_Load(path.c_str());

	if (animSpeedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}

	else
	{
		texture = SDL_CreateTextureFromSurface(_renderer, animSpeedSurface);

		posX = _posX;
		posY = _posY;
		sizeW = _sizeW;
		sizeH = _sizeH;

		walkingAnim.x = 0;
		walkingAnim.y = 0;
		walkingAnim.w = _sizeW;
		walkingAnim.h = _sizeH;

		render.x = (int)_posX - (_sizeW / 2);
		render.y = (int)_posY - (_sizeH / 2);
		render.w = _sizeW;
		render.h = _sizeH;

		playerRect.x = posX;
		playerRect.y = posY;
		playerRect.w = sizeW;
		playerRect.h = sizeH;

		speed = 2;
		runningAnimSpeed = 5;
		walkingAnimSpeed = 8;

		animSpeed = walkingAnimSpeed;

		moveDirection = e_begin;
		playerState = e_idle;

		SDL_FreeSurface(animSpeedSurface);
	}
}

Player::~Player()
{
}
int Player::getAnimSpeed()
{
	return animSpeed;
}
void Player::setAnimSpeed(int aSpeed)
{
	animSpeed = aSpeed;
}
void Player::move(SDL_Event *kEvent, int key)
{
	const Uint8 *CurrentKeyState = SDL_GetKeyboardState(NULL);

	setSpeed(walkSpeed);

	//printf("%d\n", animSpeed);

	if (!CurrentKeyState[SDL_SCANCODE_LSHIFT])
	{
		//printf("walking\n");

		if (playerState == e_running)
			animSpeed = 0;

		playerState = e_walking;
		if (CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_DOWN])
		{
			walkingAnim.y = walkingAnim.h * 4;
			moveDirection = e_southwest;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 4)
				walkingAnim.x = 0;

			setPosX(getPosX() - getSpeed());
			setPosY(getPosY() + getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
			
			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_DOWN]) && moveDirection == e_southwest)
		{
			walkingAnim.y = walkingAnim.h * 4;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_RIGHT] && CurrentKeyState[SDL_SCANCODE_DOWN])
		{
			walkingAnim.y = walkingAnim.h * 6;
			moveDirection = e_southeast;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 6)
				walkingAnim.x = 0;

			setPosX(getPosX() + getSpeed());
			setPosY(getPosY() + getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_RIGHT] && CurrentKeyState[SDL_SCANCODE_DOWN]) && moveDirection == e_southeast)
		{
			walkingAnim.y = walkingAnim.h * 6;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_UP])
		{
			walkingAnim.y = walkingAnim.h * 5;
			moveDirection = e_northwest;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 5)
				walkingAnim.x = 0;

			setPosX(getPosX() - getSpeed());
			setPosY(getPosY() - getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_UP]) && moveDirection == e_northwest)
		{
			walkingAnim.y = walkingAnim.h * 5;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_RIGHT] && CurrentKeyState[SDL_SCANCODE_UP])
		{
			walkingAnim.y = walkingAnim.h * 7;
			moveDirection = e_northeast;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 7)
				walkingAnim.x = 0;

			setPosX(getPosX() + getSpeed());
			setPosY(getPosY() - getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_UP]) && moveDirection == e_northeast)
		{
			walkingAnim.y = walkingAnim.h * 7;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_LEFT])
		{
			walkingAnim.y = walkingAnim.h;
			moveDirection = e_west;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h)
				walkingAnim.x = 0;

			setPosX(getPosX() - getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_LEFT] && moveDirection == e_west)
		{
			walkingAnim.y = walkingAnim.h;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_RIGHT])
		{
			walkingAnim.y = walkingAnim.h * 2;
			moveDirection = e_east;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 2)
				walkingAnim.x = 0;

			setPosX(getPosX() + getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_RIGHT] && moveDirection == e_east)
		{
			walkingAnim.y = walkingAnim.h * 2;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_UP])
		{
			walkingAnim.y = walkingAnim.h * 3;
			moveDirection = e_north;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 3)
				walkingAnim.x = 0;

			setPosY(getPosY() - getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_UP] && moveDirection == e_north)
		{
			walkingAnim.y = walkingAnim.h * 3;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_DOWN])
		{
			walkingAnim.y = 0;
			moveDirection = e_south;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == 0)
				walkingAnim.x = 0;

			setPosY(getPosY() + getSpeed());
			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_DOWN] && moveDirection == e_south)
		{
			walkingAnim.y = 0;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}
	}
	else if (CurrentKeyState[SDL_SCANCODE_LSHIFT])
	{
		setSpeed(runSpeed);

		if (playerState == e_walking)
			animSpeed = 0;

		printf("running\n");
		playerState = e_running;

		if (CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_DOWN])
		{
			walkingAnim.y = walkingAnim.h * 12;
			moveDirection = e_southwest;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 12)
				walkingAnim.x = 0;

			setPosX(getPosX() - getSpeed());
			setPosY(getPosY() + getSpeed());

			if (animSpeed == runningAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_DOWN]) && moveDirection == e_southwest)
		{
			walkingAnim.y = walkingAnim.h * 4;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_RIGHT] && CurrentKeyState[SDL_SCANCODE_DOWN])
		{
			walkingAnim.y = walkingAnim.h * 14;
			moveDirection = e_southeast;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 14)
				walkingAnim.x = 0;

			setPosX(getPosX() + getSpeed());
			setPosY(getPosY() + getSpeed());

			if (animSpeed == runningAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_RIGHT] && CurrentKeyState[SDL_SCANCODE_DOWN]) && moveDirection == e_southeast)
		{
			walkingAnim.y = walkingAnim.h * 6;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_UP])
		{
			walkingAnim.y = walkingAnim.h * 13;
			moveDirection = e_northwest;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 13)
				walkingAnim.x = 0;

			setPosX(getPosX() - getSpeed());
			setPosY(getPosY() - getSpeed());

			if (animSpeed == runningAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_UP]) && moveDirection == e_northwest)
		{
			walkingAnim.y = walkingAnim.h * 5;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_RIGHT] && CurrentKeyState[SDL_SCANCODE_UP])
		{
			walkingAnim.y = walkingAnim.h * 15;
			moveDirection = e_northeast;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 15)
				walkingAnim.x = 0;

			setPosX(getPosX() + getSpeed());
			setPosY(getPosY() - getSpeed());

			if (animSpeed == runningAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!(CurrentKeyState[SDL_SCANCODE_LEFT] && CurrentKeyState[SDL_SCANCODE_UP]) && moveDirection == e_northeast)
		{
			walkingAnim.y = walkingAnim.h * 7;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_LEFT])
		{
			walkingAnim.y = walkingAnim.h * 9;
			moveDirection = e_west;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 9)
				walkingAnim.x = 0;

			setPosX(getPosX() - getSpeed());

			if (animSpeed == runningAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_LEFT] && moveDirection == e_west)
		{
			walkingAnim.y = walkingAnim.h;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_RIGHT])
		{
			walkingAnim.y = walkingAnim.h * 10;
			moveDirection = e_east;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 10)
				walkingAnim.x = 0;

			setPosX(getPosX() + getSpeed());

			if (animSpeed == runningAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_RIGHT] && moveDirection == e_east)
		{
			walkingAnim.y = walkingAnim.h * 2;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_UP])
		{
			walkingAnim.y = walkingAnim.h * 11;
			moveDirection = e_north;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 11)
				walkingAnim.x = 0;

			setPosY(getPosY() - getSpeed());

			if (animSpeed == walkingAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_UP] && moveDirection == e_north)
		{
			walkingAnim.y = walkingAnim.h * 3;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}

		if (CurrentKeyState[SDL_SCANCODE_DOWN])
		{
			walkingAnim.y = walkingAnim.h * 8;
			moveDirection = e_south;

			if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 8)
				walkingAnim.x = 0;

			setPosY(getPosY() + getSpeed());

			if (animSpeed == runningAnimSpeed)
			{
				walkingAnim.x += walkingAnim.w;
				animSpeed = 0;
			}
			animSpeed++;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;

			playerRect.x = posX;
			playerRect.y = posY;

			return;
		}

		else if (!CurrentKeyState[SDL_SCANCODE_DOWN] && moveDirection == e_south)
		{
			walkingAnim.y = 0;
			walkingAnim.x = 0;
			render.x = getPosX() - getSizeW() / 2;
			render.y = getPosY() - getSizeH() / 2;
		}
	}
}
void Player::mouseEvent(int clicks, int cameraPosX, int cameraPosY)
{
	if (mouseOrder == false)
	{
		int mousePosX, mousePosY;
		float vectorX, vectorY, vectorLenght;
		float _normVectorX, _normVectorY;

		SDL_GetMouseState(&mousePosX, &mousePosY);

		mousePosX += cameraPosX;
		mousePosY += cameraPosY;

		vectorX = mousePosX - posX;
		vectorY = mousePosY - posY;

		vectorLenght = sqrt(pow(vectorX, 2) + pow(vectorY, 2));

		_normVectorX = vectorX / vectorLenght;
		_normVectorY = vectorY / vectorLenght;

		normVectorX = _normVectorX;
		normVectorY = _normVectorY;
		mouseOrderX = mousePosX;
		mouseOrderY = mousePosY;
		mouseOrder = true;
		mouseClicks = clicks;
		if (mouseClicks == 1)
			speed = 2;
		else
			speed = 6;
	}

	if (mouseClicks == 1)
	{
		if (playerState == e_running)
			animSpeed = 0;

		playerState = e_walking;

		if (abs(normVectorY) < 0.45)
		{
			if (normVectorX > 0)
			{
					walkingAnim.y = walkingAnim.h * 2;
					moveDirection = e_east;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 2)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
		else if (abs(normVectorX) < 0.45)
		{
			if (normVectorY > 0)
			{
					walkingAnim.y = 0;
					moveDirection = e_east;


					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == 0)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h * 3;
					moveDirection = e_west;


					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 3)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
		else if (normVectorY <= -0.45)
		{
			if (normVectorX >= 0.45)
			{
					walkingAnim.y = walkingAnim.h * 7;
					moveDirection = e_west;


					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 7)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h * 5;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 5)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
		else if (normVectorY >= 0.45)
		{
			if (normVectorX >= 0.45)
			{
					walkingAnim.y = walkingAnim.h * 6;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 6)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h * 4;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 4)
						walkingAnim.x = 0;

					if (animSpeed == walkingAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
	}
	else
	{
		if (playerState == e_walking)
			animSpeed = 0;

		playerState = e_running;

		if (abs(normVectorY) < 0.45)
		{
			if (normVectorX > 0)
			{
					walkingAnim.y = walkingAnim.h * 10;
					moveDirection = e_east;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 10)
						walkingAnim.x = 0;

					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h * 9;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 9)
						walkingAnim.x = 0;

					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
		else if (abs(normVectorX) < 0.45)
		{
			if (normVectorY > 0)
			{
					walkingAnim.y = walkingAnim.h * 8;
					moveDirection = e_east;


					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 8)
						walkingAnim.x = 0;

					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h * 11;
					moveDirection = e_west;


					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 11)
						walkingAnim.x = 0;
					
					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
		else if (normVectorY <= -0.45)
		{
			if (normVectorX >= 0.45)
			{
					walkingAnim.y = walkingAnim.h * 15;
					moveDirection = e_west;


					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 15)
						walkingAnim.x = 0;

					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h * 13;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 13)
						walkingAnim.x = 0;

					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
		else if (normVectorY >= 0.45)
		{
			if (normVectorX >= 0.45)
			{
					walkingAnim.y = walkingAnim.h * 14;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 14)
						walkingAnim.x = 0;

					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
			else
			{
					walkingAnim.y = walkingAnim.h * 12;
					moveDirection = e_west;

					if (walkingAnim.x == walkingAnim.w * 7 && walkingAnim.y == walkingAnim.h * 12)
						walkingAnim.x = 0;

					if (animSpeed == runningAnimSpeed)
					{
						walkingAnim.x += walkingAnim.w;
						animSpeed = 0;
					}
					animSpeed++;
			}
		}
	}

	posX += speed * normVectorX;
	posY += speed * normVectorY;


	if (abs(posX - (float)mouseOrderX) < 5 && abs(posY - (float)mouseOrderY) < 5)
		mouseOrder = false;
}


bool Player::getMouseOrder()
{
	return mouseOrder;
}
void Player::setMouseOrder(bool state)
{
	mouseOrder = state;
}
int Player::getMouseClicks()
{
	return mouseClicks;
}
void Player::setMouseClicks(int clicks)
{
	mouseClicks = clicks;
}
float Player::getRenderHP()
{
	return renderHP;
}
float Player::getRenderMP()
{
	return renderMP;
}
void Player::setRenderHP(float h)
{
	renderHP = h;
}
void Player::setRenderMP(float m)
{
	renderMP = m;
}
