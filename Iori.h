#pragma once
#include "GameObject.h"
#include "Config.h"



//#include "Image.h" // ������ ���谡 ����, ������ �ð��� �����ɸ�

class Image;	//���԰���
class Iori : public GameObject	// ��Ӱ���
{
private:
	Image* img;
	int frameX, frameY;
	int elapsedCount;
	int AliveCount;
	bool isAlive;

	MoveDir moveDir;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();


};

