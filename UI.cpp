#include "UI.h"
#include "Image.h"
#include "KeyManager.h"


void UI::Init()
{
	HP_bar = new Image;
	HP_bar->Init("Image/UI/hp_bar.bmp", 500, 63, true, RGB(255, 0, 255));

	Health_point = new Image;
	Health_point->Init("Image/UI/health_point.bmp", 492, 50, false, RGB(255, 0, 255));

	KO = new Image;
	KO->Init("Image/UI/K.O..bmp", 450, 150, true, RGB(255, 0, 255));

	pos.x = 0;
	pos.y = 0;
	
	hit_Player1 = false;
	hit_Player2 = false;

	isAlive = true;
}

void UI::InitTimer()
{
	Timer = new Image;
	Timer->Init("Image/UI/number.bmp", 140, 50, 10, 2, true, RGB(255, 0, 255));

	Time_Over = new Image;
	Time_Over->Init("Image/UI/time_over.bmp", 561, 187, true, RGB(255, 0, 255));

	elapsedCount = 0;
	timer_FrameX1 = 6, timer_FrameX2 = 0;
	timer_FrameY = 0;

	lostHp_Player2 = 0;

	isAlive = true;
}

void UI::Update()
{	
	
	if (hit_Player1)
	{
		{

			lostHp_Player1 += 50;
			lostHp_Player2 += 50;

			hit_Player1 = false;

			elapsedCount = 0;
		}
		if (lostHp_Player2 > 492)
		{
			isAlive = false;
		}
	}


	if (hit_Player2)
	{
		{
			lostHp_Player2 += 50;

			hit_Player2 = false;

			elapsedCount = 0;
		}
		if (lostHp_Player2 > 492)
		{
			isAlive = false;
		}
	}

	elapsedCount++;
	if (elapsedCount == 2)
	{
		timer_FrameX2--;
		if (timer_FrameX2 < 0)
		{
			timer_FrameX2 = 9;
			timer_FrameX1--;
		}
		if (timer_FrameX1 == 0)
		{
			timer_FrameY = 1;
		}
		if (timer_FrameX1 == 0 && timer_FrameX2 == 0)
		{
			timer_FrameX1 = 0, timer_FrameX2 = 0;
			elapsedCount == 3;
		}
		if (!(timer_FrameX1 == 0 && timer_FrameX2 == 0))
		{
			elapsedCount = 0;
		}
	}
}

void UI::Render(HDC hdc)
{	
	if (HP_bar)
	{
		HP_bar->Render(hdc, pos.x, pos.y);
	}
	if (Health_point)
	{
		Health_point->RenderHP(hdc, pos.x, pos.y, lostHp_Player1, lostHp_Player2);
	}
	if (lostHp_Player2 > 492)
	{
		KO->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	}
}

void UI::RenderTimer(HDC hdc)
{
	if (isAlive == true)
	{
		Timer->Render(hdc, TIMER_POS_X, TIMER_POS_Y, timer_FrameX1, timer_FrameY);
		Timer->Render(hdc, TIMER_POS_X + 14, TIMER_POS_Y, timer_FrameX2, timer_FrameY);
	}
	if (timer_FrameX1 == 0 && timer_FrameX2 == 0)
	{
		Time_Over->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	}

}



void UI::Release()
{
	if (HP_bar)
	{
		delete HP_bar;
		HP_bar = nullptr;
	}
	if (Health_point)
	{
		delete Health_point;
		Health_point = nullptr;
	}
	if (Timer)
	{
		delete Timer;
		Timer = nullptr;
	}
	if (Time_Over)
	{
		delete Time_Over;
		Time_Over = nullptr;
	}
	if (KO)
	{
		delete KO;
		KO = nullptr;
	}
}
