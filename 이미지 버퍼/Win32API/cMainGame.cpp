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
	// 흰색으로 이미지를 칠한다.
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
	/* 전체 배경 */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/field00.bmp", 4800, 600);

	/* 맵 */
	m_pImgGround = g_pImageManager->AddImage("Map", "images/map_wide.bmp", 4800, 600);
	m_pImgGround0 = g_pImageManager->AddImage("Map0", "images/map_wide.bmp", 4800, 600, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("MapBuffer", WINSIZEX * 6, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255)); //화면에 맵 그림
	g_pImageManager->AddImage("ClientBuffer", WINSIZEX * 6, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* 미니맵 */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX * 6, WINSIZEY / 5);//뒤의 x, y는 미니맵 크기
	//m_pImgMiniMap0 = g_pImageManager->AddImage("MiniMap", WINSIZEX, WINSIZEY / 5);//뒤의 x, y는 미니맵 크기

	/* 프로그레스바 */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* 지형물 오브젝트*/
	g_pImageManager->AddImage("Object", "images/angrybirds-name-03.bmp", 894, 894, true, RGB(255, 0, 255));

	/* 플레이어 */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12, 200, MAP1_Y, true, RGB(255, 0, 255));

	/* 몬스터 */ 
}

void cMainGame::MiniMapRender()
{
	m_pPlayer->MiniRender();
	
	//미니맵 빈 비트맵에 넣어주고 오브젝트도 빈 비트맵에 넣어주고 플레이어 점 넣어주고
	
	m_pImgBackground->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	m_pImgGround0->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	m_pImgMiniMap->Render(g_hDC, 0, 0); //미니맵 시작좌표
	m_pImgBackBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5); //미니맵에 그려주는 이미지 백버퍼
	
	
	
	

	//아까 설명을 다시 돌아보면
	//메인 화면에 출력되는 버퍼가 있고
	//이 버퍼를 움직여서 맵 이동을 표현해야 한다!
	//그런데 버퍼를 어떻게 움직여주지?!


	//m_pImgMinimapBuffer->Render(m_pImgBackBuffer->GetMemDC(), 0, 0);
	//m_pImgBackground->Render(m_pImgMiniMap->GetMemDC(), 0, 0);
	//m_pImgGround->Render(m_pImgMiniMap->GetMemDC(), 0, 0);
	//m_pImgGround->Render(m_pImgMiniMap->GetMemDC(), m_pImgGround->GetPosX() + WINSIZEX / 2, m_pImgGround->GetPosY() + WINSIZEY / 2);
	//m_pImgGround->Render(m_pImgMiniMap->GetMemDC(), m_pImgGround->GetPosX() + WINSIZEX / 2, m_pImgGround->GetPosY()  WINSIZEY / 2);

}