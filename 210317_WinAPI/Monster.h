#pragma once
#include "GameNode.h"

class Player;
class MonsterManager;
class Monster : public GameNode
{
private:
	//MonsterManager* stage1Mon[3];
	//MonsterManager* stage2Mon[1];
	//MonsterManager* stage3Mon[1];
	//MonsterManager* stage4Mon[2];
	//MonsterManager* stage5Mon[3];
	//MonsterManager* stage6Mon[4];
	//MonsterManager* stage7Mon[3];
	//MonsterManager* stage8Mon[2];
	//MonsterManager* stage9Mon[1];

	MonsterManager* stage02Mon[1];
	MonsterManager* stage03Mon[1];
	MonsterManager* stage04Mon[1];
	MonsterManager* stage05Mon[1];
	MonsterManager* stage06Mon[1];
	MonsterManager* stage07Mon[1];
	MonsterManager* stage08Mon[1];
	MonsterManager* stage09Mon[1];
	MonsterManager* stage10Mon[1];
	Player* player;
	FPOINT pos;

public:
	virtual HRESULT Init(vector<BATTLE_ZONE> rc);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	MonsterManager* GetMonMgr(int i, int j);
	void SetPlayer(Player* player) { this->player = player; }
};

