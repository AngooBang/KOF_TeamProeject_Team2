#include "SceneManager.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FightScene.h"

void SceneManager::ChangeScene(E_SCENE state)
{
	switch (state)
	{
	case E_SCENE_START:
		sceneState = state;
		break;

	case E_SCENE_SELECT:
		sceneState = state;
		break;

	case E_SCENE_FIGHT:
		sceneState = state;
		break;

	};
	isChangeScene = true;
}
