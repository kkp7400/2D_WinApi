#pragma once
#include "GameNode.h"

class Image;
class Enemy;
class Tank;
class Missile : public GameNode
{
public:
	enum TYPE { Normal, Skill_01, FollowTarget, End };

private:
	// ÀÌ¹ÌÁö
	Image* img;

	FPOINT pos;
	float moveSpeed;
	float moveTime;
	int size;
	RECT shape;
	int damage;
	float angle;
	bool isFired;
	TYPE missileType;
	int fireIndex;
	int fireStep;

	//GameNode* target;
	Enemy* target;
	float destAngle;

	Enemy* owner;
	Tank* t_Owner;

public:
	HRESULT Init(Enemy* owner);
	HRESULT Init(Tank* t_Owner);
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void MovingNormal();
	void MovingSkill_01();
	void MovingFollowTarget();

	void SetIsFired(bool isFired, FPOINT pos);
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline bool GetIsFired() { return this->isFired; }

	inline void SetTarget(Enemy* target) { this->target = target; }
	inline void SetType(TYPE type) { this->missileType = type; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
	inline RECT GetMissileShape() { return this->shape; }
	inline int GetSize() { return this->size; }
};

