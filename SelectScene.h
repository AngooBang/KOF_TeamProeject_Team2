#pragma once
#include "GameEntity.h"

class SelectScene : GameEntity
{
public:

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

