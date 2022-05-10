#pragma once
class CWinUtils
{
public :
	static void SetGradientsDC(HWND hwnd, HDC dc, COLORREF bgSrart,
		COLORREF bgEnd);
	static int GetFontHeight(int nPointSize);
};

