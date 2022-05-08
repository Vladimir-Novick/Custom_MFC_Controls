#include "StdAfx.h"
#include "CWinUtils.h"

void CWinUtils::SetGradientsDC(HWND hwnd, HDC dc, COLORREF bgSrart,
	COLORREF bgEnd)
{

	RECT rect, temp;
	HBRUSH color; /* A brush to do the painting with */

	GetClientRect(hwnd, &rect);

	/* Start color; Change the R,G,B values
	to the color of your choice */
	int r1 = GetRValue(bgSrart);
	int g1 = GetGValue(bgSrart);
	int b1 = GetBValue(bgSrart);


	/* End Color; Change the R,G,B values
	to the color of your choice */
	int r2 = GetRValue(bgEnd);
	int g2 = GetGValue(bgEnd);
	int b2 = GetBValue(bgEnd);

	/* loop to create the gradient */
	for (int i = 0; i < rect.bottom; i++)
	{
		/* Color ref. for the gradient */
		int r, g, b;
		/* Determine the colors */
		r = r1 + (i * (r2 - r1) / rect.bottom);
		g = g1 + (i * (g2 - g1) / rect.bottom);
		b = b1 + (i * (b2 - b1) / rect.bottom);

		temp = rect;

		/* Fill in the rectangle information */


		temp.top = i;
		/* Height of the rectangle */
		temp.bottom = i + 1;

		/* Create a brush to draw with;
		these colors are randomized */
		color = CreateSolidBrush(RGB(r, g, b));

		/* Finally fill in the rectangle */
		FillRect(dc, &temp, color);
		DeleteObject(color);
	}
}
