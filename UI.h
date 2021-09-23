#pragma once
#include "GameObject.h"

class Image;
class HPBar;
class Timer;
class UI : public GameObject
{
private:
	HPBar* p1HP;
	HPBar* p2HP;

	Timer* roundTime;

	bool isAlive;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();


	inline bool GetIsAlive() { return this->isAlive; }
};


