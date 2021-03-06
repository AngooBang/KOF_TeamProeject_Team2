#pragma once
#include "Singleton.h"
#include "Config.h"

class StartScene;
class FightScene;
class SelectScene;
class SceneManager : public Singleton<SceneManager>
{
private:
public:
	E_SCENE sceneState = E_SCENE_START;

	bool isChangeScene = false;

	void ChangeScene(E_SCENE state);
};

