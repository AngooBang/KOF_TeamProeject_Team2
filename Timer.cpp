#include "Timer.h"
#include "Image.h"

void Timer::Init()
{
	SecTimer = new Image;
	SecTimer->Init("Image/UI/number.bmp", 140, 50, 10, 2, true, RGB(255, 0, 255));

	TimeOver = new Image;
	TimeOver->Init("Image/UI/time_over.bmp", 561, 187, true, RGB(255, 0, 255));

	tenSec = 6;
	oneSec = 0;
	chgNumColor = 0;

	isAlive = true;
}

void Timer::Update()
{
	oneSec--;
	if (oneSec < 0)
	{
		oneSec = 9;
		tenSec--;
	}
	if (tenSec == 1 && oneSec == 0)	//남은시간 10초
	{
		chgNumColor = 1;
	}
	if (tenSec == 0 && oneSec == 0) //남은시간 00초
	{
		tenSec = 0, oneSec = 0;
	}
}

void Timer::Render(HDC hdc)
{
	if (isAlive == true)
	{
		SecTimer->Render(hdc, TIMER_POS_X, TIMER_POS_Y, tenSec, chgNumColor);
		SecTimer->Render(hdc, TIMER_POS_X + 14, TIMER_POS_Y, oneSec, chgNumColor);
	}
	if (tenSec == 0 && oneSec == 0)
	{
		TimeOver->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	}
}

void Timer::Release()
{
	if (SecTimer)
	{
		delete SecTimer;
		SecTimer = nullptr;
	}
	if (TimeOver)
	{
		delete TimeOver;
		TimeOver = nullptr;
	}
}
