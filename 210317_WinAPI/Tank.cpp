#include "CommonFunction.h"
#include "Tank.h"
#include "Missile.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Tank::Init()
{
	ImageManager::GetSingleton()->AddImage("탱크", "Image/BattleCity/Player/Player.bmp", 512 * 0.8, 256 * 0.8, 8, 4, true, RGB(255, 0, 255));
	tank = ImageManager::GetSingleton()->FindImage("탱크");


	missileMgr = new MissileManager();
	if (missileMgr)missileMgr->Init(this);
	currFrame = 2;
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;
	size = 40;
	attackValue = 10;
	name = "탱크";
	shape = GetRectToCenter(pos.x, pos.y, size, size);
	isAlive = true;

	// 포신
	barrelSize = 50;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = DegToRad(90);
	fireAngle = 90;
	// 미사일
	/*missileCount = 300;
	missile = new Missile[missileCount];
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Init(this);
	}*/
	tankDir = UP;

	//for (int i = 0; i < missileCount; i++)
	//{
	//	missile[i] = new Missile();
	//	missile[i]->Init();
	//}

	//missile = new Missile();
	//missile->Init();

	return S_OK;
}

void Tank::Release()
{
	/*for (int i = 0; i < missileCount; i++)
	{
		missile[i].Release();
	}
	delete[] missile;*/

	//for (int i = 0; i < missileCount; i++)
	//{
	//	missile[i]->Release();
	//}
	//delete[] missile;

	//missile->Release();
	//delete missile;
	if (missileMgr)SAFE_RELEASE(missileMgr);
}

void Tank::Update()
{
	if (isAlive)
	{
		moveSpeed = 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
		if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
		{
			//FireFollowTarget(&enemy[0]);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
		{
			FireSkill_01();
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
		{
			if (missileMgr)missileMgr->Fire(pos, fireAngle);
		}
		//moveSpeed = 100.0f * TimerManager::GetSingleton()->GetElapsedTime();

		Move();

		// 포신 각도에 따른 좌표 계산
		barrelEnd.x = pos.x + cosf(barrelAngle) * barrelSize;
		barrelEnd.y = pos.y - (sinf(barrelAngle)) * barrelSize;

		if (missileMgr)missileMgr->Update();
	}
	if (!isAlive)
	{
		pos = { -200, -200 };
		size = 0;
	}

}

void Tank::Render(HDC hdc)
{
	//if (isAlive)
	//{
		// 몸통
		shape = GetRectToCenter(pos.x, pos.y, size, size);
		//Rectangle(hdc, pos.x - size / 2, pos.y - size / 2, pos.x + size / 2, pos.y + size / 2 /*shape.left, shape.top, shape.right, shape.bottom*/);

		// 포신
		MoveToEx(hdc, pos.x, pos.y, NULL);
		LineTo(hdc, barrelEnd.x, barrelEnd.y);

		// 미사일
		/*for (int i = 0; i < missileCount; i++)
		{
			missile[i].Render(hdc);
		}*/

		tank->FrameRender(hdc, pos.x, pos.y, currFrame, 0, true);

		if (missileMgr)missileMgr->Render(hdc);
	/*}*/
	//if (!isAlive)
	//{
	//	shape = GetRectToCenter(pos.x, pos.y, size, size);
	//}
}

//void Tank::RotateBarrel(float angle)
//{
//	barrelAngle = angle;
//}

void Tank::Move()
{

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))currFrame = 2;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		currFrame++;
		if (currFrame > 3 && titleTimer % 100 == 0)
		{
			currFrame = 2;
		}
		pos.x -= moveSpeed;
		/*RotateBarrel(0);*/
		barrelAngle = DegToRad(180);
		fireAngle = 180;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))currFrame = 6;
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		currFrame++;
		if (currFrame > 7 && titleTimer % 100 == 0)
		{
			currFrame = 6;
		}
		pos.x += moveSpeed;
		/*RotateBarrel(0);*/
		barrelAngle = DegToRad(0);
		fireAngle = 0;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))currFrame = 0;
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		currFrame++;
		if (currFrame > 1 && titleTimer % 100 == 0)
		{
			currFrame = 0;
		}
		pos.y -= moveSpeed;
		/*RotateBarrel(90);*/
		barrelAngle = DegToRad(90);
		fireAngle = 90;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))currFrame = 4;
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		currFrame++;
		if (currFrame > 5 && titleTimer % 100 == 0)
		{
			currFrame = 4;
		}
		pos.y += moveSpeed;
		/*RotateBarrel(-180);*/
		barrelAngle = DegToRad(-90);
		fireAngle = -90;
	}
}

void Tank::Fire()
{
	// 미사일 발사
	// 상태만 변경
	//if()
	//for (int i = 0; i < missileCount; i++)
	//{
	//	if (missile[i].GetIsFired() == false)
	//	{
	//		missile[i].SetType(Missile::TYPE::Normal);
	//		missile[i].SetPos(barrelEnd);
	//		missile[i].SetIsFired(true);
	//		missile[i].SetAngle(barrelAngle);

	//		break;
	//	}
	//}
}

void Tank::FireSkill_01()
{
	// 1. 미사일을 36발을 쏘고 일정 높이 이상 올라가면 36방향으로 퍼지게 한다.
	//int firedCount = 0;
	//for (int i = 0; i < missileCount; i++)
	//{
	//	if (firedCount < 36 && missile[i].GetIsFired() == false)
	//	{
	//		missile[i].SetType(Missile::TYPE::Skill_01);
	//		missile[i].SetPos(barrelEnd);
	//		missile[i].SetIsFired(true,pos);
	//		missile[i].SetAngle(barrelAngle/* + (firedCount * 0.05f)*/);
	//		missile[i].SetFireIndex(firedCount);

	//		firedCount++;
	//	}
	//}

	// 2. 미사일을 한발 쏘고 일정 높이 이상 올라가면 36발을 호출한다.
}

void Tank::FireFollowTarget(Enemy* target)
{
	//for (int i = 0; i < missileCount; i++)
	//{
	//	if (missile[i].GetIsFired() == false)
	//	{
	//		missile[i].SetType(Missile::TYPE::FollowTarget);
	//		missile[i].SetPos(barrelEnd);
	//		missile[i].SetIsFired(true, pos);
	//		missile[i].SetAngle(barrelAngle);
	//		missile[i].SetTarget(target);

	//		break;
	//	}
	//}
}

void Tank::Dead()
{
}
