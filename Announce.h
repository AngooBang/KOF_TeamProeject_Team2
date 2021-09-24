#pragma once
#include "UI.h"

class Image;
class Announce : public UI
{
private:

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

