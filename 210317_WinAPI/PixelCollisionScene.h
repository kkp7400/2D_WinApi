#pragma once
#include "GameNode.h"

class Image;
class PixelCollisionScene : public GameNode
{
private:
	Image* bg;
	Image* ball;

	FPOINT posBall;
	bool isLanding;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~PixelCollisionScene() {};
};

