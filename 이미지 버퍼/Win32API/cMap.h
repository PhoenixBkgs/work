#pragma once

class cMap
{
private:
	cImage*		m_pImgGround;			// �⺻ ���� �̹���
	cImage*		m_pImgBackground;		//����

	cImage*		m_pObject;				// �����̴� ������Ʈ
	bool		m_bMoveRight;

	cImage*		m_pImgMapBuffer;		// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
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

