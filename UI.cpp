#include "UI.h"
#include "Image.h"
#include "HPBar.h"
#include "Timer.h"
#include "KeyManager.h"


void UI::Init()
{
	p1Hp = new HPBar;
	p1Hp->Init();
	POINTFLOAT pos1{ HP_BAR_SET_X, HP_BAR_SET_Y };
	p1Hp->SetPos(pos1);
	p1Hp->SetPlayerNum(1);

	p2Hp = new HPBar;
	p2Hp->Init();
	POINTFLOAT pos2{ WIN_SIZE_X - HP_BAR_SET_X, HP_BAR_SET_Y };
	p2Hp->SetPos(pos2);
	p2Hp->SetPlayerNum(2);

	isAlive = true;
}
void UI::Update()
{
	if (p1Hp->GetIsAlive() == true && p2Hp->GetIsAlive() == true)
	{
		p1Hp->Update();
		p2Hp->Update();
	}

	if (p1Hp->GetIsAlive() == false || p2Hp->GetIsAlive() == false)
	{
		isAlive = false;
	}
}

void UI::Render(HDC hdc)
{
	p1Hp->Render(hdc);
	p2Hp->Render(hdc);
}
void UI::Release()
{
	SAFE_RELEASE(p1Hp);
	SAFE_RELEASE(p2Hp);
}
