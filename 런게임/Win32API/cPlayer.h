#pragma once
#include "cImage.h"

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;
	float			m_fGravity;
	bool			m_isJumpping;
	bool			m_is2ndJump;
	float			m_fJumpPower;

	int				m_nMapYPos;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

	void SetLanding();
};

