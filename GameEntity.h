#pragma once
#include <Windows.h>
#include "Config.h"

class GameEntity
{
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

