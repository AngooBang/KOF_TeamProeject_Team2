#pragma once

#include "GameEntity.h"


class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos;
	RECT shape;
	float moveSpeed;
	int bodySizeX, bodySizeY;
	MoveDir moveDir;

public:
	void Move();

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySizeX() { return this->bodySizeX; }
	inline int GetBodySizeY() { return this->bodySizeY; }
	

	GameObject();
	~GameObject();

};

