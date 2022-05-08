//
// Author:  Vladimir Novick
//          vlad.novick@gmail.com
//


#pragma once
#include  "StdAfx.h"


static enum ButtonState {
	BS_DISABLED		= 0,	
	BS_ENABLED		= 1,	
	BS_CLICKED		= 2,	
	BS_PRESSED		= 3,	
	BS_HOT			= 4,	
	BS_LAST_STATE	= 5		
};

struct tColorScheme {
	COLORREF	m_Disabled;
	COLORREF	m_Enabled;
	COLORREF	m_Clicked;
	COLORREF	m_Pressed;
	COLORREF	m_Hover;
};

struct tBitmapScheme {
	CBitmap	*m_Disabled;
	CBitmap	*m_Enabled;
	CBitmap* m_Clicked;
	CBitmap* m_Pressed;
	CBitmap* m_Hover;
	BOOL m_bTransparent;
};


struct tButtonStyle {
	double	m_dSizeAA;
	double	m_dRadius;
	double	m_dBorderRatio;
	double	m_dHeightBorder;
	double	m_dHeightButton;
	double	m_dHighLightX;
	double	m_dHighLightY;
	double	m_dRadiusHighLight;
	double	m_dPowerHighLight;
	tColorScheme	m_ColorBack;
	tColorScheme	m_ColorBorder;
	tColorScheme	m_ColorFace;
	tBitmapScheme   m_BitmapScheme;
};

class CRoundButtonStyle
{
public:
	CRoundButtonStyle(void);
	~CRoundButtonStyle(void);

	bool GetButtonStyle(tButtonStyle* _ptButtonStyle);
	bool SetButtonStyle(tButtonStyle* _ptButtonStyle);
	CSize GetEdgeSize(void)
	{
		return m_BtnSize;
	}
	CSize GetMaskSize(void)
	{
		return CSize(
			2 * m_BtnSize.cx + 1,
			2 * m_BtnSize.cy + 1);
	}
	CBitmap* GetButtonEdge(CDC* _pDC);
	tButtonStyle m_ButtonStyle;
private:
	bool m_bButtonDrawn;
	CSize	m_BtnSize;
	CBitmap m_BmpButtonEdge;
	CBitmap m_BMPButtons;


};