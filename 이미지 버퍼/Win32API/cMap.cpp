#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{
	m_pImgGround = g_pImageManager->FindImage("Map");
	m_pImgBackground = g_pImageManager->FindImage("BackGround");

	m_pObject = g_pImageManager->FindImage("Object");
	m_pObject->SetPosX(100);
	m_pObject->SetPosY(100);
	m_bMoveRight = true;

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgMinimap	= g_pImageManager->FindImage("MiniMap");
	m_pImgClientBuffer = g_pImageManager->FindImage("ClientBuffer");
}

cMap::~cMap()
{
}

void cMap::Setup()
{
}

void cMap::Update()
{
	MoveObject();

	
	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);
}

void cMap::Render()
{
	// 픽셀 충돌 처리용 이미지 버퍼에 그림을 그린다.
	//void cImage::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
	
	//m_pImgBackground->Render(g_hDC, m_pImgBackground->GetPosX() - WINSIZEX / 2, m_pImgBackground->GetPosY() - WINSIZEY / 2);
	
	//m_pImgBackground->Render(m_pImgMapBuffer->GetMemDC(), m_pImgBackground->GetPosX() - WINSIZEX / 2, m_pImgBackground->GetPosY() - WINSIZEY / 2);
	
	//m_pImgGround->Render(m_pImgClientBuffer->GetMemDC(), m_pImgGround->GetPosX() - WINSIZEX / 2, m_pImgGround->GetPosY() - WINSIZEY / 2);

	
	//m_pImgBackground->Render(m_pImgMinimap->GetMemDC(), 0, 0);
	//m_pImgGround->Render(m_pImgMinimap->GetMemDC(), 0, 0);
	
	//m_pImgBackground->Render(g_hDC, 0, 0);
	//m_pImgGround->Render(g_hDC, 0, 0);
	
	//m_pImgBackground->Render(g_hDC, m_pImgGround->GetPosX() - WINSIZEX / 2, m_pImgGround->GetPosY() - WINSIZEY / 2);
	//m_pImgGround->Render(g_hDC, m_pImgBackground->GetPosX() - WINSIZEX / 2, m_pImgBackground->GetPosY() - WINSIZEY / 2);
	

	//m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_pImgGround->GetPosX() - WINSIZEX / 2, m_pImgGround->GetPosY() - WINSIZEY / 2);
	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), m_pObject->GetPosX(), m_pObject->GetPosY(), 300, 100); //움직이는 발판(앵그리버드)

	// 백버퍼에 그린다.
	//m_pImgClientBuffer->Render(g_hDC, 0, 0);
	m_pImgMapBuffer->Render(g_hDC, 0, 0);
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_pImgGround->GetPosX() - WINSIZEX / 2, m_pImgGround->GetPosY() - WINSIZEY / 2);

	//m_pImgMinimap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);
}

void cMap::MoveObject()
{
	if (m_bMoveRight && m_pObject->GetPosX() < 500)
	{
		m_pObject->SetPosX(m_pObject->GetPosX() + 1);
		if (m_pObject->GetPosX() >= 500)
			m_bMoveRight = false;
	}
	else if (m_pObject->GetPosX() > 100)
	{
		m_pObject->SetPosX(m_pObject->GetPosX() - 1);
		if (m_pObject->GetPosX() <= 100)
			m_bMoveRight = true;
	}
}