#pragma once
#include "Character.h"
#include "Ammo.h"

class Mary : public Character
{
private:

	Image* backBuffer;

public:
	Ammo* ammo;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void KeyEvent(int a);
};

