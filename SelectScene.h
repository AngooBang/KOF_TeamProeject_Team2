#pragma once
#include "Scene.h"
class SelectScene :
    public Scene
{
public:

	void Init();
	void Update();
	void Render();
	void Release();
};

