#pragma once
#include "GameEntity.h"

class SelectScene : public GameEntity
{
public:

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

