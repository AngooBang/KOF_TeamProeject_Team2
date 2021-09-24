#pragma once
#include "Singleton.h"
#include "Config.h"

class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
public:

	Scene* pScene;
	SceneManager() {}
	~SceneManager() { }

	Scene* ChangeScene(E_SCENE state);
};

