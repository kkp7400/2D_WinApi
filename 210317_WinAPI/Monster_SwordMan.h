#pragma once
#include "MonsterManager.h"
class Image;
class Monster_SwordMan: public MonsterManager
{
private:
	Image* spawn;
	Image* swordManLeft;
	Image* swordManRight;
	Image* effect;
	float atkCool;
	char szText[128];
	POINT fxCurrFrame;
	float fxElapsedTime = 0;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void SetStartPos(FPOINT pos, RECT rc);
	virtual void Spawn();
	virtual void Idle();
	virtual void Move();
	virtual void Attack();
	virtual void Die();
	virtual void GoHome();
	virtual void Hit();
	virtual void SetHp(float hp) { this->hp = hp; }
	virtual float GetHp() { return this->hp; };
	virtual RECT GetHitCol() { return hitCol; }
	virtual RECT GetAtkCol() { return atkCol; }
	virtual FPOINT GetPos() { return pos; }
	virtual void SetPos(FPOINT pos) { this->pos = pos; }
	virtual void SetIsHit(bool isHit) { this->isHit = isHit; }
	virtual float GetAtk() { return this->atk; };
};
