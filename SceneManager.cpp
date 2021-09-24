#include "SceneManager.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FightScene.h"

Scene* SceneManager::ChangeScene(E_SCENE state)
{
	SAFE_RELEASE(pScene);

	switch (state)
	{
	case E_SCENE_START:
		pScene = new StartScene();
		pScene->Init();
		return pScene;

	case E_SCENE_SELECT:
		pScene = new SelectScene();
		pScene->Init();
		return pScene;

	case E_SCENE_FIGHT:
		pScene = new FightScene();
		pScene->Init();
		return pScene;

	default:
		return pScene;

	}
}
