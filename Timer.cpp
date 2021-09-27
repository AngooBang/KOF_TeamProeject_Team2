#include "Timer.h"
#include "Image.h"

void Timer::Init()
{
	timerNumImg = new Image;
	timerNumImg->Init("Image/UI/number.bmp", 280, 150, 10, 2, true, RGB(255, 0, 255));

	timeOverImg = new Image;
	timeOverImg->Init("Image/UI/time_over.bmp", 561, 187, true, RGB(255, 0, 255));

	tenSecNumImg = 6;
	oneSecNumImg = 0;
	chgNumColor = 0;

	isAlive = true;
}

void Timer::Update()
{
	if (!isAlive) return;

	oneSecNumImg--;
	if (oneSecNumImg < 0)
	{
		oneSecNumImg = 9;
		tenSecNumImg--;
	}
	if (tenSecNumImg == 1 && !oneSecNumImg)	//남은시간 10초
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
	}
}

void Timer::Release()
{
	SAFE_RELEASE(timerNumImg);
	SAFE_RELEASE(timeOverImg);
}
