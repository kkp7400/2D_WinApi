#pragma once
#include "GameNode.h"

// TODO : ��ĳ����, �ٿ�ĳ���� ����
class Image;
class Tank;
class MissileManager;
class Enemy : public GameNode
{
private:
	MissileManager* missileMgr;

	Image* image;
	int currFrameX;
	int updateCount;
	FPOINT pos;
	int size;
	RECT enemyShape;
	float moveSpeed;
	bool isAlive;
	float angle;
	float currTimer = 0;
	

	//GameNode* target;
	Tank* target;
	FPOINT startPos;

	string name;
	int fireCount;
	int currTimer2 = 0;
	int dir;
public:
	HRESULT Init(int posX = 0, int posY = 0);		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	void HorizonMove();

	// get, set
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
	inline RECT GetEnemyShape() { return this->enemyShape; }
	MissileManager* getMissileManager() { return missileMgr; }
};

