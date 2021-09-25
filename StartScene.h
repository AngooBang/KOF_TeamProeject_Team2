#pragma once
#include "GameEntity.h"

class StartScene : GameEntity
{

public:
	StartScene() {}
	~StartScene() {}

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

