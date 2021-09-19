#pragma once
#include "Character.h"

class Terry : public Character
{
private:
	Image* img;
	int frameX, frameY;
	int elapsedCount;
	bool isAlive;
	int walkFrameX[10];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

