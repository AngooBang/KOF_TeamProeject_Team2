#pragma once
#include "Character.h"
#include "Ammo.h"

class Terry : public Character
{
private:

public:
	Ammo* ammo;
	Image* backBuffer;
	Image* backGround;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void KeyEvent(int a);
	
};

