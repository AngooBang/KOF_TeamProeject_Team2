#pragma once
#include "Character.h"

class Terry : public Character
{
private:
	char inputKey;
public:

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void ProcessInputKey();
	void KeyEvent(char inputKey);
	void SetBodySize();
	void MoveToFrame();
	void NextFrame(bool b);
};

