
//
// Author:  Vladimir Novick
//          vlad.novick@gmail.com
//

#pragma once
#include "StdAfx.h"
#include "CRoundButtonStyle.h"

class CRoundButton :
	public CButton
{
public:
	CRoundButton(void);
	~CRoundButton(void);
	int GetFontHeight(int nPointSize);
	bool SetButtonStyle(CRoundButtonStyle* _ptDesignRoundButtonStyle);
	bool GetFont(LOGFONT* _ptLogFont);
	bool SetFont(LOGFONT* _ptLogFont);
	bool GetTextColor(tColorScheme* _ptTextColor);
	bool SetTextColor(tColorScheme* _ptTextColor);
	void SetCheckButton(bool _bCheckButton) { m_bIsCheckButton = _bCheckButton; };
	bool GetCheckButton() { return m_bIsCheckButton; };
	void SetRadioButton(bool _bRadioButton) { m_bIsRadioButton = _bRadioButton; };
	bool GetRadioButton() { return m_bIsRadioButton; };
	void SetHotButton(bool _bHotButton) { m_bIsHotButton = _bHotButton; };
	bool GetHotButton() { return m_bIsHotButton; };
	void SetCheck(bool _bIsChecked) { m_bIsChecked = _bIsChecked; Invalidate(); };
	bool GetCheck() { return m_bIsChecked; };

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

protected:
	void GenButtonBMPs(CDC* _pDC, CRect _rRect);
	void DrawButtonCaption(CDC* _pDC);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
private:
	BOOL m_bHover;
	BOOL m_bMouseTracking;
	void SaveBaskgroundImage(HDC _hDC);
	CBitmap* m_pBitmapBackground;
	CRect	m_rBtnSize;
	CBitmap	m_BmpBtn;
	CFont	m_BtnFont;
	LOGFONT	m_LogFont;
	tColorScheme	m_TextColor;
	CString m_sOldCaption;
	bool	m_bDefaultButton;
	bool	m_bIsCheckButton;
	bool	m_bIsRadioButton;
	bool m_bIsHotButton;
	bool	m_bIsChecked;
	bool m_bMouseOnButton;
	bool	m_bRedraw;
	ButtonState m_ButtonState;
	CRoundButtonStyle *m_ptButtonStyle;
	void DrawTransparentBitmap(CDC* pTargetDC, int x, int y, int nWidth, int nHeight, CDC* pSrcDC,
		int xSrc, int ySrc, DWORD dwRop);
	void DrawTransparentBitmap(CDC* dc, CBitmap* bitmap, RECT& rect);
	void DrawBitmap(CDC* dc, CBitmap* bitmap, RECT& rect);
public:
	afx_msg void OnCaptureChanged(CWnd* pWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};