//
// Author:  Vladimir Novick
//          vlad.novick@gmail.com
//




#include "StdAfx.h"
#include <math.h>
#include "CRoundButton.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRoundButton::CRoundButton(void):	
	  m_bDefaultButton(false)
	, m_bIsCheckButton(false)
	, m_bIsRadioButton(false)
	, m_bIsHotButton(false)
	, m_bMouseOnButton(false)
	, m_bIsChecked(false)	
	, m_rBtnSize(CRect(0, 0, 0, 0))
	, m_bRedraw(false)
	, m_sOldCaption(_T(""))
	  {
	m_ptButtonStyle = new CRoundButtonStyle();
	m_LogFont.lfHeight			= 12;
	m_LogFont.lfWidth			= 0;
	m_LogFont.lfEscapement		= 0;
	m_LogFont.lfOrientation	= 0;
	m_LogFont.lfWeight			= FW_SEMIBOLD;
	m_LogFont.lfItalic			= false;
	m_LogFont.lfUnderline		= false;
	m_LogFont.lfStrikeOut		= false;
	m_LogFont.lfCharSet		= DEFAULT_CHARSET;
	m_LogFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_LogFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_LogFont.lfQuality		= ANTIALIASED_QUALITY;
	m_LogFont.lfPitchAndFamily	= DEFAULT_PITCH;
	lstrcpy(m_LogFont.lfFaceName, _T("Tahoma"));
	m_BtnFont.CreateFontIndirect(&m_LogFont);
	m_TextColor.m_Disabled	= RGB(64, 64, 64);
	m_TextColor.m_Enabled		= RGB( 0,  0,  0);
	m_TextColor.m_Clicked		= RGB( 0,  0,  0);
	m_TextColor.m_Pressed		= RGB( 0,  0,  0);
	m_TextColor.m_Hover			= RGB( 200,  0,  0);
	m_pBitmapBackground = NULL;
	m_bHover = FALSE;
	m_bMouseTracking = FALSE;
	
}
CRoundButton::~CRoundButton(void)
{
	delete m_ptButtonStyle;

	if (m_pBitmapBackground != NULL) {
		m_pBitmapBackground->DeleteObject();
		delete m_pBitmapBackground;
	}
}

//=============================================================================
int CRoundButton::GetFontHeight(int nPointSize)
//=============================================================================
{
	HDC hdc = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	ASSERT(hdc);
	int cyPixelsPerInch = ::GetDeviceCaps(hdc, LOGPIXELSY);
	::DeleteDC(hdc);

	int nHeight = -MulDiv(nPointSize, cyPixelsPerInch, 72);

	return nHeight;
}


bool CRoundButton::SetButtonStyle(CRoundButtonStyle* _ptDesignRoundButtonStyle)
{
	if (_ptDesignRoundButtonStyle == NULL)
		return false;
	m_ptButtonStyle = _ptDesignRoundButtonStyle;
	m_bRedraw = true;
	return false;
}
bool CRoundButton::SetFont(LOGFONT* _ptLogFont)
{
	if (_ptLogFont == NULL)
		return false;
	if (m_BtnFont.m_hObject != NULL)
		m_BtnFont.DeleteObject();
	memcpy(&m_LogFont, _ptLogFont, sizeof(LOGFONT));
	m_BtnFont.CreateFontIndirect(&m_LogFont);
	m_bRedraw = true;
	return true;
}
bool CRoundButton::GetFont(LOGFONT* _ptLogFont)
{
	if (_ptLogFont == NULL)
		return false;
	memcpy(_ptLogFont, &m_LogFont, sizeof(LOGFONT));
	return true;
}
bool CRoundButton::SetTextColor(tColorScheme* _ptTextColor)
{
	if (_ptTextColor == NULL)
		return false;
	memcpy(&m_TextColor, _ptTextColor, sizeof(tColorScheme));
	m_bRedraw = true;
	return true;
}
bool CRoundButton::GetTextColor(tColorScheme* _ptTextColor)
{
	if (_ptTextColor == NULL)
		return false;
	memcpy(_ptTextColor, &m_TextColor, sizeof(tColorScheme));
	return true;
}
void CRoundButton::GenButtonBMPs(CDC* _pDC, CRect _rRect)
{
	if (m_BmpBtn.m_hObject != NULL)
		m_BmpBtn.DeleteObject();
	m_BmpBtn.m_hObject = NULL;
	if (m_BmpBtn.CreateCompatibleBitmap(_pDC, _rRect.Width(), _rRect.Height() * BS_LAST_STATE) == FALSE)
	{
		m_rBtnSize = CRect(0, 0, 0, 0);
	}
	else
	{
		m_rBtnSize = _rRect;
	}
}

void CRoundButton::DrawButtonCaption(CDC *_pDC)
{
	int nOldBckMode = _pDC->SetBkMode(TRANSPARENT);
	this->GetTextColor(&m_TextColor);
	COLORREF tOldColor ;
	HGDIOBJ hOldFont = _pDC->SelectObject(&m_BtnFont);
	CString sCaption;
	this->GetWindowText(sCaption);
	{
		switch(m_ButtonState)
		{
		case BS_ENABLED: {
			if (m_bHover) {
				tOldColor = _pDC->SetTextColor(m_TextColor.m_Hover);
			}
			else {
				tOldColor = _pDC->SetTextColor(m_TextColor.m_Enabled);
			}
		}
			break;
		case BS_CLICKED:
			tOldColor = _pDC->SetTextColor(m_TextColor.m_Clicked);
			break;
		case BS_PRESSED:
			tOldColor = _pDC->SetTextColor(m_TextColor.m_Pressed);
			break;
		case BS_HOT:
			tOldColor =_pDC->SetTextColor(m_TextColor.m_Hover);
			break;
		case BS_DISABLED:
		default:
			tOldColor =_pDC->SetTextColor(m_TextColor.m_Disabled);
			break;
		}




		_pDC->DrawText(
			sCaption, 
			m_rBtnSize,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	_pDC->SelectObject(hOldFont);
	_pDC->SetBkMode(nOldBckMode);
	_pDC->SetTextColor(tOldColor);
}

void CRoundButton::PreSubclassWindow()
{
#ifdef _DEBUG
	TCHAR buffer[255];
	GetClassName (m_hWnd, buffer, sizeof(buffer) / sizeof(TCHAR));
	ASSERT (CString (buffer) == _T("Button"));
#endif
	if (GetStyle() & 0x0FL)
		m_bDefaultButton = true;
	ModifyStyle (0x0FL, BS_OWNERDRAW | BS_AUTOCHECKBOX);
	CButton::PreSubclassWindow();
}

void CRoundButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	ASSERT (pDC != NULL);
	//DrawBitmap(pDC, m_pBitmapBackgrownd, lpDrawItemStruct->rcItem);


	m_ButtonState = BS_ENABLED;
	if (m_bIsHotButton && m_bMouseOnButton)
		m_ButtonState = BS_HOT;
	if ((lpDrawItemStruct->itemState & ODS_DISABLED) == ODS_DISABLED)
		m_ButtonState = BS_DISABLED;
	else
	{
		if ((lpDrawItemStruct->itemState & ODS_SELECTED) == ODS_SELECTED)
			m_ButtonState = BS_PRESSED;
		else
		{
			if (this->m_bIsChecked)
			{
				m_ButtonState = BS_CLICKED;
			}
		}
	}


	tButtonStyle tStyle;
	// Get default Style

	m_ptButtonStyle->GetButtonStyle(&tStyle);

	GetClientRect(m_rBtnSize);

	if (tStyle.m_BitmapScheme.m_Enabled != NULL) {
		if (!m_bHover) {
				DrawBitmap(pDC, m_pBitmapBackground, m_rBtnSize);
				DrawTransparentBitmap(pDC, tStyle.m_BitmapScheme.m_Enabled, m_rBtnSize);
		}
		else {
				DrawBitmap(pDC, m_pBitmapBackground, m_rBtnSize);
				DrawTransparentBitmap(pDC, tStyle.m_BitmapScheme.m_Hover, m_rBtnSize);
		}
	}
	else {

		COLORREF colorFace;
		COLORREF colorBorder;
		int boredeHeight;
		int boredeRadius;

		boredeHeight = tStyle.m_dHeightBorder;
		boredeRadius = tStyle.m_dRadius;

		switch (m_ButtonState)
		{
		case BS_DISABLED:
			colorFace = tStyle.m_ColorFace.m_Disabled;
			colorBorder = tStyle.m_ColorBorder.m_Disabled;

			break;
		case BS_ENABLED: {
			if (m_bHover) {
				colorFace = tStyle.m_ColorFace.m_Hover;
				colorBorder = tStyle.m_ColorBorder.m_Hover;
			} {
				colorFace = tStyle.m_ColorFace.m_Enabled;
				colorBorder = tStyle.m_ColorBorder.m_Enabled;
			}
		}
			break;
		case BS_CLICKED:
			colorFace = tStyle.m_ColorFace.m_Clicked;
			colorBorder = tStyle.m_ColorBorder.m_Clicked;

			break;
		case BS_PRESSED:
			colorFace = tStyle.m_ColorFace.m_Pressed;
			colorBorder = tStyle.m_ColorBorder.m_Pressed;

			break;
		case BS_HOT:
			colorFace = tStyle.m_ColorFace.m_Hover;
			colorBorder = tStyle.m_ColorBorder.m_Hover;

			break;
		default:
			colorFace = tStyle.m_ColorFace.m_Disabled;
			colorBorder = tStyle.m_ColorBorder.m_Disabled;

			break;
		}

	


		HBRUSH      brCross = CreateSolidBrush(colorFace);
		auto oldBrush = ::SelectObject(pDC->m_hDC, brCross);

		HPEN hLinePen = CreatePen(PS_SOLID, boredeHeight, colorBorder);
		HPEN hPenOld = (HPEN)SelectObject(pDC->m_hDC, hLinePen);

		pDC->GetWindow()->SetFont(&m_BtnFont, FALSE);


		::RoundRect(pDC->m_hDC, m_rBtnSize.left, m_rBtnSize.top, m_rBtnSize.right, m_rBtnSize.bottom, boredeRadius, boredeRadius);
		DrawButtonCaption(pDC);

		::SelectObject(pDC->m_hDC, oldBrush);
		DeleteObject(brCross);

		SelectObject(pDC->m_hDC, hPenOld);
		DeleteObject(hPenOld);

		DrawButtonCaption(pDC);

	}
	
}


BEGIN_MESSAGE_MAP(CRoundButton, CButton)
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_CAPTURECHANGED()
ON_WM_ERASEBKGND()
ON_WM_DRAWITEM()
ON_WM_MOUSEHOVER()
ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()
void CRoundButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bIsCheckButton)
	{
		m_bIsChecked = !m_bIsChecked;
	}
	if (m_bIsRadioButton)
	{
		m_bIsChecked = true;
	}

	CButton::OnLButtonUp(nFlags, point);
	
}
void CRoundButton::OnMouseMove(UINT nFlags, CPoint point)
{
	//start tracking of Hover and Leave Event
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	tme.dwHoverTime = 10;
	TrackMouseEvent(&tme);
	CButton::OnMouseMove(nFlags, point);
}
void CRoundButton::OnCaptureChanged(CWnd *pWnd)
{
	if (GetCapture() != this)
	{
		m_bMouseOnButton = false;
		if (m_bIsHotButton)
			Invalidate();
	}
	CButton::OnCaptureChanged(pWnd);
	
}

void CRoundButton::SaveBaskgroundImage(HDC _hDC) {
	if (m_pBitmapBackground == NULL) {
		m_pBitmapBackground = new CBitmap();

		HWND parentWindow = ::GetParent(m_hWnd);
		HDC parentDC = ::GetDC(parentWindow);

		CRect rectImage;
		::GetClientRect(m_hWnd, rectImage);
		::MapWindowPoints(m_hWnd, parentWindow, (LPPOINT)(&rectImage), (sizeof(RECT) / sizeof(POINT)));

		HDC hdcImage = CreateCompatibleDC(_hDC);
		HBITMAP hbmp = ::CreateCompatibleBitmap(_hDC, rectImage.Width(), rectImage.Height());
		auto restore = SelectObject(hdcImage, hbmp);

		::BitBlt(hdcImage, 0, 0, rectImage.Width(), rectImage.Height(), parentDC, rectImage.left, rectImage.top, SRCCOPY);
		m_pBitmapBackground->Attach(CopyImage(hbmp, IMAGE_BITMAP, 0, 0, 0));

		SelectObject(hdcImage, restore);
		DeleteObject(hbmp);
		DeleteDC(hdcImage);

		CImage image;
	}
}

BOOL CRoundButton::OnEraseBkgnd(CDC* pDC)
{
	CRect rectWindow;
	::GetClientRect(m_hWnd, rectWindow);
	SaveBaskgroundImage(pDC->m_hDC);
	DrawBitmap(pDC, m_pBitmapBackground, rectWindow);
	return TRUE;
}

void CRoundButton::DrawBitmap(CDC  *dc, CBitmap * bitmap, RECT &rect) {
	BITMAP bm = { 0 };
	bitmap->GetBitmap(&bm);
	auto size = CSize(bm.bmWidth, bm.bmHeight);

	// Get paint field
	CDC dcMem;
	dcMem.CreateCompatibleDC(dc);
	CBitmap* pOldBitmap = dcMem.SelectObject(bitmap);
	int mode;

	mode = SetStretchBltMode(dc->m_hDC, STRETCH_HALFTONE);
	dc->StretchBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, &dcMem, 0, 0, size.cx, size.cy, SRCCOPY);
	SetStretchBltMode(dc->m_hDC, mode);
	dcMem.SelectObject(pOldBitmap);
	dcMem.DeleteDC();
}

void CRoundButton::DrawTransparentBitmap(CDC* dc, CBitmap* bitmap, RECT& rect) {
	BITMAP bm = { 0 };
	bitmap->GetBitmap(&bm);
	auto size = CSize(bm.bmWidth, bm.bmHeight);

	// Get paint field
	CDC dcMem;
	dcMem.CreateCompatibleDC(dc);
	CBitmap* pOldBitmap = dcMem.SelectObject(bitmap);
	int mode;

	mode = SetStretchBltMode(dc->m_hDC, STRETCH_HALFTONE);
	::TransparentBlt(dc->m_hDC, rect.left, rect.top, rect.right - rect.left, 
		rect.bottom - rect.top, dcMem, 0, 0, size.cx, size.cy, GetPixel(dcMem, 0, 0));
	SetStretchBltMode(dc->m_hDC, mode);
	dcMem.SelectObject(pOldBitmap);
	dcMem.DeleteDC();
}

void CRoundButton::DrawTransparentBitmap(CDC* pTargetDC, int x, int y, int nWidth, int nHeight, CDC* pSrcDC,
	int xSrc, int ySrc, DWORD dwRop) {

	int mode = SetStretchBltMode(pTargetDC->m_hDC, STRETCH_HALFTONE);
	auto oldMode = pTargetDC->SetBkMode(TRANSPARENT);
	::TransparentBlt(pTargetDC->m_hDC, x, y, nWidth, nHeight, pSrcDC->m_hDC, 0, 0, nWidth, nHeight, RGB(100, 100, 100));
	SetStretchBltMode(pTargetDC->m_hDC, mode);
	pTargetDC->SetBkMode(oldMode);
}



void CRoundButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}






void CRoundButton::OnMouseHover(UINT nFlags, CPoint point)
{
	if (!m_bHover) {
		m_bHover = true;
		Invalidate();
	}

	CButton::OnMouseHover(nFlags, point);
}


void CRoundButton::OnMouseLeave()
{
		m_bHover = false;
		Invalidate();

	CButton::OnMouseLeave();
}
