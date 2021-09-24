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

	//�� ����
	SceneManager::GetSingleton()->ChangeScene(E_SCENE_FIGHT);

	// Ÿ�̸� ����
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
	// Ÿ�̸� ��ü ����
	KillTimer(g_hWnd, 0);
}

