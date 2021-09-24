#include "SceneManager.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FightScene.h"

void SceneManager::ChangeScene(E_SCENE state)
{
	SAFE_RELEASE(pScene);

	switch (state)
	{
	case E_SCENE_START:
		pScene = new StartScene();
		pScene->Init();
		return;

	case E_SCENE_SELECT:
		pScene = new SelectScene();
		pScene->Init();
		return;

	case E_SCENE_FIGHT:
		pScene = new FightScene();
		pScene->Init();
		return;

	default:
		return;

	}
}
