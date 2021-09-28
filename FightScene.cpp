#include "FightScene.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "HPBar.h"
#include "Timer.h"
#include "HPBar.h"
#include "Map.h"
#include "Character.h"
#include "HitBox.h"

void FightScene::Init()
{

	// HP
	p1Hp = new HPBar;
	p1Hp->SetPlayerNum(1);
	p1Hp->SetCharacterType(p1CharacterType);
	p1Hp->Init();

	p2Hp = new HPBar;
	p2Hp->SetPlayerNum(2);
	p2Hp->SetCharacterType(p2CharacterType);
	p2Hp->Init();


	//게임 타이머
	roundTimer = new Timer;
	roundTimer->Init();

	// 배경 이미지
	backGround = new Image;
	backGround->Init("Image/mapImage.bmp", 1400, 933); 


	// 맵
	map = new Map();
	map->Init();

	// 플레이어
	player1 = new Character();
	player2 = new Character();

	player1->SetPlayerNum(1);
	player2->SetPlayerNum(2);
	player1->SetCharacterType(p1CharacterType);
	player2->SetCharacterType(p2CharacterType);
	player1->Init();
	player2->Init();

	player2->hitBox->SetTarget(player1);
	player1->hitBox->SetTarget(player2);

	isSecTimer = false;
	

}

void FightScene::Update()
{


	player1->Update();
	if (player2->GetIsHit())
	{
		switch (player2->GetHitMotion())
		{
		case HitMotion::Small:
			p2Hp->DamageToHp(SMALL_ATTACK_DAMAGE);
			break;
		case HitMotion::Big:
			p2Hp->DamageToHp(BIG_ATTACK_DAMAGE);
			break;
		}
	}

	player2->Update();
	if (player1->GetIsHit()) // 1p가 맞음
	{
		switch (player1->GetHitMotion())
		{
		case HitMotion::Small:
			p1Hp->DamageToHp(SMALL_ATTACK_DAMAGE);
			break;
		case HitMotion::Big:
			p1Hp->DamageToHp(BIG_ATTACK_DAMAGE);
			break;
		}
	}
	
	map->Update();

	
	if (p1Hp->GetIsAlive() && p2Hp->GetIsAlive())
	{
		p1Hp->Update();
		p2Hp->Update();
		if (isSecTimer)
		{
			roundTimer->Update();
			isSecTimer = false;
		}
	}

	//InvalidateRect(g_hWnd, NULL, false);
}

void FightScene::Render(HDC hdc)
{	
	backGround->Render(hdc);
	map->Render(hdc);	

	player1->Render(hdc);	
	player2->Render(hdc);

	p1Hp->Render(hdc);
	p2Hp->Render(hdc);
	player1->hitBox->Render(hdc);
	player2->hitBox->Render(hdc);

	roundTimer->Render(hdc);
}

void FightScene::Release()
{

	SAFE_RELEASE(p1Hp);
	SAFE_RELEASE(p2Hp);
	SAFE_RELEASE(backGround);
	SAFE_RELEASE(map);
	SAFE_RELEASE(roundTimer);
	SAFE_RELEASE(player1);
	SAFE_RELEASE(player2);

	KillTimer(g_hWnd, 1);
}

void FightScene::SetCharType(CharacterType type, int playerNum)
{
	switch (playerNum)
	{
	case 1:
		p1CharacterType = type;
		break;
	case 2:
		p2CharacterType = type;
		break;
	}
}
