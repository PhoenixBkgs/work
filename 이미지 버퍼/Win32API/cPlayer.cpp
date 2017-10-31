#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	//m_pPlayerImage = new cImage;
	//m_pPlayerImage->Setup("images/ch.bmp", 960, 960, 12, 12,
	//	200, MAP1_Y, true, RGB(255, 0, 255));
	m_pImgBackground = g_pImageManager->FindImage("BackGround");
	m_pPlayerImage = g_pImageManager->FindImage("Player");
	m_pImgGround = g_pImageManager->FindImage("Map");

	m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront",
		m_pPlayerImage->GetFrameWidth(), 10);

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	
}


cPlayer::~cPlayer()
{
	vector<string> saveData;
	char temp[128];

	saveData.push_back(itoa(m_fPosX, temp, 10));
	saveData.push_back(itoa(m_fPosY, temp, 10));
	saveData.push_back(itoa(m_fCurrHp, temp, 10));

	g_pFileDataManager->txtSave("PlayerData.txt", saveData);
}

void cPlayer::Setup()
{
	m_nDamageDelay = 0;
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);

	SetLanding();

	//vector<string> vecLoad = g_pFileDataManager->txtLoad("PlayerData.txt");

	//if (!vecLoad.empty())
	//{
	//	m_pPlayerImage->SetPosX(atoi(vecLoad[0].c_str()));
	//	m_pPlayerImage->SetPosY(atoi(vecLoad[1].c_str()));
	//	m_fCurrHp = atoi(vecLoad[2].c_str());
	//}
}

void cPlayer::Update()
{
	float probeX = m_pPlayerImage->GetPosX();
	float probeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2;

	if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY))
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() + 5);
	else if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 5) == false)
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - 5);

	if (g_pKeyManager->isStayKeyDown('A'))
	{
		m_pPlayerImage->SetPosX(m_fPosX - 3.0f);
		if (m_pPlayerImage->GetBoundingBox().left <= 0)//바운딩 박스로 화면 바깥 못벗어나게(왼쪽)
		{
			m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() + 3.0f);
			m_pImgMapBuffer->SetPosX(m_pImgMapBuffer->GetPosX() + 3);
			m_pImgGround->SetPosX(m_pImgGround->GetPosX() + 3);
			//if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX + m_pPlayerImage->GetFrameWidth(), probeY))
			//	m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() + 3.0f);
		}

	}
	//이미지 그라운드, 이미지 백그라운드
	else if (g_pKeyManager->isStayKeyDown('D'))
	{
		m_pPlayerImage->SetPosX(m_fPosX + 3.0f);
		if (m_pPlayerImage->GetBoundingBox().right >= WINSIZEX / 2)//바운딩 박스로 화면 바깥 못벗어나게(오른쪽)
		{
			//if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX + m_pPlayerImage->GetFrameWidth(), probeY))
			//	m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() - 6.0f);
			m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() - 3.0f);
			//m_pImgMapBuffer->SetPosX(m_pImgMapBuffer->GetPosX() + 3);
			m_pImgBackground->SetPosX(m_pImgBackground->GetPosX() - 3);
			m_pImgGround->SetPosX(m_pImgGround->GetPosX() - 3);
			//if (m_pImgBackground->GetPosX >= WINSIZEX)
			//{
			//	m_pImgBackground->SetPosX(m_pImgBackground->GetPosX() +3);
			//}
			
		}

	}

	if (g_pKeyManager->isStayKeyDown('W'))
	{
		m_pPlayerImage->SetPosY(m_fPosY - 3.0f);
	}
	else if (g_pKeyManager->isStayKeyDown('S'))
	{
		m_pPlayerImage->SetPosY(m_fPosY + 3.0f);
	}

	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		m_fCurrHp -= 1.0f;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		m_fCurrHp += 1.0f;
	}

	if (!m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_isJumpping = true;
	}

	if (m_isJumpping)
	{
		m_pPlayerImage->SetPosY(m_fPosY - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;

		// 점프 후 내려오는 중에 착지 설정
		if (m_fGravity > m_fJumpPower)
		{
			probeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 5) == false)
				SetLanding();
		}
	}

	if (m_nDamageDelay > 0)
		--m_nDamageDelay;

	m_fPosX = m_pPlayerImage->GetPosX();
	m_fPosY = m_pPlayerImage->GetPosY();

	m_pHpBar->SetPosX(m_fPosX);
	m_pHpBar->SetPosY(m_fPosY - m_pPlayerImage->GetFrameHeight() / 2 - 10);
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	m_pHpBar->Update();
}

void cPlayer::MiniRender()//미니맵에 플레이어 위치 점으로 표시
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(100, 100, 100));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	EllipseMakeCenter(g_hDC, m_pPlayerImage->GetPosX(), m_pPlayerImage->GetPosY(), 30, 30);//플레이어 위치를 점으로 표현

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
	//m_pImgBackground->Render(g_hDC, 0, 0);
	//m_pImgGround->Render(g_hDC, 0, 0);
}

void cPlayer::Render()
{
	
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	BoudingLineMake(g_hDC, m_pPlayerImage->GetBoundingBox().left,
		m_pPlayerImage->GetBoundingBox().top,
		m_pPlayerImage->GetFrameWidth(),
		m_pPlayerImage->GetFrameHeight());

	DeleteObject(hSelectPen);
	DeleteObject(hPen);

	// 무적 모드 중에는 반짝이게 표현
	if (m_nDamageDelay % 2 == 0)
	{
		m_pPlayerImage->FrameRender(g_hDC,
			m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
			m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
			1, 0, 8, 0, 3);
	}

	//m_pHpBar->Render();
}

void cPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_isJumpping = false;
}