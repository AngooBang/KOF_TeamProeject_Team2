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
	//SceneManager::GetSingleton()->ChangeScene(E_SCENE_FIGHT);

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);



	//게임 타이머
	roundTimer = new Timer;
	roundTimer->Init();

	// 배경 이미지
	backGround = new Image;
	if (!SUCCEEDED(backGround->Init("Image/mapImage.bmp", 1400, 933)))
	{
		cout << "Image/bin.bmp 파일 로드에 실패했다." << endl;
	}

	map = new Map;
	map->Init();


	terry = new Terry;
	terry->Init();
	mary = new Mary;
	mary->Init();	

	terry->ammo->SetTarget(mary);
	mary->ammo->SetTarget(terry);

void MainGame::Update()
{
	//SceneManager::GetSingleton()->pScene->Update();

	terry->Update();
	mary->Update();
	HP->Update();

	map->Update();

	if (isSecTimer)
	{
		if (HP->GetIsAlive() == true)
		{
			roundTimer->Update();
		}
		isSecTimer = false;
	}


void MainGame::Render(HDC hdc)
{
	//SceneManager::GetSingleton()->pScene->Render();

	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	map->Render(hBackBufferDC);

	terry->Render(hBackBufferDC);
	mary->Render(hBackBufferDC);

	HP->Render(hBackBufferDC);
	roundTimer->Render(hBackBufferDC);

	backBuffer->Render(hdc);

}

void MainGame::Release()
{
	//SceneManager::GetSingleton()->pScene->Release();
	SAFE_RELEASE(backBuffer);

	SAFE_RELEASE(backGround);

	SAFE_RELEASE(map);

	SAFE_RELEASE(HP);

	SAFE_RELEASE(roundTimer);

	SAFE_RELEASE(terry);

	SAFE_RELEASE(mary);
	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}

