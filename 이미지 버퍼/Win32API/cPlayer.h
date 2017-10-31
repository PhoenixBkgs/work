#pragma once

class cMap;
class cProgressBar;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// �÷��̾� �̹��� ����
	float			m_fPosX;
	float			m_fPosY;

	float			m_fGravity;			// �߷� (������ ���)
	bool			m_isJumpping;		// ���� ���̳�?
	float			m_fJumpPower;		// ���� �Ŀ�

	int				m_nMapYPos;			// �÷��̾��� �ٴ��� ���� (�ʿ� ���� �ٸ��� ������ �ʿ�)
	int				m_nDamageDelay;		// ���� ������ ������ ������(���� ���)

	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;

	cImage*			m_pImgMapBuffer;	// ��� ���� �̹���
	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
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

