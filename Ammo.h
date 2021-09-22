#pragma once
#include "Character.h"

class Terry;
class Mary;
class Ammo : public Character
{
private:
	Terry* terryTarget;
	Mary* maryTarget;
	bool terryFire;
	bool maryFire;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	bool CheckCollision();

	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	inline void SetTerryFire(bool Fire) { this->terryFire = Fire; }
	inline void SetMaryFire(bool Fire) { this->maryFire = Fire; }


	inline void SetTarget(Terry* target) { this->terryTarget = target; }
	inline void SetTarget(Mary* target) { this->maryTarget = target; }

	inline void SetMaxFrame(int maxFrame) { this->maxFrame = maxFrame; }


};

