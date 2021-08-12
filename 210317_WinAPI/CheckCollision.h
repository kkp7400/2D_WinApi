#pragma once
#include "GameNode.h"
#include "config.h"

#define TILESIZE		40

// 메인 그리기 공간 정보
#define	TILE_X			20
#define	TILE_Y			20

class Enemy;
class MissileManager;
class Tank;
class Player;
class EnemyManager;
class BattleScene;
class Monster;
class CheckCollision : public Singleton<CheckCollision>
{
private:
	BattleScene* battleScene;
	RECT interRcet;
	RECT playerRc;
	RECT tileRC;
	FPOINT pos;
	Player* player;
	Monster* monster;
public:
	HRESULT Init();
	FPOINT PlayerVsTile(RECT rc, FPOINT playerPos, vector<vector<TILE_INFO>>&tile);	
	void SetMonster(Monster* monster) { this->monster = monster; }
	void SetPlayer(Player* player) { this->player = player; }
	void Update();
	void PlayerHitVsMonHit();
	void PlayerAtkVsMonHit();
	void PlayerHitVsMonAtk();
};