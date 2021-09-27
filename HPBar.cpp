#include "HPBar.h"
#include "Image.h"
#include "KeyManager.h"

void HPBar::Init()
{
	HPBarFrame = new Image;
	HPBarFrame->Init("Image/UI/hp_bar.bmp", 407, 63, true, RGB(255, 0, 255));

	HPBar = new Image;
	HPBar->Init("Image/UI/health_point.bmp", 400, 50, false, RGB(255, 0, 255));

	Portrait = new Image;
	Portrait->Init("Image/UI/player_portrait.bmp", 594, 146, 2, 1, true, RGB(255, 0, 255));
	 
	KO = new Image;
	KO->Init("Image/UI/K.O..bmp", 450, 150, true, RGB(255, 0, 255));

	pos.x = 0;
	pos.y = 0;

	portraitX1 = 0;
	portraitX2 = WIN_SIZE_X;

	HP = 400;
	lostHP = 0;
	damage = 50;

	player1, player2 = false;
	hitP1, hitP2 = false;
	isAlive = true;
}

void HPBar::Update()
{
	if (player1)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))//hitP1
		{
			lostHP += damage;
			hp -= damage;
		}
	}
	if (player2)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))//hitP2
		{
			lostHP += damage;
			hp -= damage;
		}
	}
	if (HP <= 0)
	{
		isAlive = false;
	}
	//초상화 프레임 시작시 움직임 효과
	if (portraitX1 < 297 / 2)
	{
		portraitX1 += 25;
	}
	if (portraitX2 > WIN_SIZE_X - 297 / 2)
	{
		portraitX2 -= 25;
	}
}

void HPBar::Render(HDC hdc)
{	
	if (Portrait)
	{
		if (player1) Portrait->Render(hdc, portraitX1, pos.y, 0, 0);
		if (player2) Portrait->Render(hdc, portraitX2, pos.y, 1, 0);
	}

	if (HPBarFrame)
	{
		HPBarFrame->Render(hdc, pos.x, pos.y);
	}

	if (HPBar)
	{
		if(player1)	HPBar->Render1pHP(hdc, pos.x, pos.y, lostHP);
		if(player2) HPBar->Render2pHP(hdc, pos.x, pos.y, lostHP);
	}

	if (isAlive == false)
	{
		KO->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	}
}

void HPBar::Release()
{
	if (HPBarFrame)
	{
		delete HPBarFrame;
		HPBarFrame = nullptr;
	}
	if (HPBar)
	{
		delete HPBar;
		HPBar = nullptr;
	}
	if (Portrait)
	{
		delete HPBar;
		HPBar = nullptr;
	}
	if (KO)
	{
		delete KO;
		KO = nullptr;
	}
}