#pragma once

class cMap;
class cProgressBar;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// 플레이어 이미지 파일
	float			m_fPosX;
	float			m_fPosY;

	float			m_fGravity;			// 중력 (점프시 사용)
	bool			m_isJumpping;		// 점프 중이냐?
	float			m_fJumpPower;		// 점프 파워

	int				m_nMapYPos;			// 플레이어의 바닥위 설정 (맵에 따라 다르게 설정이 필요)
	int				m_nDamageDelay;		// 연속 데미지 방지용 딜레이(무적 모드)

	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;

	cImage*			m_pImgMapBuffer;	// 배경 정보 이미지
	cImage*			m_pImgBackground;		// 화면 전체 배경
	cImage*			m_pImgGround;
	cImage*			m_pImgMiniMap;
	cImage*			m_pImgClientBuffer;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void MiniRender();
	void Render();

	void SetLanding();
	RECT GetBoundingBox() { return m_pPlayerImage->GetBoundingBox(); }
	float GetPosX() { return m_pPlayerImage->GetPosX(); }
	float GetPosY() { return m_pPlayerImage->GetPosY(); }

	int GetDamageDelay() { return m_nDamageDelay; }
	void SetDamageDelay(int delay) { m_nDamageDelay = delay; }
};

