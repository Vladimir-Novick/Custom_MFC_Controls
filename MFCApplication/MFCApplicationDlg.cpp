
// MFCApplicationDlg.cpp : implementation file
//
#define WINVER 0x0501

#include "stdafx.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include "..\NVRControls\CWinUtils.h"
#include "..\NVRControls\CRoundButtonStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationDlg dialog



CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_RoundButton1);
	DDX_Control(pDX, IDC_BUTTON2, m_RoundButton2);
	DDX_Control(pDX, IDC_BUTTON3, m_CircleButton);
	DDX_Control(pDX, IDC_BUTTON4, m_ImageButton);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMFCApplicationDlg message handlers

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	{
		LOGFONT tFont;
		m_RoundButton2.SetButtonStyle(&m_RoundButton2_Style);
		m_RoundButton2.GetFont(&tFont);  // Get default font
		lstrcpy(tFont.lfFaceName, _T("Tahoma")); // _NOTRANSLATE_
		tFont.lfWeight = FW_SEMIBOLD;
		tFont.lfHeight = CWinUtils::GetFontHeight(14);
		m_RoundButton2.SetFont(&tFont);
	}


	{
		tColorScheme tColor;
		m_RoundButton2.GetTextColor(&tColor); // Get default button color schema

		tColor.m_Hover = RGB(200, 10, 10);
		tColor.m_Enabled = RGB(40, 40, 40);
		tColor.m_Clicked = RGB(100, 100, 100);
		tColor.m_Pressed = RGB(100, 100, 100);

		m_RoundButton2.SetTextColor(&tColor);


		// Structure containing Style
		tButtonStyle tStyle;
		// Get default Style
		m_RoundButton2_Style.GetButtonStyle(&tStyle);

		tStyle.m_ColorBorder.m_Hover = RGB(255, 255, 255);
		tStyle.m_ColorFace.m_Enabled = RGB(100, 255, 40);
		tStyle.m_ColorBorder.m_Enabled = RGB(150, 150, 150);

		tStyle.m_ColorFace.m_Clicked = RGB(200, 200, 200);
		tStyle.m_ColorBorder.m_Clicked = RGB(100, 100, 100);

		tStyle.m_ColorFace.m_Pressed = RGB(200, 200, 200);
		tStyle.m_ColorBorder.m_Pressed = RGB(100, 100, 100);
		tStyle.m_dRadius = 45;

		m_RoundButton2_Style.SetButtonStyle(&tStyle);


	}



	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CMFCApplicationDlg::OnEraseBkgnd(CDC* pDC)
{
	HWND hwnd = m_hWnd;
	CWinUtils::SetGradientsDC(hwnd, pDC->m_hDC,
		RGB(95, 177, 219),
		RGB(180, 226, 227)
	);

	return TRUE;
}
