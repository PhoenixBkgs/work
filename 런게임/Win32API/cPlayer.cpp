#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
	m_pPlayerImage = new cImage;
	m_pPlayerImage->Setup("images/Rockman.bmp", 512, 376, 4, 3,
		128, MAP1_Y, true, RGB(255, 0, 255));
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;

	SetLanding();
}

void cPlayer::Update()
{
	if (!m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_isJumpping = true;
	}

	if (m_isJumpping)
	{		//점프 애니메이션
		m_pPlayerImage->FrameRender(g_hDC,
			(int)(m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2),
			(int)(m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2),
			0, 1, 0, 0, 0); //FrameRender(HDC hdc, int 시작지점X, 시작지점Y, 루프지점X, 루프지점Y, 맥스프레임X, 맥스프레임Y, 딜레이)
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;
	}
	if (m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))//2단점프
	{
		m_is2ndJump = true;
	}
	if (m_is2ndJump)
	{
		//2단 점프 애니메이션
		m_pPlayerImage->FrameRender(g_hDC,
			(int)(m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2),
			(int)(m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2),
			1, 1, 3, 1, 8); //FrameRender(HDC hdc, int 시작지점X, 시작지점Y, 루프지점X, 루프지점Y, 맥스프레임X, 맥스프레임Y, 딜레이)
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - m_fJumpPower);
		m_fGravity += GRAVITY;
	}
	if (m_fGravity > m_fJumpPower &&
		m_pPlayerImage->GetPosY() > m_nMapYPos - m_pPlayerImage->GetFrameHeight() / 2)
	{
		SetLanding();
	}
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	//RectangleMake(g_hDC, m_pPlayerImage->GetBoundingBox(20, 5));
	LineMake(g_hDC, m_pPlayerImage->GetBoundingBox(20, 5).left,
		m_pPlayerImage->GetBoundingBox(20, 5).top,
		m_pPlayerImage->GetBoundingBox(20, 5).right,
		m_pPlayerImage->GetBoundingBox(20, 5).top);
	LineMake(g_hDC, m_pPlayerImage->GetBoundingBox(20, 5).right,
		m_pPlayerImage->GetBoundingBox(20, 5).top,
		m_pPlayerImage->GetBoundingBox(20, 5).right,
		m_pPlayerImage->GetBoundingBox(20, 5).bottom);
	LineMake(g_hDC, m_pPlayerImage->GetBoundingBox(20, 5).right,
		m_pPlayerImage->GetBoundingBox(20, 5).bottom,
		m_pPlayerImage->GetBoundingBox(20, 5).left,
		m_pPlayerImage->GetBoundingBox(20, 5).bottom);
	LineMake(g_hDC, m_pPlayerImage->GetBoundingBox(20, 5).left,
		m_pPlayerImage->GetBoundingBox(20, 5).bottom,
		m_pPlayerImage->GetBoundingBox(20, 5).left,
		m_pPlayerImage->GetBoundingBox(20, 5).top);

	DeleteObject(hSelectPen);
	DeleteObject(hPen);



	//걷기 애니메이션

	m_pPlayerImage->FrameRender(g_hDC,
		(int)(m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2),
		(int)(m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2),
		0, 0, 3, 0, 15); //FrameRender(HDC hdc, int 시작지점X, 시작지점Y, 루프지점X, 루프지점Y, 맥스프레임X, 맥스프레임Y, 딜레이)
	
}

void cPlayer::SetLanding()
{
	m_pPlayerImage->SetCenterY(m_nMapYPos);
	m_fGravity = 0.0f;
	m_isJumpping = false;
	m_is2ndJump = false;
}