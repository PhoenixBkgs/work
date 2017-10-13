#pragma once
#include "cImage.h"

class cGameNode
{
private:
	cImage*		m_backBuffer;

public:
	cGameNode();
	virtual ~cGameNode();

	virtual void Update();
	virtual void Render() PURE;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	cImage*	GetBackBuffer() { return m_backBuffer; }
};

