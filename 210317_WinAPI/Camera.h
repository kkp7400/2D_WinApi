#pragma once
#include "GameNode.h"
#include "config.h"
#include "Singleton.h"

class CameraTarget;
class Camera : public Singleton<Camera>
{
private:
	FPOINT pos;
	FPOINT originPos;
	POINT cliSize;
	POINT worldSize;
	FPOINT pivot;
	CameraTarget* target;
	RECT fRect;
	bool isCameraShake = false;
	float shakeTime;
public:	
	HRESULT Init(FPOINT& pos, POINT& size, POINT& worldSize);
	void Release();
	void Update(/*float fDeltaTime*/);
	void Render(HDC hdc);

	void Input(float fDeltaTime);
	void Shake(float _amount, float _duration);
	void SetTarget(CameraTarget* mTarget);

	void SetPivot(FPOINT& pivot) { this->pivot = pivot; }
	void SetPivot(float x, float y) { this->pivot.x = x; this->pivot.y = y; }

	void SetShake(bool a) { isCameraShake = a; }

	void SetPos(FPOINT& pos) { this->pos = pos; }
	void SetPos(float x, float y) { this->pos.x = x; this->pos.y = y; }

	void SetSize(POINT& size) { this->cliSize = size; }
	void SetSize(int x, int y) { this->cliSize.x = x; this->cliSize.y = y; }

	void SetWorldSize(POINT& worldSize) { this->worldSize = worldSize; }
	void SetWorldSize(int x, int y) { this->worldSize.x = x; this->worldSize.y = y; }

	FPOINT GetPos() { return pos; }

	RECT GetRect() { return fRect; }
	Camera();
	~Camera();
};

