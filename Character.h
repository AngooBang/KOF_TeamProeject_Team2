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
	int* actionFrameX[Action::END];
	int maxFrame[Action::END];
	int hp;
	bool isStatus,  isHit, isMove;

	//int terryWalk[15] = { 0, 87, 172, 256, 342, 426, 511, 598 };
	//actionFrameX[Action::Basic] = terryWalk;
	//int terryfMove[15] = { 0, 77, 151, 217, 281, 345, 423 };
	//actionFrameX[Action::fMove] = terryfMove;
	//int terrybMove[15] = { 0, 85, 152, 217, 280, 335, 409 };
	//actionFrameX[Action::bMove] = terrybMove;
	//int terrysHand[15] = { 0, 85, 188, 275 };
	//actionFrameX[Action::sHand] = terrysHand;
	//int terrybHand[15] = { 0, 86, 170, 254, 371, 486, 577, 660, 753 };
	//actionFrameX[Action::bHand] = terrybHand;
	//int terrysKick[15] = { 0, 90, 156, 282, 348, 444 };
	//actionFrameX[Action::sKick] = terrysKick;
	//int terrybKick[15] = { 0, 75, 140, 260, 375, 490, 590, 650, 745 };
	//actionFrameX[Action::bKick] = terrybKick;
	//int terrysHit[15] = { 0, 97, 192, 276, 353, 440 };
	//actionFrameX[Action::sHit] = terrysHit;
	//int terrybHit[15] = { 0, 94, 194, 290, 385, 473 };
	//actionFrameX[Action::bHit] = terrybHit;

	//int* walkFrameX, fMoveFrameX[15], bMoveFrameX[15], sHandFrameX[15], bHandFrameX[15], sKickFrameX[15], bKickFrameX[15], sHitFrameX[15], bHitFrameX[15];

	Action action;
	HitMotion hitMotion;


public:
	HitBox* hitBox;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetCharacterData(CharacterType type);
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


	inline bool GetIsHit() { return this->isHit; }
	inline int GetPlayerNum() { return this->playerNum; }

	inline void SetHitMotion(HitMotion hitMotion) { this->hitMotion = hitMotion; }
	inline HitMotion GetHitMotion() { return this->hitMotion; }



};

