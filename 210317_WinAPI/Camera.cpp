#include "Camera.h"
#include "CameraTarget.h"

HRESULT Camera::Init(FPOINT& pos, POINT& size, POINT& worldSize)
{
	this->pos = pos;
	this->cliSize = size;
	this->worldSize = worldSize;
	pivot.x = 0.5f;
	pivot.y = 0.5f;	
	originPos = this->pos;
	return S_OK;
}


void Camera::Release()
{
	//SAFE_RELEASE(this->target);
}

void Camera::Update()
{
	if (target)
	{		
		FPOINT playerPos = target->GetPos();//플레이어 포스
		//FPOINT fPivot = target->GetPivot();
		//POINT size;
		//size.x = WINSIZE_X*5;//월드 좌표
		//size.y = WINSIZE_Y*5;
		RECT screenRECT;
		screenRECT.left = playerPos.x - WINSIZE_X / 2;
		screenRECT.right = playerPos.x + WINSIZE_X / 2;
		screenRECT.top = playerPos.y - WINSIZE_Y / 2;
		screenRECT.bottom = playerPos.y - WINSIZE_Y / 2;
		//fRect.left = pos.x - pivot.x * size.x;
		//fRect.top = pos.y - pivot.y * size.y;
		//fRect.right = fRect.left + size.x;
		//fRect.bottom = fRect.top + size.y;

		//RECT outArea;
		//outArea.left = cliSize.x * pivot.x;
		//outArea.right = cliSize.x - outArea.left;
		//outArea.top = cliSize.y * pivot.y;
		//outArea.bottom = cliSize.y - outArea.top;

		//pos.x = (size.x - fPos.x);
		//pos.y = (size.y - fPos.y);
		/*if (fPos.x <= outArea.left)
		{
			pos.x = 0.0f;
		}
		else if (fPos.x >= worldSize.x - outArea.right)
		{
			pos.x = worldSize.x - cliSize.x;
		}
		else
		{
			pos.x = fPos.x - cliSize.x * pivot.x;
		}

		if (fPos.y <= outArea.top)
		{
			pos.x = 0.0f;
		}
		else if (fPos.y >= worldSize.y - outArea.bottom)
		{
			pos.y = worldSize.y - cliSize.y;
		}
		else
		{
			pos.y = fPos.y - cliSize.y * pivot.y;
		}*/
		//pos.x = playerPos.x;//카메라 좌표
		//pos.y = playerPos.y;	
		//srand(time(NULL));
		//
		//int x = rand() % 50 + 25;
		//int y = rand() % 50 + 25;
		//if (shakeTime>0)
		//{		
		//	shakeTime -= TimerManager::GetSingleton()->GetElapsedTime();
		//	pos.x = screenRECT.left+ x;
		//	pos.y = screenRECT.top + y;
		//}
		//else
		//{
			pos.x = screenRECT.left;
			pos.y = screenRECT.top;
		//}
		//
		//if (isCameraShake)
		//{
		//	shakeTime = 1.0f;
		//	isCameraShake = false;
		//}
		
		//1pos.y000 - 500 = 500 
		// 스크린 사이즈 = 100
	}
	
}


void Camera::Shake(float _amount, float _duration)
{
	FPOINT playerPos = target->GetPos();//플레이어 포스                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
	RECT screenRECT;
	screenRECT.left = playerPos.x - WINSIZE_X / 2;
	screenRECT.right = playerPos.x + WINSIZE_X / 2;
	screenRECT.top = playerPos.y - WINSIZE_Y / 2;
	screenRECT.bottom = playerPos.y - WINSIZE_Y / 2;
	float timer = 0;
	while (timer <= _duration)
	{
		this->pos.x = screenRECT.left + (rand()%50) * _amount + originPos.x;
		this->pos.y = screenRECT.left + (rand() % 50) * _amount + originPos.y;
		timer += TimerManager::GetSingleton()->GetElapsedTime();
	}
	pos = originPos;
}

void Camera::SetTarget(CameraTarget* mTarget)
{
	//SAFE_RELEASE(this->target);

	this->target = mTarget;

	if (target)
	{
		
	}
}

Camera::Camera()
{
	target = nullptr;
}

Camera::~Camera()
{
}

