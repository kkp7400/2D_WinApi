// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

#define WINSIZE_X	1366
#define WINSIZE_Y	768
#define TILEMAPTOOLSIZE_X	1800
#define TILEMAPTOOLSIZE_Y	900
#define ASTARSIZE_X	5000
#define ASTARSIZE_Y	5000
#define WORLDSIZE_X	5000//30 * 24
#define WORLDSIZE_Y	5000//30 * 24

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

enum TILEOPTION
{
	WALL, WAY, HOLE, BLANK, END, START, INWALL, WALLTWO, MAX_COUNT
};

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagTile
{
	int index;
	RECT rcTile;
	int frameX;
	int frameY;	
	bool isAlive;
	TILEOPTION tileVar;
} TILE_INFO;

typedef struct battleZoneRect
{
	int index;
	RECT rect;
}BATTLE_ZONE;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
