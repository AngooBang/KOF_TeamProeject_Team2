#pragma once
#include "GameEntity.h"

class Image;
class SelectIcon;
class FightScene;
class SelectScene : public GameEntity
{
private:
	Image* selectBackground;

	Image* charProfile;

	Image* selectCharframe;

	SelectIcon* iconP1;
	SelectIcon* iconP2;

	FightScene* fightScene;

	int elapsedtCount;


	int selectCharFramePos;



public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetFightScene(FightScene* scene) { this->fightScene = scene; }
};

