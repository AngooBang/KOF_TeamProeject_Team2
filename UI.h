#pragma once
#include "GameObject.h"

class Image;
class HPBar;
class Timer;
class UI : public GameObject
{
protected:

	Timer* roundTime;

	bool isAlive;

public:

	HPBar* p1Hp;
	HPBar* p2Hp;
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline bool GetIsAlive() { return this->isAlive; }
};


