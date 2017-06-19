#pragma once
#pragma comment (lib, "SDL2")
#include <SDL.h>

class Camera
{
public:
	SDL_Rect cameraRect;

	float borderPosX;
	float borderPosY;
	int borderWidth;
	int borderHeight;

	Camera(float _posX, float _posY, int _width, int _height);

	void addBorder(float posX, float posY, int width, int height);

	SDL_Rect getRect();

	float getPosX();
	float getPosY();
	int getWidth();
	int getHeight();
	void setPosX(float x);
	void setPosY(float y);
	void setWidth(int w);
	void setHeight(int h);

	float getBorderPosX();
	float getBorderPosY();
	float getBorderWidth();
	float getBorderHeight();

	void setBorderPosX(float x);
	void setBorderPosY(float y);
	void setBorderWidth(int w);
	void setBorderHeight(int h);

};