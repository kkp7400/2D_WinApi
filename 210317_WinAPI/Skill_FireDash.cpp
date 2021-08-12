#include "Skill_FireDash.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Camera.h"

HRESULT Skill_FireDash::Init(Player* player)
{

	ImageManager::GetSingleton()->AddImage("파이어대쉬", "Image/WOL/player/FireDash.bmp", 4096, 128, 32, 1, true, RGB(255, 0, 255));
	fireDashImage = ImageManager::GetSingleton()->FindImage("파이어대쉬");//32	
	for (int i = 0; i < 5; i++)
	{
		dashTimer[i] = 0;
		isDashPos[i] = false;
		isDashFX[i] = false;
		dashPos[i].x = 0;
		dashPos[i].y = 0;
		dashCurrFrameX[i] = 0;
	}
	clientPos.x = 0;
	clientPos.y = 0;
	currFrame =  player->GetCurrFrame();
	moveSpeed =  player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();
	isFire = true;
	coolTime = 0.0f;
	atkCol.resize(5);
	for (int i = 0; i < 5; i++)
	{		
		atkCol[i] = GetRectToCenter(-700, -700, 0, 0);
	}
	
    return S_OK;
}

void Skill_FireDash::Release()
{
}

void Skill_FireDash::Update(Player* player)
{
	//if(!isFire&&coolTime>=0) coolTime -= TimerManager::GetSingleton()->GetElapsedTime();
	for (int i = 0; i < 5; i++)//대쉬 상태가 아니게 되어도 계속 재생해야하니까 업데이트에 있다.
	{
		dashTimer[i] += TimerManager::GetSingleton()->GetElapsedTime();
		if (isDashFX[i])
		{
			if (dashTimer[i] > 0.05f)
			{
				dashTimer[i] = 0.0f;
				dashCurrFrameX[i]++;
				if (dashCurrFrameX[i] >= 32)
				{
					dashCurrFrameX[i] = 0;
					isDashFX[i] = false;
				}
			}
		}
	}
	if(coolTime >= 0.0f)  coolTime -= TimerManager::GetSingleton()->GetElapsedTime();
	currFrame = player->GetCurrFrame();
	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();	
	
}

void Skill_FireDash::Render(HDC hdc, Player* player)
{
	//for (int i = 0; i < 5; i++)
	//	Rectangle(hdc, atkCol[i].left - Camera::GetSingleton()->GetPos().x,
	//		atkCol[i].top - Camera::GetSingleton()->GetPos().y,
	//		atkCol[i].right - Camera::GetSingleton()->GetPos().x,
	//		atkCol[i].bottom - Camera::GetSingleton()->GetPos().y);
	for (int i = 0; i < 5; i++)
	{
		if (isDashFX[i])
		{
			clientPos.x = dashPos[i].x - Camera::GetSingleton()->GetPos().x;
			clientPos.y = dashPos[i].y - Camera::GetSingleton()->GetPos().y;
			fireDashImage->FrameRender(hdc, clientPos.x, clientPos.y, dashCurrFrameX[i], 0, true);
			atkCol[i] = GetRectToCenter((int)dashPos[i].x, (int)dashPos[i].y, 45, 80);
		}
		else
		{
			atkCol[i] = GetRectToCenter(-700, -700, 0, 0);
		}
	}
}
void Skill_FireDash::Skill(Player* player)
{
	int maxDashSpeed = 2000;
	//불꽃돌격	
	if (player->GetDirState() == Player::DirState::RIGHT)
	{
		if (!isDashStop && moveSpeed <= maxDashSpeed)
		{
			moveSpeed += 10000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (isDashStop)
		{
			moveSpeed -= 30000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 7;
		for (int i = 0; i < 5; i++)
		{
			if (moveSpeed >= ((i * (maxDashSpeed / 6)) + maxDashSpeed / 6))
			{
				isDashPos[i] = true;
				isDashFX[i] = true;
			}
		}
		if (!isDashStop && moveSpeed <= (maxDashSpeed / 6))
		{
			currFrame.x = 0;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 2)
		{
			currFrame.x = 1;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 3)
		{
			currFrame.x = 2;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 4)
		{
			currFrame.x = 3;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 5)
		{
			currFrame.x = 4;
		}
		else if (!isDashStop && moveSpeed >= (maxDashSpeed / 6) * 6)
		{
			currFrame.x = 5;
			isDashStop = true;
		}
		else if (isDashStop && moveSpeed >= maxDashSpeed / 2)
		{
			currFrame.x = 6;
		}
		if (isDashStop && moveSpeed >= 0)
		{
			currFrame.x = 7;
		}
		else if (isDashStop && moveSpeed <= 0)
		{
			player->SetState(Player::State::IDLE);
			moveSpeed = 0;
			isDashStop = false;
			coolTime = 5.0f;
		}
	}
	if (player->GetDirState() == Player::DirState::LEFT)
	{
		if (!isDashStop && moveSpeed <= maxDashSpeed)
		{
			moveSpeed += 10000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (isDashStop)
		{
			moveSpeed -= 30000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 8;
		for (int i = 0; i < 5; i++)
		{
			if (moveSpeed >= ((i * (maxDashSpeed / 6)) + maxDashSpeed / 6))
			{
				isDashPos[i] = true;
				isDashFX[i] = true;
			}
		}
		if (!isDashStop && moveSpeed <= (maxDashSpeed / 6))
		{
			currFrame.x = 0;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 2)
		{
			currFrame.x = 1;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 3)
		{
			currFrame.x = 2;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 4)
		{
			currFrame.x = 3;
		}
		else if (!isDashStop && moveSpeed <= (maxDashSpeed / 6) * 5)
		{
			currFrame.x = 4;
		}
		else if (!isDashStop && moveSpeed >= (maxDashSpeed / 6) * 6)
		{
			currFrame.x = 5;
			isDashStop = true;
		}
		else if (isDashStop && moveSpeed >= maxDashSpeed / 2)
		{
			currFrame.x = 6;
		}
		if (isDashStop && moveSpeed >= 0)
		{
			currFrame.x = 7;
		}
		else if (isDashStop && moveSpeed <= 0)
		{
			player->SetState(Player::State::IDLE);
			moveSpeed = 0;
			isDashStop = false;
			coolTime = 5.0f;
		}
	}
	if (player->GetDirState() == Player::DirState::TOP)
	{
		if (!isDashStop && moveSpeed <= maxDashSpeed)
		{
			moveSpeed += 10000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (isDashStop)
		{
			moveSpeed -= 30000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 18;
		for (int i = 0; i < 5; i++)
		{
			if (moveSpeed >= ((i * (maxDashSpeed / 6)) + maxDashSpeed / 6))
			{
				isDashPos[i] = true;
				isDashFX[i] = true;
			}
		}
		if (!isDashStop && moveSpeed <= (maxDashSpeed / 2))
		{
			currFrame.x = 0;
		}
		else if (!isDashStop && moveSpeed >= (maxDashSpeed / 2) * 2)
		{
			currFrame.x = 1;
			isDashStop = true;
			coolTime = 5.0f;

		}
		if (isDashStop && moveSpeed >= 0)
		{
			currFrame.x = 2;

		}
		else if (isDashStop && moveSpeed <= 0)
		{
			player->SetState(Player::State::IDLE);
			moveSpeed = 0;
			isDashStop = false;
			coolTime = 5.0f;
		}
		//---------------------------------------------------------------
		//if (!isDashStop && moveSpeed <= 3000)
		//{
		//	moveSpeed += 100;
		//}
		//else if (isDashStop)
		//{
		//	moveSpeed -= 300;
		//}
		//pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		//currFrame.y = 18;
		//if (!isDashStop && moveSpeed <= 1500)
		//{
		//	currFrame.x = 0;
		//}
		//else if (!isDashStop && moveSpeed <= 3000)
		//{
		//	currFrame.x = 1;
		//	isDashStop = true;
		//}
		//if (isDashStop && moveSpeed >= 0)
		//{
		//	currFrame.x = 2;
		//}
		//else if (isDashStop && moveSpeed <= 0)
		//{
		//	state = State::IDLE;
		//	moveSpeed = 0;
		//	isDashStop = false;
		//}

	}
	if (player->GetDirState() == Player::DirState::BOTTOM)
	{
		if (!isDashStop && moveSpeed <= maxDashSpeed)
		{
			moveSpeed += 10000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (isDashStop)
		{
			moveSpeed -= 30000 * TimerManager::GetSingleton()->GetElapsedTime();
		}
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 18;
		for (int i = 0; i < 5; i++)
		{
			if (moveSpeed >= ((i * (maxDashSpeed / 6)) + maxDashSpeed / 6))
			{
				isDashPos[i] = true;
				isDashFX[i] = true;
			}
		}
		if (!isDashStop && moveSpeed <= (maxDashSpeed / 2))
		{
			currFrame.x = 3;
		}
		else if (!isDashStop && moveSpeed >= (maxDashSpeed / 2) * 2)
		{
			currFrame.x = 4;
			isDashStop = true;

		}
		if (isDashStop && moveSpeed >= 0)
		{
			currFrame.x = 5;

		}
		else if (isDashStop && moveSpeed <= 0)
		{
			player->SetState(Player::State::IDLE);
			moveSpeed = 0;
			isDashStop = false;
			coolTime = 5.0f;
		}
		//-------------------------------------------------------------------------------
		/*if (!isDashStop && moveSpeed <= 3000)
		{
			moveSpeed += 100;
		}
		else if (isDashStop)
		{
			moveSpeed -= 300;
		}
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		currFrame.y = 18;
		if (!isDashStop && moveSpeed <= 1500)
		{
			currFrame.x = 3;
		}
		else if (!isDashStop && moveSpeed <= 3000)
		{
			currFrame.x = 4;
			isDashStop = true;
		}
		if (isDashStop && moveSpeed >= 0)
		{
			currFrame.x = 5;
		}
		else if (isDashStop && moveSpeed <= 0)
		{
			state = State::IDLE;
			moveSpeed = 0;
			isDashStop = false;
		}*/

	}
	for (int i = 0; i < 5; i++)
	{
		if (isDashPos[i])
		{
			switch (player->GetDirState())
			{
			case Player::DirState::LEFT:
				dashPos[i].x = pos.x + (i * 20);
				dashPos[i].y = pos.y;
				isDashPos[i] = false;
				break;
			case Player::DirState::RIGHT:
				dashPos[i].x = pos.x - (i * 20);
				dashPos[i].y = pos.y;
				isDashPos[i] = false;
				break;
			case Player::DirState::TOP:
				dashPos[i].x = pos.x;
				dashPos[i].y = pos.y + (i * 20);
				isDashPos[i] = false;
				break;
			case Player::DirState::BOTTOM:
				dashPos[i].x = pos.x;
				dashPos[i].y = pos.y - (i * 20);
				isDashPos[i] = false;
				break;
			default:
				break;
			}
		}
	}
	isFire = false;

	player->SetCurrFrame(currFrame);
	player->SetMoveSpeed(moveSpeed);
	player->SetPos(pos);
	player->SetMoveFrameSpeed(moveframespeed);	
}