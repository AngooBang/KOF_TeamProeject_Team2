#pragma once
#include "Scene.h"
class StartScene : public Scene
{

public:
	StartScene() {}
	~StartScene() {}

	void Init();
	void Update();
	void Render();
	void Release();
};

