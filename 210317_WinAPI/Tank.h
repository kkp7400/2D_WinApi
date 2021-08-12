#pragma once
#include "GameNode.h"
//#include "Missile.h"

/*
	is-a 관계		탱크는 게임노드이다.
	has-a 관계		탱크는 미사일을 가지고 있다.
*/

class Image;
class Enemy;
class Missile;		// 전방선언
class MissileManager;
class Tank : public GameNode
{
private:
	// 속성 : 멤버변수
	FPOINT pos;
	int size;
	float attackValue;
	string name;
	RECT shape;
	int titleTimer;
	int currFrame;
	int elapsedTime;
	float moveSpeed = 0;
	enum Direction
	{
		LEFT, RIGHT, UP, DOWN
	};
	Direction tankDir;
	Image* tank;
	MissileManager* missileMgr;
	bool isAlive;
	// 포신
	// 포신의 시작점, 끝점
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;		// 단위	: 도 (degree)		0	~ 180	~ 360
							//		: 라디안 (radian)	0f	~ 3.14f	~ 6.28f
	float fireAngle;
	// 미사일
	int missileCount;
	//Missile* missile[3];	// 1
/*	Missile* missile;	*/	// 2

public:
	HRESULT Init();
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void RotateBarrel(float angle);
	void Move();
	void Fire();
	void FireSkill_01();
	void FireFollowTarget(Enemy* target);
	void Dead();

	// get, set
	FPOINT GetPos() { return this->pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline int GetMissileCount() { return this->missileCount; }
	//Missile* GetMissile() { return this->missile; }
	MissileManager* getMissileManager() { return missileMgr; }
	inline RECT GetShape() { return this->shape; }
	inline bool GetisAlive() { return this->isAlive; }
	inline void SetisAlive(bool isAlive) { this->isAlive = isAlive; }
};

