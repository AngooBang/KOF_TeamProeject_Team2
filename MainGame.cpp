#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Image.h"
#include "Terry.h"
#include "HPBar.h"
#include "Timer.h"
#include "Mary.h"
#include "UI.h"
#include "Map.h"



void MainGame::Init()
{
	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();

	//씬 세팅
	SceneManager::GetSingleton()->ChangeScene(E_SCENE_FIGHT);

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);



}

void MainGame::Update()
{
	SceneManager::GetSingleton()->pScene->Update();

}

void MainGame::SecUpdate()
{
}


void MainGame::Render(HDC hdc)
{
	SceneManager::GetSingleton()->pScene->Render(hdc);


}

void MainGame::Release()
{
	SceneManager::GetSingleton()->pScene->Release();
	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}

