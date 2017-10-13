#pragma once

// 랜덤 값 생성
inline int GetRandom(int max)
{
	return rand() % max;
}

// 최소값과 최대값 사이의 랜덤 값 생성(최소, 최대값 포함)
inline int GetRandom(int min, int max)
{
	// 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
	// 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
	return rand() % (max - min + 1) + min;
}

//선 그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//렉트 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//렉트 센터점에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline RECT RectMakeCenter(RECT rt, int width, int height)
{
	RECT rc;
	rc.left = (rt.right + rt.left) / 2 - width / 2;
	rc.top = (rt.top + rt.bottom) / 2 - height / 2;
	rc.right = rc.left + width;
	rc.bottom = rc.top + height;

	return rc;
}

//렉트 구조체로 사각형 그리기
inline void RectangleMake(HDC hdc, RECT rt)
{
	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

//사각형 그리기 (Rectangle함수이용)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//원 그리기 (Ellipse함수이용)
inline void EllipseMake(HDC hdc, RECT rt)
{
	Ellipse(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//원 센터점 그리기 (Ellipse함수이용)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// 거리(대각선 길이) 구하는 함수
inline float GetLength(float x1, float y1, float x2, float y2)
{
	float fLengthX = x2 - x1;
	float fLengthY = y2 - y1;

	return sqrtf(fLengthX * fLengthX + fLengthY * fLengthY);
}

// 두 점 사이의 각도 구하는 함수
inline float GetAngle(float x1, float y1, float x2, float y2)
{
	float fLengthDiagonal = GetLength(x1, y1, x2, y2);

	if (fLengthDiagonal < FLT_EPSILON) return 0;

	float fAngle = acosf((x2 - x1) / fLengthDiagonal) / PI * 180.0f;

	// 각도 예외 처리
	if (y1 > y2)
	{
		fAngle = 360.0f - fAngle;

		if (fAngle >= 360.0f)
			fAngle -= 360.0f;
	}

	return fAngle;
}