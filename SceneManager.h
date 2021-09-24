#pragma once
#include "Singleton.h"
#include "Config.h"

class Scene;
class SceneManager : public Singleton<SceneManager>
{
public:
	Scene* pScene;

	SceneManager() {}
	~SceneManager() { }

	void ChangeScene(E_SCENE state);
};

