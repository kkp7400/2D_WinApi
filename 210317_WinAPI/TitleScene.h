#pragma once
#include "GameNode.h"

class Button;
class Image;
class TitleScene:public GameNode
{
private:
	Image* titleImage;
	POINT pos;
	int selectMode;
	Image* logo;
	Image* start;
	int currFrame;
	int titleTimer;
	int tankPosY;
public:

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	POINT GetPos() { return this->pos; }

	virtual ~TitleScene() {};
};

