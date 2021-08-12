#include "PixelCollisionScene.h"
#include "Image.h"

HRESULT PixelCollisionScene::Init()
{
	bg = ImageManager::GetSingleton()->AddImage("�ȼ� �浹 ���",
		"Image/mountain.BMP", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	ball = ImageManager::GetSingleton()->AddImage("�ȼ� �浹 ��",
		"Image/ball.BMP", 60, 60, true, RGB(255, 0, 255));

	posBall.x = WINSIZE_X / 2;
	posBall.y = WINSIZE_Y / 2;

	isLanding = false;

	return S_OK;
}

void PixelCollisionScene::Release()
{
}

void PixelCollisionScene::Update()
{
	if (ball)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			posBall.x = WINSIZE_X / 2;
			posBall.y = WINSIZE_Y / 2;
		}

		// �¿��̵�
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			posBall.x -= 1.0f;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			posBall.x += 1.0f;
		}

		// ����
		if (posBall.y < WINSIZE_Y /*&& isLanding == false*/)
		{
			posBall.y += 9.81f * TimerManager::GetSingleton()->GetElapsedTime();
		}

		// �ȼ� �浹 Ȯ��
		COLORREF color;
		int R, G, B;
		float currPosY = posBall.y + ball->GetHeight() / 2;
		for (int i = currPosY - 10; i < currPosY + 10; i++)
		{
			color = GetPixel(bg->GetMemDC(),
				posBall.x, i);

			R = GetRValue(color);
			G = GetGValue(color);
			B = GetBValue(color);

			if (!(R == 255 && G == 0 && B == 255))
			{
				// ��ġ ����
				posBall.y = i - (ball->GetHeight() / 2);
				break;
				//isLanding = true;
			}
		}
	}
}

void PixelCollisionScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	if (bg)
	{
		bg->Render(hdc);
	}

	if (ball)
	{
		ball->Render(hdc, posBall.x, posBall.y, true);
	}
}
