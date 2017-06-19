#include "Statistics.h"

Statistics::Statistics(float _hp, float _mp, float _sp)
{
	HP = _hp;
	MP = _mp;
	SP = _sp;
	actualHP = HP;
	actualMP = MP;
	actualSP = SP;	
	walkSpeed = 2;
	runSpeed = walkSpeed * 3;
}

float Statistics::getHP()
{
	return HP;
}
float Statistics::getMP()
{
	return MP;
}
float Statistics::getSP()
{
	return SP;
}
float Statistics::getActualHP()
{
	return actualHP;
}
float Statistics::getActualMP()
{
	return actualMP;
}
float Statistics::getActualSP()
{
	return actualSP;
}
float Statistics::getSpeed()
{
	return speed;
}
void Statistics::setHP(float h)
{
	HP = h;
}
void Statistics::setMP(float m)
{
	MP = m;
}
void Statistics::setSP(float s)
{
	SP = s;
}
void Statistics::setActualHP(float h)
{
	actualHP = h;
}
void Statistics::setActualMP(float m)
{
	actualMP = m;
}
void Statistics::setActualSP(float s)
{
	actualSP = s;
}
void Statistics::setSpeed(float s)
{
	speed = s;
}