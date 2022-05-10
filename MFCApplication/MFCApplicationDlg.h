
// MFCApplicationDlg.h : header file
//

#pragma once


#include "stdafx.h"

#include "../NVRControls/CRoundButton.h"
#include "../NVRControls/CRoundButtonStyle.h"


// CMFCApplicationDlg dialog
class CMFCApplicationDlg : public CDialogEx
{
// Construction
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CRoundButton m_RoundButton1;
	CRoundButton m_RoundButton2;
	CRoundButtonStyle m_RoundButton2_Style;
	CRoundButton m_CircleButton;
	CRoundButton m_ImageButton;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
