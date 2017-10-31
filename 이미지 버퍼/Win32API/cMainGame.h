#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:
	bool			m_isPlaying;

	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
	cImage*			m_pImgGround;
	cImage*			m_pImgMiniMap;			// �̴ϸʿ� �̹��� ����
	cImage*			m_pImgMiniMap0;
	cImage*			m_pImgGround0;

	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	void LoadImageFromFile();
	void MiniMapRender();

public:
	cMainGame();
	~cMainGame();

	void Setup();
	virtual void Update() override;
	virtual void Render() override;
};