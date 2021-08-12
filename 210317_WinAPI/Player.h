#pragma once
#include "CameraTarget.h"

class SkillManager;
class Button;
class Image;
class Player : public CameraTarget
{
private:
	char szText[128];
	Image* playerImage;

	Image* fireDashImage;

	bool isDashStop;
	bool isDashPos[5];
	bool isDashFX[5];
	POINT currFrame;
	int dashCurrFrameX[5];
	float dashTimer[5];
	POINT dashPos[5];
	bool isDashFXOn;
	float dashSkillCoolTime;

	bool isAlive;
	float nowHP;
	float maxHP;
	float atk;
	float moveSpeed;
	float moveFrameSpeed;
	float critPer;
	
	float elapsedTime;
	float runTimer;	
	vector<SkillManager*>skillMgr;
	bool atkDir;
	int atkCount;
	int isRunStopX; 
	float mAngle;
	FPOINT fMouse;
	vector<string>skillIndex;
	FPOINT pivot;
	POINT size;
	FPOINT clientPos;
	float coolTime[4];
	bool canMove;
	RECT hitCol;
	vector<RECT> atkCol;
	bool isHit = false;
	float hitTime;
public:
	enum class State
	{
		IDLE, MOVE, HIT, DASH, RUNEND, ATTACK, SKILL1, SKILL2, DIE, END, SPAWN
		//기본공격과 스킬을 나눈 이유는 맞으면 기본공격은 캔슬 되지만 스킬은
		//캔슬 안되기 때문
	};
	State state;
	enum DirState
	{
		LEFT, RIGHT, TOP, BOTTOM
	};
	DirState dirState;
	enum  MDir
	{
		좌단, 우단, 상단, 하단, 좌상단, 좌하단, 우상단, 우하단
	};
	MDir mDir;
	RECT moveCol;
	string hitDir = "None";
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Idle();	
	void Move();
	void Run();
	void Hit();
	void Dash();
	void Attack();	
	void Skill1();
	void Skill2();
	void Die();
	virtual ~Player() {}

	SkillManager* GetSkillMgr0() { return skillMgr[0]; }
	SkillManager* GetSkillMgr1() { return skillMgr[1]; }
	SkillManager* GetSkillMgr2() { return skillMgr[2]; }
	SkillManager* GetSkillMgr3() { return skillMgr[3]; }
	SkillManager* GetSkillMgr4() { return skillMgr[4]; }

	float GetAtk() { return this->atk; }

	void SetHitDir(string hitDir) { this->hitDir = hitDir; }
	void SetIsHit(bool isHit) { this->isHit = isHit; }
	void SetHp(float hp) { this->nowHP = hp; }
	float GetHp() { return this->nowHP; }
	void SetHitTime(float hitTime) { this->hitTime = hitTime; }
	vector<RECT>* GetAtkCol(int i);
	RECT GetHitCol() { return this->hitCol; }
	void SetCanMove(bool a) { this->canMove = a; }

	float GetNowHP() { return nowHP; }
	float GetMaxHP() { return maxHP; }

	void SetRockCoolTime(float coolTime) { this->coolTime[0] = coolTime; }
	float GetRockCoolTime() { return coolTime[0]; }

	RECT GetMoveCol() { return moveCol; }

	bool GetAtkDir() { return atkDir; }

	float GetMAngle() { return mAngle; }	

	FPOINT GetPos() { return pos; }
	void SetPos(FPOINT pos) { this->pos = pos; }

	float GetMoveSpeed() { return moveSpeed; }
	void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }

	int GetMoveFrameSpeed() { return moveFrameSpeed;}
	void SetMoveFrameSpeed(int moveFrameSpeed) { this->moveFrameSpeed = moveFrameSpeed; }

	DirState GetDirState() { return dirState; }
	void SetDirState(DirState dirState) { this->dirState = dirState; }

	State GetState() { return state; }
	void SetState(State state) { this->state = state; }

	POINT GetCurrFrame() { return currFrame; }
	void SetCurrFrame(POINT currFrame) { this->currFrame = currFrame; }

};