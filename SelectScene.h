#pragma once
#include "GameEntity.h"

class Image;
class SelectIcon;
class SelectScene : public GameEntity
{
private:
	Image* selectBackground;

	Image* selectChar1;
	Image* selectChar2;


	Image* selectCharframe;

	SelectIcon* iconP1;
	SelectIcon* iconP2;

	int elapsedtCount;


	int selectCharFramePos;



public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

