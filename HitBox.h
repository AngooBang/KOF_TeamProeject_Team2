#pragma once
#include "GameObject.h"

class Image;
class Character;
class HitBox : public GameObject
{
private:

	Character* target;
	Image* img;
	HitMotion hitMotion;
	bool isFire, isHit;

	POINTFLOAT targetPos;

	int frameX, frameY;
	int maxFrame;
	int actionFrameX[10];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void CheckCollision();

	void SetBodySize();
	void NextFrame();



	inline void SetMaxFrame(int maxFrame) { this->maxFrame = maxFrame; }
	inline void SetTarget(Character* target) { this->target = target; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	inline void SetHitMotion(HitMotion hitMotion) { this->hitMotion = hitMotion; }

};

