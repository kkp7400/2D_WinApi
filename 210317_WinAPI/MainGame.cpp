#include "MainGame.h"
#include "Image.h"
#include "TilemapTool.h"
#include "BattleScene.h"
#include "AstarScene.h"
#include "LoadingScene.h"
#include "PixelCollisionScene.h"
#include "TitleScene.h"
#include "RandomMap.h"
#include "Camera.h"
HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);
	cameraInitPos.x = 0.0f;
	cameraInitPos.y = 0.0f;
	cameraInitSize.x = WINSIZE_X;
	cameraInitSize.y = WINSIZE_Y;
	initWorldCameraSize.x = cameraInitSize.x*5;
	initWorldCameraSize.y = cameraInitSize.y*5;
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	Camera::GetSingleton()->Init(cameraInitPos, cameraInitSize, initWorldCameraSize);
	// �̹����� �̸� �ε��Ѵ�
	ImageManager::GetSingleton()->AddImage("Enemy",
		"Image/ufo.bmp", 530, 32, 10, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("EnemyMissile",
		"Image/����.bmp", 20, 20, true, RGB(255, 0, 255));

	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// ����� �̹���
	int maxWidth, maxHeight;
	maxWidth = max(WINSIZE_X, TILEMAPTOOLSIZE_X);
	maxHeight = max(WINSIZE_Y, TILEMAPTOOLSIZE_Y);

	backBuffer = new Image();
	backBuffer->Init(maxWidth, maxHeight);
	SceneManager::GetSingleton()->AddScene("Ÿ��Ʋ��", new TitleScene());
	SceneManager::GetSingleton()->AddScene("����_1", new BattleScene());
	SceneManager::GetSingleton()->AddScene("Ÿ�ϸ���", new TilemapTool());
	SceneManager::GetSingleton()->AddScene("A*", new AstarScene());
	SceneManager::GetSingleton()->AddScene("�ȼ��浹", new PixelCollisionScene());
	SceneManager::GetSingleton()->AddScene("������", new RandomMap());
	SceneManager::GetSingleton()->AddLoadingScene("�ε���_1", new LoadingScene());
		

	SceneManager::GetSingleton()->ChangeScene("Ÿ��Ʋ��");

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();
	Camera::GetSingleton()->Release();
	SAFE_RELEASE(backBuffer);	
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
	Camera::GetSingleton()->Update();
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	SceneManager::GetSingleton()->Render(hBackDC);



	// �λ�
	//TextOut(hBackDC, 20, 20, "MainGame ���� ��", strlen("MainGame ���� ��"));
	// ���콺 ��ǥ
	//wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x, g_ptMouse.y);
	//TextOut(hBackDC, 200, 20, szText, strlen(szText));
	// FPS
	TimerManager::GetSingleton()->Render(hBackDC);

	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
