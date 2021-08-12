#pragma once
#include "GameNode.h"
#include "CameraTarget.h"
#define TILESIZE		40

// 메인 그리기 공간 정보
#define	TILE_X			20
#define	TILE_Y			20

class Image;
class CheckCollision;
class AstarScene;
class RandomMap : public CameraTarget
{
private:

	Image* stage;
	Image* stage2;
	Image* img;
	Image* bin;
	AstarScene* astar;
	static TILE_INFO tileInfo[TILE_X * TILE_Y];
	TILE_INFO randTile[10][TILE_X * TILE_Y];
	bool viewWorldMap;
	CheckCollision* checkAll;
	char szText[128];
	RECT rcMain;
	int phaseCount = 0;
	float zoomPoint = 0.2f;
	HBRUSH brush, oldBrush;
	PAINTSTRUCT ps;
	struct MAP
	{
		POINT pos;
		RECT rect;
		int sizeX;
		int sizeY;
		string dirV;
		string dirH;
		int index;		
		bool select;
	};
	struct SHOP
	{
		POINT pos;		
		int size;
		string dirV;
		string dirH;
		int index;
		bool select;
	};
	struct DOUBLEMAP
	{
		int a;
		int b;		
	};
	DOUBLEMAP dMap[30][30];
	vector<float>diffPointX;
	vector<float>diffPointY;
	vector<int>matchRC;
	vector<SHOP>vShop;
	vector<MAP>vMap;
	vector<RECT>compareRect;
	vector<RECT>compareRect2;
	vector<int>asIndex;

	int minRange;
	int maxSelect;
	int sizeX[30];
	int sizeY[30];	
	int testId;
	float zoomValue;
	bool phaseStart;
	bool phase1;
	bool phase2;
	bool phase3;
	bool phase4;
	bool phase5;
	bool phase6;
	bool phase7;
	bool phase8;
	bool phase9;
	bool phase10;
	bool isAstarOn;
	bool isViewAstar;
	bool isPhase9Break;
	
	RECT sibal;
	struct ENDTILEINDEX
	{
		int index;
		POINT endPos;
	};
	vector<ENDTILEINDEX>TotalTileIndex;
	vector<ENDTILEINDEX>endTile;
	vector<ENDTILEINDEX>startTile;
	vector<POINT>wayPos;
	vector<POINT>astarFrame;
	vector<TILEOPTION>astarType;

	POINT wayPos2[125][125];
	POINT astarFrame2[125][125];
	TILEOPTION astarType2[125][125];

	vector<TILE_INFO>creatRoad;
	vector<TILE_INFO>creatRoad2;
	vector<TILE_INFO>worldTile2;
	vector<vector<TILE_INFO>>worldTile;
	bool isWorldTile;
	bool isRandMapOK;
	vector<BATTLE_ZONE> battleZone;
	int randMapStep = 0;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void Load(int saveNum);

	inline TILE_INFO GetTileInfo() { return this->tileInfo[TILE_X * TILE_Y]; }
	inline void SetTileInfo(TILE_INFO tileInfo) { this->tileInfo[TILE_X * TILE_Y] = tileInfo; }
	
	bool GetIsRandMap() { return this->isRandMapOK; }
	
	vector<TILE_INFO>* GetMap() { return &creatRoad2; }
	vector<vector<TILE_INFO>>* GetMap2() { return &worldTile; }
	
	vector<BATTLE_ZONE>* GetMapRect();

	void CheckCollision();
	void CheckCollisionAS();
	void CheckCollisionAS2();
	void CheckCollisionAS3();
	void CheckCollisionAS4();
	void SelectMap();
	void CheckMap();
	void EraseMap();
	void AddShop();
	void FillTile();
	void farMap();
	void eraseRect();
	void RemewalRect();
	void MatchRect();
	void SetStart();
	void SetEnd();
	void SetEnd2();
	//3페이즈
	void RemainderTile();
	void addWall();

	float lineDistance(POINT a, POINT b);
	virtual ~RandomMap() {};
};



