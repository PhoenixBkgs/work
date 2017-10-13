#pragma once
#include "cImage.h"

class cMap
{
private:
	cImage*		m_pBgImage;
	int			m_nSourX;
	int			m_nMoveSpeed;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	void SetMoveSpeed(int speed) { m_nMoveSpeed = speed; }
};

