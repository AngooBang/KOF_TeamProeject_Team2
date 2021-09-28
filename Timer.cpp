#include "Timer.h"
#include "Image.h"

void Timer::Init()
{
	timerNumImg = new Image;
	timerNumImg->Init("Image/UI/number.bmp", 280, 150, 10, 2, true, RGB(255, 0, 255));

	timeOverImg = new Image;
	timeOverImg->Init("Image/UI/time_over.bmp", 561, 187, true, RGB(255, 0, 255));

	timeOverImgEffect = new Image;
	timeOverImgEffect->Init("Image/UI/time_over2.bmp", 561, 187, true, RGB(255, 0, 255));

	tenSecNumImg = 6;
	oneSecNumImg = 0;
	chgNumColor = 0;

	elapsedcount1 = 0;
	elapsedcount2 = 0;

	isAlive = true;
	wordEffect = true;
}

void Timer::Update()
{
	elapsedcount1++;
	if (!isAlive)
	{
		elapsedcount2++;
		if (elapsedcount2 < 6)
		{
			if (wordEffect) wordEffect = false;
			else if (!wordEffect) wordEffect = true;
		}
		return;
	}
	//oneSecNumImg--;
	if (elapsedcount1 == 2)
	{
		oneSecNumImg--;
		elapsedcount1 = 0;
	}
	if (oneSecNumImg < 0)
	{
		oneSecNumImg = 9;
		tenSecNumImg--;
	}
	if (tenSecNumImg == 1 && !oneSecNumImg && chgNumColor == 0)	//남은시간 10초
	{
		chgNumColor = 1;
	}
	else if (tenSecNumImg == 0 && oneSecNumImg && chgNumColor == 1)
	{
		chgNumColor = 0;
	}
	else if (tenSecNumImg == 0 && oneSecNumImg && chgNumColor == 0)
	{
		chgNumColor = 1;
	}
	if (!tenSecNumImg && !oneSecNumImg) //남은시간 00초
	{
		tenSecNumImg = 0, oneSecNumImg = 0;
		isAlive = false;
	}
}

void Timer::Render(HDC hdc)
{
	if (timerNumImg)
	{
		timerNumImg->Render(hdc, TIMER_POS_X, TIMER_POS_Y, tenSecNumImg, chgNumColor);
		timerNumImg->Render(hdc, TIMER_POS_X + 28, TIMER_POS_Y, oneSecNumImg, chgNumColor);
	}
	if (!tenSecNumImg && !oneSecNumImg)
	{
		timeOverImg->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		if(wordEffect)timeOverImgEffect->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	}
}

void Timer::Release()
{
	SAFE_RELEASE(timerNumImg);
	SAFE_RELEASE(timeOverImg);
}
