#include "UI.h"
#include "Image.h"
#include "HPBar.h"
#include "Timer.h"
#include "KeyManager.h"


void UI::Init()
{
	p1HP = new HPBar;
	p1HP->Init();
	POINTFLOAT pos1{ HP_BAR_SET_X, HP_BAR_SET_Y };
	p1HP->SetPos(pos1);
	p1HP->SetPlayer1(true);

	p2HP = new HPBar;
	p2HP->Init();
	POINTFLOAT pos2{ WIN_SIZE_X - HP_BAR_SET_X, HP_BAR_SET_Y };
	p2HP->SetPos(pos2);
	p2HP->SetPlayer2(true);
}
void UI::Update()
{	
	p1HP->Update();
	p2HP->Update();
}

void UI::Render(HDC hdc)
{	
	p1HP->Render(hdc);
	p2HP->Render(hdc);
}
void UI::Release()
{
	SAFE_RELEASE(p1HP);
	SAFE_RELEASE(p2HP);
}
