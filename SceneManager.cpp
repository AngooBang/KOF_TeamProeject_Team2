#include "SceneManager.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FightScene.h"

void SceneManager::ChangeScene(E_SCENE state)
{

	switch (state)
	{
	case E_SCENE_START:
		sceneState = E_SCENE_START;
		return;

	case E_SCENE_SELECT:
		sceneState = E_SCENE_SELECT;
		return;

	case E_SCENE_FIGHT:
		sceneState = E_SCENE_FIGHT;
		return;

	default:
		return;

	};
}
