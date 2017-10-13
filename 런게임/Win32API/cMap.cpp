#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{
	m_pBgImage = new cImage;
	m_pBgImage->Setup("images/bg2.bmp", 2400 , 675);
}


cMap::~cMap()
{
}

void cMap::Setup()
{
	m_nSourX = 0;
	m_nMoveSpeed = 5;
}

void cMap::Update()
{
	m_nSourX += m_nMoveSpeed;

	if (m_nSourX >= 800)
		m_nSourX = 0;
}

void cMap::Render()
{
	m_pBgImage->Render(g_hDC, 0, 0, m_nSourX, 0, WINSIZEX, WINSIZEY);

	// string 문자열 클래스 : 문자열에 대한 연산자 사용이 가능하다 ex) +=
	string str("맵 X 좌표 : ");
	char szStr[128];
	//str += "asdfasdfsadf";
	str += itoa(m_nSourX, szStr, 10); // itoa => 인트형을 문자열로 변환 (변환 소스, 임시 저장소, 숫자의 진수)
	TextOutA(g_hDC, 100, 100, str.c_str(), str.length());
}

//#include "stdafx.h"
//#include "cMap.h"
//
//
//cMap::cMap()
//{
//	m_pBgImage = new cImage;
//	m_pBgImage->Setup("images/bg.bmp", 6600, 675);
//}
//
//
//cMap::~cMap()
//{
//}
//
//void cMap::Setup()
//{
//	m_nSourX = 0;
//	m_nMoveSpeed = 5;
//}
//
//void cMap::Update()
//{
//	m_nSourX += m_nMoveSpeed;
//
//	if (m_nSourX >= 5400)
//		m_nSourX = 0;
//}