#pragma once
#include "GameObject.h"

class Image;
class HPBar;
class Timer;
class UI : public GameObject
{
private:

	Timer* roundTime;

	bool isAlive;

public:

	HPBar* p1HP;
	HPBar* p2HP;
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();


	inline bool GetIsAlive() { return this->isAlive; }
};


