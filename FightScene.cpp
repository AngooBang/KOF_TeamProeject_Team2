#include "FightScene.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "HPBar.h"
#include "Timer.h"
#include "UI.h"
#include "Map.h"
#include "Character.h"

void FightScene::Init()
{

	//hSecTimer = (HANDLE)SetTimer(g_hWnd, 1, 1000, NULL);

	// HP
	HP = new UI;
	HP->Init();

	//게임 타이머
	roundTimer = new Timer;
	roundTimer->Init();

	// 배경 이미지
	backGround = new Image;

	// 맵
	map = new Map();
	map->Init();

	// 플레이어
	player1->Init();
	player2->Init();



}

void FightScene::Update()
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

	//InvalidateRect(g_hWnd, NULL, false);
}

void FightScene::Render(HDC hdc)
{	
	backGround->Render(hdc);
	map->Render(hdc);	

	player1->Render(hdc);	
	player2->Render(hdc);

	HP->Render(hdc);
	roundTimer->Render(hdc);
}

void FightScene::Release()
{


	SAFE_RELEASE(backGround);

	SAFE_RELEASE(map);

	SAFE_RELEASE(HP);

	SAFE_RELEASE(roundTimer);

	SAFE_RELEASE(player1);
	SAFE_RELEASE(player2);

	KillTimer(g_hWnd, 1);
}
