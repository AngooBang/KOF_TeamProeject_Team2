#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FightScene.h"
#include "Image.h"

void MainGame::Init()
{
	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();
	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);
	hSecTimer = (HANDLE)SetTimer(g_hWnd, 1, 1000, NULL);

	startScene = new StartScene;
	selectScene = new SelectScene;
	fightScene = new FightScene;

	//씬 세팅
	//SceneManager::GetSingleton()->ChangeScene(E_SCENE_START);
	//SceneManager::GetSingleton()->isChangeScene = false;
	switch (SceneManager::GetSingleton()->sceneState)
	{
	case E_SCENE_START:
		startScene->Init();
		break;
	case E_SCENE_SELECT:
		selectScene->Init();
		break;
	case E_SCENE_FIGHT:
		fightScene->Init();
		break;
	}

	//startScene->Init();
	//selectScene->Init();
	//fightScene->Init();


	selectScene->SetFightScene(fightScene);




	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);




	isSecTimer = false;
}
void MainGame::Update()
{


	if (SceneManager::GetSingleton()->isChangeScene)
	{
		switch (SceneManager::GetSingleton()->sceneState)
		{
		case E_SCENE::E_SCENE_START:
			startScene->Init();
			break;
		case E_SCENE::E_SCENE_SELECT:
			selectScene->Init();
			break;
		case E_SCENE::E_SCENE_FIGHT:
			fightScene->Init();
			break;
		}
		SceneManager::GetSingleton()->isChangeScene = false;
	}

	if (isSecTimer)
	{
		fightScene->SetIsSecTimer(true);
		isSecTimer = false;
	}

	if (!SceneManager::GetSingleton()->isChangeScene)
	{
		switch (SceneManager::GetSingleton()->sceneState)
		{
		case E_SCENE_START:
			startScene->Update();
			break;
		case E_SCENE_SELECT:
			selectScene->Update();
			break;
		case E_SCENE_FIGHT:
			fightScene->Update();
			break;
		}
	}
	InvalidateRect(g_hWnd, NULL, false);
}
void MainGame::Render(HDC hdc)
{

	HDC hBackBufferDC = backBuffer->GetMemDC();

	if (!SceneManager::GetSingleton()->isChangeScene)
	{
		switch (SceneManager::GetSingleton()->sceneState)
		{
		case E_SCENE_START:
			startScene->Render(hBackBufferDC);
			break;
		case E_SCENE_SELECT:
			selectScene->Render(hBackBufferDC);
			break;
		case E_SCENE_FIGHT:
			fightScene->Render(hBackBufferDC);
			break;
		}
	}
	backBuffer->Render(hdc);

}

void MainGame::Release()
{
	switch (SceneManager::GetSingleton()->sceneState)
	{
	case E_SCENE_START:
		startScene->Release();
		break;
	case E_SCENE_SELECT:
		selectScene->Release();
		break;
	case E_SCENE_FIGHT:
		fightScene->Release();
		break;
	}
	
	
	SAFE_RELEASE(startScene);
	SAFE_RELEASE(selectScene);
	SAFE_RELEASE(fightScene);

	SAFE_RELEASE(backBuffer);

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
	KillTimer(g_hWnd, 1);
}

