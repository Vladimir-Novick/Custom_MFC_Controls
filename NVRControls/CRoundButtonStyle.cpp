//
// Author:  Vladimir Novick
//          vlad.novick@gmail.com
//


#include  "StdAfx.h"
#include "math.h"
#include "CRoundButtonstyle.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CRoundButtonStyle::CRoundButtonStyle(void)
	: m_bButtonDrawn(false)
{
	m_BtnSize = CSize(0, 0);
	m_ButtonStyle.m_dSizeAA = 1.0;
	m_ButtonStyle.m_dHighLightX = 0.0;
	m_ButtonStyle.m_dHighLightY = -4.0;//-7.0;
	m_ButtonStyle.m_dRadius = 25.0;
	m_ButtonStyle.m_dBorderRatio = 0.2;
	m_ButtonStyle.m_dHeightButton = 0.2; //0.5;
	m_ButtonStyle.m_dRadiusHighLight = 5.0;// 7.0;
	m_ButtonStyle.m_dPowerHighLight = 0.4;
	m_ButtonStyle.m_ColorBack.m_Disabled = GetSysColor(COLOR_3DFACE);
	m_ButtonStyle.m_ColorBorder.m_Disabled = RGB(128, 128, 128);
	m_ButtonStyle.m_ColorFace.m_Disabled = RGB(128, 128, 128);
	m_ButtonStyle.m_ColorBack.m_Enabled = RGB(100, 100, 100);
	m_ButtonStyle.m_ColorBorder.m_Enabled = RGB(164, 128, 128);
	m_ButtonStyle.m_ColorFace.m_Enabled = RGB(200, 200, 200);
	m_ButtonStyle.m_ColorBack.m_Clicked = RGB(100, 100, 100);
	m_ButtonStyle.m_ColorBorder.m_Clicked = RGB(255, 255,255);
	m_ButtonStyle.m_ColorFace.m_Clicked = RGB(164, 164, 164);
	m_ButtonStyle.m_ColorBack.m_Pressed = RGB(150, 150, 150);
	m_ButtonStyle.m_ColorBorder.m_Pressed = RGB(164, 128, 128);
	m_ButtonStyle.m_ColorFace.m_Pressed = RGB(164, 164, 164);
	m_ButtonStyle.m_ColorBack.m_Hover = RGB(100, 100, 100); 
	m_ButtonStyle.m_ColorBorder.m_Hover = RGB(164, 128, 128);
	m_ButtonStyle.m_ColorFace.m_Hover = RGB(220, 220, 220);

	m_ButtonStyle.m_BitmapScheme.m_Disabled = NULL;
	m_ButtonStyle.m_BitmapScheme.m_Enabled = NULL;
	m_ButtonStyle.m_BitmapScheme.m_Clicked = NULL;
	m_ButtonStyle.m_BitmapScheme.m_Pressed = NULL;
	m_ButtonStyle.m_BitmapScheme.m_Hover = NULL;
	m_ButtonStyle.m_BitmapScheme.m_bTransparent = FALSE;

}
CRoundButtonStyle::~CRoundButtonStyle(void)
{
}
bool CRoundButtonStyle::GetButtonStyle(tButtonStyle* _ptButtonStyle)
{
	if (_ptButtonStyle == NULL)
		return false;
	memcpy(_ptButtonStyle, &m_ButtonStyle, sizeof(tButtonStyle));
	return true;
}
bool CRoundButtonStyle::SetButtonStyle(tButtonStyle* _ptButtonStyle)
{
	if (_ptButtonStyle == NULL)
		return false;
	memcpy(&m_ButtonStyle, _ptButtonStyle, sizeof(tButtonStyle));
	if (_ptButtonStyle->m_BitmapScheme.m_Enabled != NULL) {
		TRACE("Set Bitmap style");
	}
	m_bButtonDrawn = false;
	return true;
}
CBitmap* CRoundButtonStyle::GetButtonEdge(CDC* _pDC)
{
	if (!m_bButtonDrawn)
	{
		m_bButtonDrawn = true;
	}
	return &m_BmpButtonEdge;
}
