#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>

using namespace std;

#define WIN_START_POS_X	100
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	1200
#define WIN_SIZE_Y	800
#define HP_BAR_SET_X	365
#define HP_BAR_SET_Y	100
#define TIMER_POS_X		587
#define TIMER_POS_Y		100


#define PI 3.14159265357989

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p){if (p) {p->Release(); delete p; p = nullptr;}}

enum MoveDir { Left, Right, Up, Down };
//enum hitBox { leftHand, rightHand, leftFoot, rightFoot };
enum E_SCENE
{
	E_SCENE_NONE = 0,
	E_SCENE_START,
	E_SCENE_SELECT,
	E_SCENE_FIGHT
};


extern HWND g_hWnd;
extern HINSTANCE g_hInstance;