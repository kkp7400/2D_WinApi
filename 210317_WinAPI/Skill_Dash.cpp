#include "Skill_Dash.h"
#include "CommonFunction.h"
#include "Camera.h"
HRESULT Skill_Dash::Init(Player* player)
{
	clientPos.x = 0;
	clientPos.y = 0;
	currFrame = player->GetCurrFrame();
	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();
	isFire = true;
	coolTime = 0.0f;
	return S_OK;
}

void Skill_Dash::Release()
{
}

void Skill_Dash::Update(Player* player)
{
	if (coolTime >= 0.0f)  coolTime -= TimerManager::GetSingleton()->GetElapsedTime();
	currFrame = player->GetCurrFrame();
	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();
}

void Skill_Dash::Render(HDC hdc, Player* player)
{
}

void Skill_Dash::Skill(Player* player)
{
	int maxDashSpeed = 2000;
	//ºÒ²Éµ¹°Ý	
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

		if (!isDashStop && moveSpeed <= (maxDashSpeed / 2))
		{
			currFrame.x = 0;
		}
		else if (!isDashStop && moveSpeed >= (maxDashSpeed / 2) * 2)
		{
			currFrame.x = 1;
			isDashStop = true;

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

	isFire = false;
	coolTime = 5.0f;
	player->SetCurrFrame(currFrame);
	player->SetMoveSpeed(moveSpeed);
	player->SetPos(pos);
	player->SetMoveFrameSpeed(moveframespeed);
}
