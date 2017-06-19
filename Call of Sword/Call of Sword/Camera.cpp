#include "Camera.h"

Camera::Camera(float _posX, float _posY, int _width, int _height)
{
	cameraRect.x = _posX;
	cameraRect.y = _posY;
	cameraRect.w = _width;
	cameraRect.h = _height;
}

void Camera::addBorder(float posX, float posY, int width, int height)
{
	borderPosX = posX;
	borderPosY = posY;
	borderWidth = width;
	borderHeight = height;
}

float Camera::getPosX()
{
	return cameraRect.x;
}

void Camera::setPosX(float x)
{
	cameraRect.x = x;
}

float Camera::getPosY()
{
	return cameraRect.y;
}

void Camera::setPosY(float y)
{
	cameraRect.y = y;
}

int Camera::getWidth()
{
	return cameraRect.w;
}

void Camera::setWidth(int w)
{
	cameraRect.w = w;
}

int Camera::getHeight()
{
	return cameraRect.h;
}

void Camera::setHeight(int h)
{
	cameraRect.h = h;
}

float Camera::getBorderPosX()
{
	return borderPosX;
}

void Camera::setBorderPosX(float x)
{
	borderPosX = x;
}

float Camera::getBorderPosY()
{
	return borderPosY;
}

void Camera::setBorderPosY(float y)
{
	borderPosY = y;
}

float Camera::getBorderWidth()
{
	return borderWidth;
}

void Camera::setBorderWidth(int w)
{
	borderWidth = w;
}

float Camera::getBorderHeight()
{
	return borderHeight;
}

void Camera::setBorderHeight(int h)
{
	borderHeight = h;
}

SDL_Rect Camera::getRect()
{
	return cameraRect;
}
