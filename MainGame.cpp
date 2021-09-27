#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FightScene.h"
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
	SceneManager::GetSingleton()->ChangeScene(E_SCENE_START);
	playScene = SceneManager::GetSingleton()->sceneState;

	startScene = new StartScene();
	selectScene = new SelectScene();
	fightScene = new FightScene();

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);


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

}
void MainGame::Update()
{

	
	player1->Update();

	if (player2->GetIsHit())
	{
		switch (player2->GetHitMotion())
		{
		case HitMotion::Small:
			HP->p2Hp->DamageToHp(SMALL_ATTACK_DAMAGE);
			break;
		case HitMotion::Big:
			HP->p2Hp->DamageToHp(BIG_ATTACK_DAMAGE);
			break;
		}
	}

	player2->Update(); 
	if (player1->GetIsHit()) // 1p가 맞음
	{
		switch (player1->GetHitMotion())
		{
		case HitMotion::Small:
			HP->p1Hp->DamageToHp(SMALL_ATTACK_DAMAGE);
			break;
		case HitMotion::Big:
			HP->p1Hp->DamageToHp(BIG_ATTACK_DAMAGE);
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
	if (playScene != SceneManager::GetSingleton()->sceneState)
	{
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
		playScene = SceneManager::GetSingleton()->sceneState;
	}
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
void MainGame::Render(HDC hdc)
{

	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	map->Render(hBackBufferDC);

	
	player1->Render(hBackBufferDC);
	
	player2->Render(hBackBufferDC);


	HP->Render(hBackBufferDC);
	roundTimer->Render(hBackBufferDC);
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

	intro->Render(hBackBufferDC);

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

	SAFE_RELEASE(player1);
	SAFE_RELEASE(backBuffer);

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}

