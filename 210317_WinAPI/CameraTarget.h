#pragma once
#include "GameNode.h"

class CameraTarget: public GameNode
{
protected:
	FPOINT pos;
	FPOINT pivot;
	POINT targetSize;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	FPOINT GetPos() { return pos; }
	FPOINT GetPivot() { return pivot; }
};

