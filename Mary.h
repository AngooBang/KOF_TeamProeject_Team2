#pragma once
#include "Character.h"

class Mary : public Character
{
private:


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

