#pragma once
#include "GameNode.h"
class Player;
class MonsterManager: public GameNode
{
protected:	
	Player* player;
	FPOINT pos;
	float atk;
	float hp;
	float moveSpeed;
	float elapsedTime;		
	FPOINT startPos;
	RECT aggroRange;
	enum STATE
	{
		NONE, SPAWN, IDLE, MOVE, ATTACK, DIE, GOHOME, HIT, END
	};
	enum DIRECTION
	{
		LEFT, RIGHT
	};
	DIRECTION dir;
	STATE state;
	bool isSpawn = false;
	POINT currFrame;
	float moveFrameSpeed;
	RECT atkRange;
	float angle;
	POINT fxCurrFrame;
	RECT atkCol;
	RECT hitCol;
	bool isHit;
	int hitDir;
public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void SetStartPos(FPOINT pos, RECT rc) = 0;
	virtual void SetPlayer(Player* player) { this->player = player; }
	virtual void Spawn() = 0;
	virtual void Idle() = 0;
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void Die() = 0;
	virtual void GoHome() = 0;
	virtual void Hit() = 0;
	virtual void SetHp(float hp) = 0;
	virtual float GetHp() = 0;
	virtual RECT GetHitCol() = 0;
	virtual RECT GetAtkCol() = 0;
	virtual FPOINT GetPos() = 0;
	virtual void SetPos(FPOINT pos) = 0;
	virtual void SetIsHit(bool isHit) = 0;
	virtual float GetAtk() = 0;


};
//
//astar는 쓰지 말구벽 못넘게하구
//
//그 vMap 넘겨주고  v맵의 중심에서 어느정도 인지 쓰고
//
//입구 부분 HOLE로 해서 못 들어가게
//홀이랑 WALL충돌 체크
//
//몬스터 ui처럼 만들고
//
//몬스터 인터페이스 만들고
//
//몬스터 스폰 매니저 만들고
//그냥 인지 범위 안이면 무조건 이동
//
//몬스터 인지 범위는 렉트를 받아 와야겠다.
//인잇에서 줘야겠다 처음 위치랑 인지 범위를
//
//rc의 사이즈 / 3만큼 근데 각 rc가
//
//1. hp가 0이면 다이
//2. 플레이어가 어그로레인지 안에 들어오면 스폰
//3. 그 다음에 공격 범위 밖이면 무브
//4. 공격 범위 안이면 어택
//5. 플래이어가 어그로 범위를 벗어나면 hp 100으로 만들고  스타트 포지션으로 이동
