#pragma once
#include "GameObject.h"

class Image;
class Intro : public GameObject
{
private:
	Image* IntroBackground1;
	Image* IntroBackground2;
	Image* IntroWalking;
	Image* WalkingWord;
	Image* Wall;
	Image* Intro2Img1;
	Image* Intro2Img2;
	Image* Episode;
	Image* EpisodeImg;
	Image* Intro4Img1;
	Image* Intro4Img2;
	Image* Intro4Img3;
	Image* Intro4Img4;
	Image* Intro4Img5;
	Image* GameLogo1;
	Image* GameLogo2;

	int blackPosX, blackPosY;
	int walkFrameX, walkFrameY;
	int walkPosX;
	int wordFrameX, wordFrameY;
	int wordPosX;
	int wallPosX;
	int intro2PosY1, intro2PosY2;
	int Intro2Img2FmX, Intro2Img2FmY;
	int intro2PosX2;
	int episodeFrmX;
	int episodeImgX, episodeImgY;
	int Intro4Img1X;
	int Intro4Img3X, Intro4Img3Y;
	int Intro4Img4X;
	int Intro4Img5X, Intro4Img5Y;
	
	int elapsedCount1, elapsedCount2, elapsedCount3, elapsedCount4;

	bool showIntro, gameStart;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};


