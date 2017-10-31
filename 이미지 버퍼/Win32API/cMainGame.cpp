#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"


cMainGame::cMainGame()
	: m_isPlaying(false)
{
	LoadImageFromFile();

	m_pMap = new cMap;
	m_pPlayer = new cPlayer;
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cMainGame::Setup()
{
	m_pMap->Setup();
	m_pPlayer->Setup();
}

void cMainGame::Update()
{
	cGameNode::Update();

	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		Setup();
		m_isPlaying = true;
	}
}

void cMainGame::Render()
{
	// ������� �̹����� ĥ�Ѵ�.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
		m_pImgBackground->Render(g_hDC, 0, 0);
		

		m_pMap->Render();
		MiniMapRender();
		m_pPlayer->Render();
		
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}
}

void cMainGame::LoadImageFromFile()
{
	/* ��ü ��� */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/field00.bmp", 4800, 600);

	/* �� */
	m_pImgGround = g_pImageManager->AddImage("Map", "images/map_wide.bmp", 4800, 600);
	m_pImgGround0 = g_pImageManager->AddImage("Map0", "images/map_wide.bmp", 4800, 600, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("MapBuffer", WINSIZEX * 6, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255)); //ȭ�鿡 �� �׸�
	g_pImageManager->AddImage("ClientBuffer", WINSIZEX * 6, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* �̴ϸ� */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX * 6, WINSIZEY / 5);//���� x, y�� �̴ϸ� ũ��
	//m_pImgMiniMap0 = g_pImageManager->AddImage("MiniMap", WINSIZEX, WINSIZEY / 5);//���� x, y�� �̴ϸ� ũ��

	/* ���α׷����� */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* ������ ������Ʈ*/
	g_pImageManager->AddImage("Object", "images/angrybirds-name-03.bmp", 894, 894, true, RGB(255, 0, 255));

	/* �÷��̾� */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12, 200, MAP1_Y, true, RGB(255, 0, 255));

	/* ���� */ 
}

void cMainGame::MiniMapRender()
{
	m_pPlayer->MiniRender();
	
	//�̴ϸ� �� ��Ʈ�ʿ� �־��ְ� ������Ʈ�� �� ��Ʈ�ʿ� �־��ְ� �÷��̾� �� �־��ְ�
	
	m_pImgBackground->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	m_pImgGround0->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	m_pImgMiniMap->Render(g_hDC, 0, 0); //�̴ϸ� ������ǥ
	m_pImgBackBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5); //�̴ϸʿ� �׷��ִ� �̹��� �����
	
	
	
	

	//�Ʊ� ������ �ٽ� ���ƺ���
	//���� ȭ�鿡 ��µǴ� ���۰� �ְ�
	//�� ���۸� �������� �� �̵��� ǥ���ؾ� �Ѵ�!
	//�׷��� ���۸� ��� ����������?!


	//m_pImgMinimapBuffer->Render(m_pImgBackBuffer->GetMemDC(), 0, 0);
	//m_pImgBackground->Render(m_pImgMiniMap->GetMemDC(), 0, 0);
	//m_pImgGround->Render(m_pImgMiniMap->GetMemDC(), 0, 0);
	//m_pImgGround->Render(m_pImgMiniMap->GetMemDC(), m_pImgGround->GetPosX() + WINSIZEX / 2, m_pImgGround->GetPosY() + WINSIZEY / 2);
	//m_pImgGround->Render(m_pImgMiniMap->GetMemDC(), m_pImgGround->GetPosX() + WINSIZEX / 2, m_pImgGround->GetPosY()  WINSIZEY / 2);

}