#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Image.h"
#include "HPBar.h"
#include "Timer.h"
#include "Character.h"
#include "HitBox.h"
#include "UI.h"
#include "Map.h"
#include "Intro.h"

void MainGame::Init()
{
	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();

	//씬 세팅
	//SceneManager::GetSingleton()->ChangeScene(E_SCENE_FIGHT);

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);
	hSecTimer = (HANDLE)SetTimer(g_hWnd, 1, 1000, NULL);

	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	//Intro
	intro = new Intro;
	intro->Init();

	// HP
	HP = new UI;
	HP->Init();
	
	//게임 타이머
	roundTimer = new Timer;
	roundTimer->Init();

	// 배경 이미지
	backGround = new Image;
	if (!SUCCEEDED(backGround->Init("Image/mapImage.bmp", 1400, 933)))
	{
		cout << "Image/bin.bmp 파일 로드에 실패했다." << endl;
	}

	player1 = new Character();
	player2 = new Character();

	player1->SetPlayerNum(1);
	player2->SetPlayerNum(2);
	player1->SetCharacterType(CharacterType::Mary);
	player2->SetCharacterType(CharacterType::Terry);
	player1->Init();
	player2->Init();

	player2->hitBox->SetTarget(player1);
	player1->hitBox->SetTarget(player2);


	map = new Map;
	map->Init();



	//terry->ammo->SetTarget(mary);
	//mary->ammo->SetTarget(terry);

}

void MainGame::Update()
{

	
	player1->Update();

	if (player2->GetIsHit())
	{
		switch (player2->GetHitMotion())
		{
		case HitMotion::Small:
			HP->p2HP->DamageToHp(SMALL_ATTACK_DAMAGE);
			break;
		case HitMotion::Big:
			HP->p2HP->DamageToHp(BIG_ATTACK_DAMAGE);
			break;
		}
	}

	player2->Update(); 
	if (player1->GetIsHit()) // 1p가 맞음
	{
		switch (player1->GetHitMotion())
		{
		case HitMotion::Small:
			HP->p1HP->DamageToHp(SMALL_ATTACK_DAMAGE);
			break;
		case HitMotion::Big:
			HP->p1HP->DamageToHp(BIG_ATTACK_DAMAGE);
			break;
		}
	}

	//SceneManager::GetSingleton()->pScene->Update();

	intro->Update();
	
	HP->Update();

	/*if (player1->GetIsHit()==true)
	{
		player1->Update();
	}
	if(player2->GetIsHit()==true)
	{
		player2->Update();
	}*/


	map->Update();

	if (isSecTimer)
	{
		if (HP->GetIsAlive() == true)
		{
			roundTimer->Update();
		}
		isSecTimer = false;
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	//SceneManager::GetSingleton()->pScene->Render();

	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	map->Render(hBackBufferDC);

	
	player1->Render(hBackBufferDC);
	
	player2->Render(hBackBufferDC);


	HP->Render(hBackBufferDC);
	roundTimer->Render(hBackBufferDC);

	intro->Render(hBackBufferDC);

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

	SAFE_RELEASE(player1);

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
	KillTimer(g_hWnd, 1);
}

//
//LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMessage)
//	{
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case VK_SPACE:
//
//			break;
//		case VK_UP:
//
//			break;
//		case VK_DOWN:
//
//			break;
//		case VK_LEFT:
//
//			break;
//		case VK_RIGHT:
//
//			break;
//		}
//		break;
//	}
//	return DefWindowProc(hWnd, iMessage, wParam, lParam);
//}
