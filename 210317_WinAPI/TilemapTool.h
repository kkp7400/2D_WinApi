#pragma once
#include "CameraTarget.h"

// 샘플 타일 정보
// 640 * 288
#define SAMPLE_TILE_X	24
#define SAMPLE_TILE_Y	14
#define TILESIZE		40

// 메인 그리기 공간 정보
#define	TILE_X			20
#define	TILE_Y			20

class Button;
class Image;
class TilemapTool : public CameraTarget
{
private:
	// 샘플 타일 이미지
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;	
	
	// 메인타일의 정보
	static TILE_INFO tileInfo[TILE_X * TILE_Y];	

	FPOINT targetPos;
	FPOINT clientPos;
	RECT rcMain;
	RECT gridRc[TILE_X * TILE_Y];
	char szText[128] = "";
	char szText1[128] = "";
	char szText2[128] = "";
	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;
	TILEOPTION ptTileOption;

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;
	float zoomSize;
	HPEN hSelectedPen;
	HPEN hOldSelectedPen;

	// UI button
	Button* btnSave;
	Button* btnLoad;
	Button* btnNext;
	Button* btnBack;
	Button* btnTenNext;
	Button* btnTenBack;
	static int argNum;

	float tileSize;
	float imgSize;

	FPOINT screenPos;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void Save();
	static void Load();
	static void Next();
	static void Back();
	static void TenNext();
	static void TenBack();
	FPOINT GetPos() { return targetPos; }
	//void SetPos(FPOINT pos) { this->targetPos = pos; }
	virtual ~TilemapTool() {};
};

