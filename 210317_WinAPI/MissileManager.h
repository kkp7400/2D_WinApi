#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class Tank;
class Missile;
class MissileManager : public GameNode
{
private:
	vector<Missile*> vMissiles;
	vector<Missile*>::iterator itMissiles;
	
	Enemy* owner;
	Tank* t_Owner;

public:
	HRESULT Init(Enemy* owner);
	HRESULT Init(Tank* t_Owner);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos, float angle);
	vector<Missile*> GetMissiles() { return vMissiles; }
};

