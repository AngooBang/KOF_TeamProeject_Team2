#include "SceneManager.h"
#include "TFactory.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FightScene.h"

void SceneManager::ChangeScene(E_SCENE state)
{
	SAFE_RELEASE(pScene);

	switch (state)
	{
	case E_SCENE_START:
		pScene = TFactory<StartScene>::Create();
		return;

	case E_SCENE_SELECT:
		pScene = TFactory<SelectScene>::Create();
		return;

	case E_SCENE_FIGHT:
		pScene = TFactory<FightScene>::Create();
		return;

	default:
		return;

	}
}
