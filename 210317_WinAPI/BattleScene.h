#pragma once
#include "GameNode.h"
#define TILESIZE		40

// 메인 그리기 공간 정보
#define	TILE_X			20
#define	TILE_Y			20

//typedef struct b_tagTile
//{
//	RECT rcTile;
//	int frameX;
//	int frameY;
//	TILEOPTION tileVar;
//} B_TILE_INFO;
// 기존 MainGame 클래스의 내용을 이동
class Player;
class EnemyManager;
class Image;
class CheckCollision;
class UI;
class RandomMap;
class Monster;
class BattleScene : public GameNode
{
private:
	UI* ui;	
	Image* stage;
	Image* bin;
	Image* spawn;
	Player* player;
	EnemyManager* enemyMgr;
	CheckCollision* checkAll;
	RandomMap* randMap;
	RECT cameraRect;
	int zoomValue;
	char szText[128];
	// 메인타일의 정보
	static TILE_INFO tileInfo[TILE_X * TILE_Y];
	RECT rcMain;
	vector<TILE_INFO> map;
	vector<vector<TILE_INFO>> map2;
	bool isRandMapStop;
	vector<BATTLE_ZONE> battleZon;
	Monster* mon;
	int currX=0;
	float elapsedTime=0;
	bool isSpawn = false;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	//Player GetPlayer() { return *player; }

	void CheckCollision();
	static void Load();
	virtual ~BattleScene() {};

	inline TILE_INFO GetTileInfo() { return this->tileInfo[TILE_X * TILE_Y]; }
	inline void SetTileInfo(TILE_INFO tileInfo){this->tileInfo[TILE_X * TILE_Y] = tileInfo;}
};

