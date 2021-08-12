#pragma once
#include "MonsterManager.h"
class Image;
class Monster_Archer:public MonsterManager
{
private:
	Image* img;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SetStartPos(FPOINT pos, RECT rc);
	virtual void Spawn();
	virtual void Idle();
	virtual void Move();
	virtual void Attack();
	virtual void Die();
	virtual void GoHome();
	virtual void Hit();
};