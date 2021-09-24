#pragma once
#include "Config.h"
class Scene
{
public:
	Scene() {}
	~Scene() {}

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

