#pragma once
#include "Scene.h"
class FightScene :
    public Scene
{
public:

	void Init();
	void Update();
	void Render();
	void Release();
};

