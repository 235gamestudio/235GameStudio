#pragma once

class Statistics
{
protected:
	float HP;
	float MP;
	float SP;
	float actualHP;
	float actualMP;
	float actualSP;
	float speed;
	float walkSpeed;
	float runSpeed;

public:
	Statistics(float _hp = 100.0f, float _mp = 100.0f, float _sp = 100.0f);

	float getHP();
	float getMP();
	float getSP();
	float getActualHP();
	float getActualMP();
	float getActualSP();
	float getSpeed();

	void setHP(float h);
	void setMP(float m);
	void setSP(float s);
	void setActualHP(float h);
	void setActualMP(float m);
	void setActualSP(float s);
	void setSpeed(float s);
};