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
//astar�� ���� ������ ���Ѱ��ϱ�
//
//�� vMap �Ѱ��ְ�  v���� �߽ɿ��� ������� ���� ����
//
//�Ա� �κ� HOLE�� �ؼ� �� ����
//Ȧ�̶� WALL�浹 üũ
//
//���� uió�� �����
//
//���� �������̽� �����
//
//���� ���� �Ŵ��� �����
//�׳� ���� ���� ���̸� ������ �̵�
//
//���� ���� ������ ��Ʈ�� �޾� �;߰ڴ�.
//���տ��� ��߰ڴ� ó�� ��ġ�� ���� ������
//
//rc�� ������ / 3��ŭ �ٵ� �� rc��
//
//1. hp�� 0�̸� ����
//2. �÷��̾ ��׷η����� �ȿ� ������ ����
//3. �� ������ ���� ���� ���̸� ����
//4. ���� ���� ���̸� ����
//5. �÷��̾ ��׷� ������ ����� hp 100���� �����  ��ŸƮ ���������� �̵�
