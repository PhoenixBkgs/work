#pragma once

class cMap
{
private:
	cImage*		m_pImgGround;			// 기본 지형 이미지
	cImage*		m_pImgBackground;		//지형

	cImage*		m_pObject;				// 움직이는 오브젝트
	bool		m_bMoveRight;

	cImage*		m_pImgMapBuffer;		// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼
	cImage*		m_pImgMinimap;
	cImage*		m_pImgClientBuffer;

	void MoveObject();

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();
};

