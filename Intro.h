#pragma once
#include "GameObject.h"

class Image;
class Intro : public GameObject
{
private:
	Image* introImage[16];

	int introBackground2PosX, introBackground2PosY;

	int intro1WalkingMotionFrameX;
	int intro1WalkingMotionPosX;
	int intro1TiltleWordFrameX, intro1TiltleWordFrameY;
	int intro1TiltleWordPosX;
	int intro1WallPosX;

	int intro2HorizontalImgPosY;
	int	intro2VerticalImgPosY;
	int Intro2Img2FmX, Intro2Img2FmY;

	int intro3EpisodeWordFrmX;
	int intro3EpisodeImgFrmX, intro3EpisodeImgFrmY;

	int intro4StepImgFrmX;
	int intro4BackgroundFrmX, intro4BackgroundFrmY;
	int intro4KickReadyMotionFrmX;
	int intro4KickMotionFrmX, intro4KickMotionFrmY;

	int elapsedCount1, elapsedCount2, elapsedCount3, elapsedCount4;

	bool showIntro, gameStart;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

