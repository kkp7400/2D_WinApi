#include "Player.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Camera.h"
#include "SkillManager.h"
#include "Skill_FireDash.h"
#include "Skill_WindAttack.h"
#include "Skill_RockThrow.h"
#include "Skill_Dash.h"
#include "Skill_IceCrystal.h"
#include "Skill_Ice.h"
HRESULT Player::Init()
{
	ImageManager::GetSingleton()->AddImage("플레이어", "Image/WOL/player/player.bmp", 1700 * 0.7, 4080 * 0.7, 10, 24, true, RGB(255, 0, 255));
	playerImage = ImageManager::GetSingleton()->FindImage("플레이어");
	//ImageManager::GetSingleton()->AddImage("파이어대쉬", "Image/WOL/player/FireDash.bmp", 4096, 128, 32, 1, true, RGB(255, 0, 255));
	//fireDashImage = ImageManager::GetSingleton()->FindImage("파이어대쉬");//32
	skillMgr.resize(5);
	for (int i = 0; i < 5; i++)
	{
		dashTimer[i] = 0;
		isDashPos[i] = false;
		isDashFX[i] = false;
		dashPos[i].x = 0;
		dashPos[i].y = 0;
		dashCurrFrameX[i] = 0;
	}
	mAngle = 0;
	pos.x = WORLDSIZE_X / 2;
	pos.y = WORLDSIZE_Y / 2;
	moveCol.left = pos.x - 20;
	moveCol.right = pos.x + 20;
	moveCol.top = pos.y + 25;
	moveCol.bottom = pos.y + 45;
	skillIndex.resize(5);
	moveSpeed = 300.0f;
	critPer = 10.0f;
	maxHP = 100000.0f / 2;
	nowHP = 100000.0f / 2;
	atk = 40.0;
	state = State::IDLE;
	dirState = DirState::BOTTOM;
	isAlive = true;
	elapsedTime = 0.0f;
	runTimer = 0.0f;
	moveFrameSpeed = 7.0f;
	pivot.x = 0.5f;
	pivot.y = 0.5f;
	size.x = 119;
	size.y = 119;
	isDashStop = false;
	currFrame.x = 0;
	currFrame.y = 0;
	mDir = MDir::하단;
	skillMgr[0] = new Skill_FireDash();
	skillMgr[0]->Init(this);
	skillMgr[1] = new Skill_WindAttack();
	skillMgr[1]->Init(this);
	skillMgr[2] = new Skill_RockThrow();
	skillMgr[2]->Init(this);
	skillMgr[3] = new Skill_Dash();
	skillMgr[3]->Init(this);
	skillMgr[4] = new Skill_Ice();
	skillMgr[4]->Init(this);
	fMouse = { 0,0 };
	atkDir = true;
	atkCount = 1;
	hitCol.left = pos.x - 25;
	hitCol.right = pos.x + 25;
	hitCol.top = pos.y - 50;
	hitCol.bottom = pos.y + 50;
	for (int i = 0; i < 4; i++)
	{
		coolTime[i] = 0.0f;
	}
	//hitTime
	return S_OK;
}

void Player::Release()
{

}

void Player::Update()
{
	if (nowHP <= 0) state = State::DIE;
	if (state != State::DIE);
	{
		hitCol.left = pos.x - 25;
		hitCol.right = pos.x + 25;
		hitCol.top = pos.y - 50;
		hitCol.bottom = pos.y + 50;
		moveCol.left = pos.x - 20;
		moveCol.right = pos.x + 20;
		moveCol.top = pos.y + 25;
		moveCol.bottom = pos.y + 45;
		/*Camera::GetSingleton()->SetPos(pos);
		Camera::GetSingleton()->SetPivot(pivot);
		Camera::GetSingleton()->SetSize(size);*/
		Camera::GetSingleton()->SetTarget(this);
		fMouse.x = g_ptMouse.x;
		fMouse.y = g_ptMouse.y;
		//if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
		mAngle = GetAngle(clientPos, fMouse) * 180 / PI;
		if (mAngle < 0)	mAngle += 360;

		if (mAngle > 337.5 || mAngle <= 22.5) mDir = MDir::우단;
		if (mAngle > 22.5 && mAngle <= 67.5) mDir = MDir::우상단;
		if (mAngle > 67.5 && mAngle <= 112.5) mDir = MDir::상단;
		if (mAngle > 112.5 && mAngle <= 157.5) mDir = MDir::좌상단;
		if (mAngle > 157.5 && mAngle <= 202.5) mDir = MDir::좌단;
		if (mAngle > 202.5 && mAngle <= 247.5) mDir = MDir::좌하단;
		if (mAngle > 247.5 && mAngle <= 292.5) mDir = MDir::하단;
		if (mAngle > 292.5 && mAngle <= 337.5) 	mDir = MDir::우하단;

		targetSize.x = size.x;
		targetSize.y = size.y;
		//clientPos.x = Camera::GetSingleton()->GetPos().x + WINSIZE_X / 2;
		//clientPos.y = Camera::GetSingleton()->GetPos().y + WINSIZE_Y / 2;
		elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();

		if (state != State::RUNEND && state != State::HIT && state != State::DASH && state != State::ATTACK && state != State::SKILL1 && state != State::SKILL2)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown('W') || KeyManager::GetSingleton()->IsOnceKeyDown('A') ||
				KeyManager::GetSingleton()->IsOnceKeyDown('S') || KeyManager::GetSingleton()->IsOnceKeyDown('D'))
			{
				state = State::MOVE;
			}
		}
		if (state != State::SKILL1 && state != State::HIT && state != State::DASH && state != State::SKILL2)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
			{
				state = State::DASH;
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('H'))
		{
			state = State::HIT;
		}


		if ((state != State::SKILL1 && state != State::HIT && state != State::DASH && state != State::ATTACK && state != State::SKILL2))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				skillMgr[1]->Skill(this);
				moveFrameSpeed = 5;
				currFrame.x = 0;
				state = State::ATTACK;
				if (mAngle > 315 || mAngle <= 45)
				{
					dirState = DirState::RIGHT;//우 
				}
				else if (mAngle > 45 && mAngle <= 135)
				{
					dirState = DirState::TOP;//위
				}
				else if (mAngle > 135 && mAngle <= 225)
				{
					dirState = DirState::LEFT;//좌
					currFrame.x = 8;
				}
				else if (mAngle > 225 && mAngle <= 315)
				{
					dirState = DirState::BOTTOM;//하
				}
				if (atkDir) atkDir = false;
				else atkDir = true;
			}
		}
		if (state == State::IDLE || state == State::MOVE)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RBUTTON) && skillMgr[2]->GetCoolTime() <= 0)
			{
				skillMgr[2]->Skill(this);
				moveFrameSpeed = 10;
				currFrame.x = 0;
				state = State::SKILL1;
				if (mAngle > 315 || mAngle <= 45)
				{
					dirState = DirState::RIGHT;//우 
					currFrame.x = 0;
				}
				else if (mAngle > 45 && mAngle <= 135)
				{
					dirState = DirState::TOP;//위
					currFrame.x = 0;
				}
				else if (mAngle > 135 && mAngle <= 225)
				{
					dirState = DirState::LEFT;//좌
					currFrame.x = 9;
				}
				else if (mAngle > 225 && mAngle <= 315)
				{
					dirState = DirState::BOTTOM;//하
					currFrame.x = 0;
				}
			}
		}
		if (state == State::IDLE || state == State::MOVE)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown('Q') && skillMgr[4]->GetCoolTime() <= 0)
			{
				skillMgr[4]->Skill(this);
				moveFrameSpeed = 10;
				currFrame.x = 0;
				state = State::SKILL2;
				if (mAngle > 315 || mAngle <= 45)
				{
					dirState = DirState::RIGHT;//우 
					currFrame.x = 0;
				}
				else if (mAngle > 45 && mAngle <= 135)
				{
					dirState = DirState::TOP;//위
					currFrame.x = 0;
				}
				else if (mAngle > 135 && mAngle <= 225)
				{
					dirState = DirState::LEFT;//좌
					currFrame.x = 9;
				}
				else if (mAngle > 225 && mAngle <= 315)
				{
					dirState = DirState::BOTTOM;//하
					currFrame.x = 0;
				}
			}
		}
		for (int i = 0; i < skillMgr.size(); i++)
		{
			skillMgr[i]->Update(this);
		}
	}
	if (isHit)
	{
		state = State::HIT;		
		isHit = false;
	}
	if(state != State::END)
	switch (state)
	{
	case Player::State::IDLE:
		Idle();
		break;
	case Player::State::MOVE:
		Move();
		break;
	case Player::State::HIT:
		Hit();
		break;
	case Player::State::DASH:
		Dash();
		break;
	case Player::State::RUNEND:
		Run();
		break;
	case Player::State::ATTACK:
		Attack();
		break;
	case Player::State::SKILL1:
		Skill1();
	case Player::State::SKILL2:
		Skill2();
		break;
	case Player::State::DIE:
		Die();
		break;	
	}
	
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		nowHP -= 100;
	}

}

void Player::Render(HDC hdc)
{
	if (state != State::END)
	{
		clientPos.x = pos.x - Camera::GetSingleton()->GetPos().x;
		clientPos.y = pos.y - Camera::GetSingleton()->GetPos().y;
		/*Rectangle(hdc, moveCol.left - Camera::GetSingleton()->GetPos().x, moveCol.top - Camera::GetSingleton()->GetPos().y,
			moveCol.right - Camera::GetSingleton()->GetPos().x, moveCol.bottom - Camera::GetSingleton()->GetPos().y);
		Rectangle(hdc, hitCol.left - Camera::GetSingleton()->GetPos().x, hitCol.top - Camera::GetSingleton()->GetPos().y,
			hitCol.right - Camera::GetSingleton()->GetPos().x, hitCol.bottom - Camera::GetSingleton()->GetPos().y);*/
		if (dirState == DirState::BOTTOM)
		{
			skillMgr[0]->Render(hdc, this);
		}
		if (mDir == MDir::상단 || mDir == MDir::우상단 || mDir == MDir::좌상단)
		{

			skillMgr[3]->Render(hdc, this);
			skillMgr[4]->Render(hdc, this);
		}
		if (mDir != MDir::상단 & mDir != MDir::우상단 && mDir != MDir::좌상단)		skillMgr[2]->Render(hdc, this);
		playerImage->FrameRender(hdc, clientPos.x, clientPos.y, currFrame.x, currFrame.y, true);
		if (dirState != DirState::BOTTOM)
		{
			skillMgr[0]->Render(hdc, this);
		}
		if (mDir != MDir::상단 & mDir != MDir::우상단 && mDir != MDir::좌상단)
		{
			skillMgr[3]->Render(hdc, this);
			skillMgr[4]->Render(hdc, this);
		}
		if (mDir == MDir::상단 || mDir == MDir::우상단 || mDir == MDir::좌상단)skillMgr[2]->Render(hdc, this);
		skillMgr[1]->Render(hdc, this);
		//wsprintf(szText, "커렌X: %d", currFrame.x);
		//TextOut(hdc, 400, 20, szText, strlen(szText));

		//wsprintf(szText, "스테이트: %d", state);
		//TextOut(hdc, 600, 20, szText, strlen(szText));

		/*wsprintf(szText, "카메라X: %d, 카메라X: %d", Camera::GetSingleton()->GetPos().x, Camera::GetSingleton()->GetPos().y);
		TextOut(hdc, 800, 40, szText, strlen(szText));

		wsprintf(szText, "플레이어X: %d, 플레이어X: %d", (int)pos.x, (int)pos.y);
		TextOut(hdc, 800, 40, szText, strlen(szText));*/

		//wsprintf(szText, "fireCool: %d", (int)skillMgr[0]->GetCoolTime());
		//TextOut(hdc, 1000, 20, szText, strlen(szText));


	//	wsprintf(szText, "nowHP: %d", (int)nowHP);
		//TextOut(hdc, 1000, 80, szText, strlen(szText));

		//wsprintf(szText, "atkCount: %d", atkCount);
		//TextOut(hdc, clientPos.x, clientPos.y-30, szText, strlen(szText));
	}
}

void Player::Idle()
{
	currFrame.y = 0;
	moveFrameSpeed = 7.0f;
	moveSpeed = 170.0f;
	runTimer = 0.0f;
	if (dirState == DirState::LEFT)
		currFrame.x = 3;
	if (dirState == DirState::RIGHT)
		currFrame.x = 2;
	if (dirState == DirState::TOP)
		currFrame.x = 1;
	if (dirState == DirState::BOTTOM)
		currFrame.x = 0;

}

void Player::Move()
{
	if (state == State::MOVE)
	{
		runTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (runTimer <= 2.0f)
		{
			moveFrameSpeed = 7.0f;
			moveSpeed = 500.0f;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('A') && KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		state = State::MOVE;
		//	elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 4;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x--;
			if (currFrame.x <= 0)
			{
				currFrame.x = 9;
			}
			elapsedTime = 0.0f;
		}
		dirState = DirState::LEFT;
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown('A') && KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		state = State::MOVE;
		//	elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 4;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x--;
			if (currFrame.x <= 0)
			{
				currFrame.x = 9;
			}
			elapsedTime = 0.0f;
		}
		dirState = DirState::LEFT;
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown('D') && KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		state = State::MOVE;
		//	elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 3;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 9)
			{
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}
		dirState = DirState::RIGHT;
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown('D') && KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		state = State::MOVE;
		//	elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 3;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 9)
			{
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}
		dirState = DirState::RIGHT;
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
		{
			state = State::MOVE;

			currFrame.y = 2;
			if (elapsedTime > moveFrameSpeed)
			{
				currFrame.x++;
				if (currFrame.x >= 9)
				{
					currFrame.x = 0;
				}
				elapsedTime = 0;
			}

			dirState = DirState::TOP;
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			state = State::MOVE;
			//	elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
			currFrame.y = 4;
			if (elapsedTime > moveFrameSpeed)
			{
				currFrame.x--;
				if (currFrame.x <= 0)
				{
					currFrame.x = 9;
				}
				elapsedTime = 0.0f;
			}
			dirState = DirState::LEFT;
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
		{
			//state = State::MOVE;
		//	elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
			currFrame.y = 1;
			if (elapsedTime > moveFrameSpeed)
			{
				currFrame.x++;
				if (currFrame.x >= 9)
				{
					currFrame.x = 0;
				}
				elapsedTime = 0.0f;
			}
			dirState = DirState::BOTTOM;
			pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			//state = State::MOVE;
			//elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
			currFrame.y = 3;
			if (elapsedTime > moveFrameSpeed)
			{
				currFrame.x++;
				if (currFrame.x >= 9)
				{
					currFrame.x = 0;
				}
				elapsedTime = 0.0f;
			}
			dirState = DirState::RIGHT;
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else
		{
			currFrame.x = 0;
			if (runTimer > 2.0f)
			{
				if (dirState == DirState::BOTTOM)
				{
					currFrame.x = 3;
				}
				if (dirState == DirState::LEFT) currFrame.x = 7;
				state = State::RUNEND;
				runTimer = 0;
			}
			else
				state = State::IDLE;
		}
	}

	if (runTimer > 2.0f)
	{
		moveFrameSpeed = 4.0f;
		moveSpeed = 800.0f;
	}
}

void Player::Run()
{
	moveFrameSpeed = 4.0f;
	if (moveSpeed >= 0)
		moveSpeed -= 1;
	if (dirState == DirState::RIGHT)
	{
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 7;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 7)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::LEFT)
	{
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 8;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x--;
			if (currFrame.x <= 0)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::TOP)
	{
		moveFrameSpeed = 10.0f;
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 18;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 2)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::BOTTOM)
	{
		moveFrameSpeed = 10.0f;
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 18;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 5)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
}

void Player::Hit()
{
	moveSpeed = 0.05;
	if (elapsedTime > 100.0f)
	{
		elapsedTime = 0;
	}
	if (hitDir == "Top")
	{
		currFrame.y = 0;
		currFrame.x = 5;
		if (moveSpeed >= 0.03)
			moveSpeed -= 0.03;
		pos.y += moveSpeed * elapsedTime;
	}
	if (hitDir == "Bottom")
	{
		currFrame.y = 0;
		currFrame.x = 4;
		if (moveSpeed >= 0.03)
			moveSpeed -= 0.03;
		pos.y -= moveSpeed * elapsedTime;
	}
	if (hitDir == "Left")
	{
		currFrame.y = 0;
		currFrame.x = 6;
		if (moveSpeed >= 0.03)
			moveSpeed -= 0.03;
		pos.x += moveSpeed * elapsedTime;
	}
	if (hitDir == "Right")
	{
		currFrame.y = 0;
		currFrame.x = 7;
		if (moveSpeed >= 0.03)
			moveSpeed -= 0.03;
		pos.x -= moveSpeed * elapsedTime;
	}
	if (elapsedTime > 50)
	{
		state = State::IDLE;
	}
}

void Player::Dash()
{
	if (skillMgr[0]->GetCoolTime() <= 0)
		skillMgr[0]->Skill(this);
	else skillMgr[3]->Skill(this);
}

void Player::Attack()
{
	//if (atkCount >= 5)
	//{
	//	atkCount = 0;
	//}

	if (dirState == DirState::RIGHT)//우
	{
		//	moveFrameSpeed = 8.0f;
			//dirState = DirState::RIGHT;
			//pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 12;//라이트
		if (elapsedTime > moveFrameSpeed)
		{

			currFrame.x++;
			if (currFrame.x >= 7)
			{
				state = State::IDLE;

			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::TOP)//위
	{

		//pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		if (atkDir)
			currFrame.y = 11;
		else
			currFrame.y = 17;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 9)
			{
				state = State::IDLE;
				/*	if (atkCount == 0)
					atkCount = 1;*/
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::LEFT)//좌
	{
		//	moveFrameSpeed = 8.0f;
		currFrame.y = 13;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x--;
			if (currFrame.x <= 0)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::BOTTOM)//하
	{
		//moveFrameSpeed = 10.0f;
		//pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		if (atkDir)
			currFrame.y = 6;
		else
			currFrame.y = 5;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 7)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
}

void Player::Skill1()
{
	if (dirState == DirState::RIGHT)//우
	{
		currFrame.y = 15;//라이트
		if (elapsedTime > moveFrameSpeed)
		{

			currFrame.x++;
			if (currFrame.x >= 9)
			{
				state = State::IDLE;

			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::TOP)//위
	{
		//pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		currFrame.y = 19;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 9)
			{
				state = State::IDLE;
				/*	if (atkCount == 0)
					atkCount = 1;*/
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::LEFT)//좌
	{
		//	moveFrameSpeed = 8.0f;
		currFrame.y = 16;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x--;
			if (currFrame.x <= 0)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::BOTTOM)//하
	{
		//moveFrameSpeed = 10.0f;
		//pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		currFrame.y = 10;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 9)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	//스킬1 기절의 바위
}
void Player::Skill2()
{
	if (dirState == DirState::RIGHT)//우
	{
		currFrame.y = 15;//라이트
		if (elapsedTime > moveFrameSpeed)
		{

			currFrame.x++;
			if (currFrame.x >= 9)
			{
				state = State::IDLE;

			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::TOP)//위
	{
		//pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		currFrame.y = 19;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 9)
			{
				state = State::IDLE;
				/*	if (atkCount == 0)
					atkCount = 1;*/
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::LEFT)//좌
	{
		//	moveFrameSpeed = 8.0f;
		currFrame.y = 16;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x--;
			if (currFrame.x <= 0)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dirState == DirState::BOTTOM)//하
	{
		//moveFrameSpeed = 10.0f;
		//pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		currFrame.y = 10;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 9)
			{
				state = State::IDLE;
			}
			elapsedTime = 0.0f;
		}
	}
	//스킬3 표준 반사의 고드름
}
void Player::Die()
{
	//if (currFrame.x >= 10)currFrame.x = 0;
	
	currFrame.y = 9;
	if (elapsedTime > moveFrameSpeed)
	{
		currFrame.x++;
		if (currFrame.x >= 9)
		{
			state = State::END;
		}
		elapsedTime = 0.0f;
	}
	
}
vector<RECT>* Player::GetAtkCol(int i)
{
	return skillMgr[i]->GetAtkCol();
}
//그림자 나중에 엄청 나중에
