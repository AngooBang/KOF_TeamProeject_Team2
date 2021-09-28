#pragma once
#include "GameObject.h"
#include <string>

class Image;
class Terry;
class Mary;
class HitBox;
class Character : public GameObject
{
protected:
	Image* charImg;

	int playerNum;
	CharacterType characterType;


	int frameX, frameY;
	int* actionFrameX[Action::ActEnd];
	int maxFrame[Action::ActEnd];
	int hp;
	bool isStatus, isHit, isMove, commandAction, isDead, isWin, swapPosition, isSwap;

	Action action;
	HitMotion hitMotion;


public:
	HitBox* hitBox;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetCharacterData(CharacterType type);
	void SwapCharacterData();
	void ReverseImg();

	void ProcessInputKey();
	void KeyEvent(char inputKey);
	void SetBodySize();
	void MoveToFrame();
	void NextFrame();
	void isFire();
	void IsHit();
	

	inline void SetCharacterType(CharacterType type) { this->characterType = type; }
	inline void SetPlayerNum(int num) { this->playerNum = num; }
	inline void SetIsHit(bool isHit) { this->isHit = isHit; }
	inline void setisWin(bool isWin) { this->isWin = isWin; }
	inline void SetHitMotion(HitMotion hitMotion) { this->hitMotion = hitMotion; }
	inline void SetswapPosition(bool swapPosition) { this->swapPosition = swapPosition; }

	inline int GetPlayerNum() { return this->playerNum; }
	inline bool GetIsHit() { return this->isHit; }
	inline bool GetIsDead() { return this->isDead; }
	inline bool GetIsSwap() { return this->isSwap; }
	inline Action GetAction() { return this->action; }
	inline HitMotion GetHitMotion() { return this->hitMotion; }



};

