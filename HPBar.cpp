#include "HPBar.h"
#include "Image.h"
#include "KeyManager.h"

void HPBar::Init()
{
	hpBarFrameImg = new Image;
	hpBarFrameImg->Init("Image/UI/hp_bar.bmp", 407, 63, true, RGB(255, 0, 255));

	hpBarImg = new Image;
	hpBarImg->Init("Image/UI/health_point.bmp", 400, 50, false, RGB(255, 0, 255));

	koImg = new Image;
	koImg->Init("Image/UI/K.O..bmp", 450, 150, true, RGB(255, 0, 255));

	koImgEffect = new Image;
	koImgEffect->Init("Image/UI/K.O.2.bmp", 450, 150, true, RGB(255, 0, 255));


	portraitImg = new Image;
	switch (characterType)
	{
	case CharacterType::Terry:
		portraitImg->Init("Image/SelectCharacterImage/TerryProfile.bmp", 140, 130, true, RGB(89, 177, 77));
		break;
	case CharacterType::Mary:
		portraitImg->Init("Image/SelectCharacterImage/MarryProfile.bmp", 140, 130, true, RGB(89, 177, 77));
		break;
	}


	portraitBackImg = new Image;
	switch (playerNum)
	{
	case 1:
		portraitBackImg->Init("Image/UI/player_portrait1.bmp", 297, 146, true, RGB(255, 0, 255));
		portraitImgFrameX = 0;
		pos.x = HP_BAR_SET_X;
		break;
	case 2:
		portraitBackImg->Init("Image/UI/player_portrait2.bmp", 297, 146, true, RGB(255, 0, 255));
		portraitImgFrameX = WIN_SIZE_X;
		pos.x = WIN_SIZE_X - HP_BAR_SET_X;
		break;
	}

	pos.y = HP_BAR_SET_Y;

	lostHp = 0;
	lostHpMotion = 0;
	getDamage = 0;

	elapsedcount = 0;

	wordEffect = true;
	isAlive = true;
}

void HPBar::Update()
{
	if (isAlive)
	{
		if (lostHp < lostHpMotion)
			{
				lostHp += 10;
			}
			
			if (lostHp >= 400)
			{
				isAlive = false;
			}
	}
	
	//초상화 프레임 시작시 움직임 효과
	switch (playerNum)
	{
	case 1:
		if (portraitImgFrameX < 149)
			portraitImgFrameX += 25;
		break;
	case 2:
		if (portraitImgFrameX > WIN_SIZE_X - 149)
			portraitImgFrameX -= 25;
		break;
	}
	
	if (!isAlive)
	{
		elapsedcount++;
		if(elapsedcount < 10)
		{
			if (wordEffect) wordEffect = false;
			else if (!wordEffect) wordEffect = true;
		}
	}
		

}

void HPBar::Render(HDC hdc)
{
	switch (playerNum)
	{
		case 1:
			portraitBackImg->Render(hdc, portraitImgFrameX, pos.y);
			portraitImg->Render(hdc, portraitImgFrameX - 70, pos.y);
			hpBarFrameImg->Render(hdc, pos.x, pos.y);
			hpBarImg->Render1pHP(hdc, pos.x, pos.y, lostHp);
			break;
		case 2:
			portraitBackImg->Render(hdc, portraitImgFrameX, pos.y);
			portraitImg->Render(hdc, portraitImgFrameX + 70, pos.y);
			hpBarFrameImg->Render(hdc, pos.x, pos.y);
			hpBarImg->Render2pHP(hdc, pos.x, pos.y, lostHp);
			break;
	}
	
	if (!isAlive)
	{
		koImg->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		if(wordEffect)
		koImgEffect->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	}
}

void HPBar::Release()
{
	SAFE_RELEASE(hpBarFrameImg);
	SAFE_RELEASE(hpBarImg);
	SAFE_RELEASE(portraitBackImg);
	SAFE_RELEASE(koImg);
}

