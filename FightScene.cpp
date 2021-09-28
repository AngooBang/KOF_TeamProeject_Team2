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
#include "HitBox.h"

void FightScene::Init()
{

	// HP
	HP = new UI;
	HP->Init();

	//���� Ÿ�̸�
	roundTimer = new Timer;
	roundTimer->Init();

	// ��� �̹���
	backGround = new Image;
	backGround->Init("Image/mapImage.bmp", 1400, 933); 


	// ��
	map = new Map();
	map->Init();

	// �÷��̾�
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
			HP->p2Hp->DamageToHp(SMALL_ATTACK_DAMAGE);
			break;
		case HitMotion::Big:
			HP->p2Hp->DamageToHp(BIG_ATTACK_DAMAGE);
			break;
		}
	}

	player2->Update();
	if (player1->GetIsHit()) // 1p�� ����
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
