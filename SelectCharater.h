#pragma once
#include "Config.h"
#include "image.h"
#include "KeyManager.h"
#include <conio.h>

class SelectCharater
{
private:
	Image* SelectBackground;

	Image* SelectChar;

	Image* SelectIconP;
	Image* SelectIconP2;

	Image* SelectCharframe;

	int pressKey;

	int elapsedtCount;

	int selectCharFrameNum1;
	int selectCharFrameNum2;
	int selectCharFrameX;
	int selectCharFrameX2;

	int selectCharFramePos;

	bool moveIcon1;
	bool moveIcon2;

	POINT SelectCharPos[2];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

