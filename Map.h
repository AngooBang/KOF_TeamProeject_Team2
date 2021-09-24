#pragma once
#include "GameObject.h"

class Image;
class Map
{
private:
	Image* TownStage;

	int mapFrameX, mapFrameY;
	int elapsedCount;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

};

