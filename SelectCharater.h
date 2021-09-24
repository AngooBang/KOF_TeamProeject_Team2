#pragma once
#include "Config.h"
#include "image.h"
#include "KeyManager.h"

class SelectCharater
{
private:
	Image* SelectPlayer1;
	Image* SelectIconP;
	Image* SelectCharframe;

	Image* SelectPlayer2;

	int selectCharFrameX;
	int	selectCharFrameY;

	POINT SelectCharPos[2];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

