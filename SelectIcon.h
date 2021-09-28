#pragma once
#include "GameObject.h"

class Image;
class SelectIcon;
class SelectIcon : public GameObject
{
private:
	Image* icon;

	int frameX, frameY;
	int* frameXData;
	int frameXDataInput[5];

	SelectIcon* target;

	CharacterType characterType;

	bool isSelect;

	int playerNum;
	int elapsedCount;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetPosFromCharType();
	void InputLeft();
	void InputRight();

	inline CharacterType GetCharacterType() { return this->characterType; }
	inline bool GetIsSelect() { return this->isSelect; }

	inline void SetTarget(SelectIcon* target) { this->target = target; }
	inline void SetCharacterType(CharacterType type) { this->characterType = type; }
	inline void SetPlayerNum(int num) { this->playerNum = num; }


};

