#include "HPBar.h"
#include "Image.h"
#include "KeyManager.h"

void HPBar::Init()
{
	hpBarFrameImg = new Image;
	hpBarFrameImg->Init("Image/UI/hp_bar.bmp", 407, 63, true, RGB(255, 0, 255));

	hpBarImg = new Image;
	hpBarImg->Init("Image/UI/health_point.bmp", 400, 50, false, RGB(255, 0, 255));

	portraitBackImg = new Image;
	portraitBackImg->Init("Image/UI/player_portrait.bmp", 594, 146, 2, 1, true, RGB(255, 0, 255));

	portraitImg = new Image;
	portraitImg->Init("Image/UI/portrait_mary_terry.bmp", 280, 130, 2, 1, true, RGB(89, 177, 77));

	koImg = new Image;
	koImg->Init("Image/UI/K.O..bmp", 450, 150, true, RGB(255, 0, 255));

	pos.x = 0;
	pos.y = 0;

	portraitBackImgX1 = 0;
	portraitBackImgX2 = WIN_SIZE_X;

	portraitImgX1 = -70;
	portraitImgX2 = WIN_SIZE_X + 70;

	playerNum = 0;
	characterNum = 0;

	lostHp = 0;
	lostHpMotion = 0;
	getDamage = 0;

	elapsecount = 0;

	isAlive = true;
}

void HPBar::Update()
{
	if (lostHp < lostHpMotion)
	{
		lostHp += 10;
	}
	
	if (lostHp >= 400)
	{
		isAlive = false;
	}
	//초상화 프레임 시작시 움직임 효과
	if (portraitBackImgX1 < 297 / 2)
	{
		portraitBackImgX1 += 25;
	}
	if (portraitBackImgX2 > WIN_SIZE_X - 297 / 2)
	{
		portraitBackImgX2 -= 25;
	}
	if (portraitImgX1 < 80)
	{
		portraitImgX1 += 20;
	}
	if (portraitImgX2 > WIN_SIZE_X - 80)
	{
		portraitImgX2 -= 20;
	}

}

void HPBar::Render(HDC hdc)
{
	switch (playerNum)
	{
	case 1:
		portraitBackImg->Render(hdc, portraitBackImgX1, pos.y, 0, 0);
		portraitImg->Render(hdc, portraitImgX1, pos.y - 2, characterNum - 1, 0);
		hpBarFrameImg->Render(hdc, pos.x, pos.y);
		hpBarImg->Render1pHP(hdc, pos.x, pos.y, lostHp);
		break;
	case 2:
		portraitBackImg->Render(hdc, portraitBackImgX2, pos.y, 1, 0);
		portraitImg->Render(hdc, portraitImgX2, pos.y - 2, characterNum - 1, 0);
		hpBarFrameImg->Render(hdc, pos.x, pos.y);
		hpBarImg->Render2pHP(hdc, pos.x, pos.y, lostHp);
		break;
	}

	if (!isAlive)
	{
		koImg->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	}
}

void HPBar::Release()
{
	SAFE_RELEASE(hpBarFrameImg);
	SAFE_RELEASE(hpBarImg);
	SAFE_RELEASE(portraitBackImg);
	SAFE_RELEASE(koImg);
}