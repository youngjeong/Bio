
// Bio-MFCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Bio-MFC.h"
#include "Bio-MFCDlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include "highgui.h"
#include "cv.h"
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/HEAP:400000000")


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CBioMFCDlg 대화 상자



CBioMFCDlg::CBioMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BIOMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBioMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_ImageButton);
	DDX_Control(pDX, IDC_BUTTON3, m_proceed1);
	DDX_Control(pDX, IDC_BUTTON1, m_proceed2);
}

BEGIN_MESSAGE_MAP(CBioMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CBioMFCDlg::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON5, &CBioMFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CBioMFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CBioMFCDlg 메시지 처리기

BOOL CBioMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont g_editFont;

	m_ImageButton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_ImageButton.m_bTransparent = TRUE;
	m_ImageButton.m_bDrawFocus = FALSE;

	m_proceed1.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_proceed1.m_bTransparent = TRUE;
	m_proceed1.m_bDrawFocus = FALSE;

	m_proceed2.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_proceed2.m_bTransparent = TRUE;
	m_proceed2.m_bDrawFocus = FALSE;

	g_editFont.CreatePointFont(200, TEXT("굴림"));

	GetDlgItem(IDC_EDIT1)->SetFont(&g_editFont);
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(L"탈모일까요 아닐까요?");

	setButtonImage(m_ImageButton, L"../button.png");

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBioMFCDlg::setButtonImage(CMFCButton &button, LPCTSTR str)
{
	CImage cButtonImage;
	HRESULT hRes = cButtonImage.Load(str);

	if (hRes != S_OK)
		return;

	original = cButtonImage.Detach();

	button.SetImage(original, TRUE);
}

void CBioMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBioMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		OnDraw(&dc);
		CDialogEx::OnPaint();
	}
}

void CBioMFCDlg::OnDraw(CDC* pDC)
{

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBioMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBioMFCDlg::OnBnClickedButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog ins_dlg(TRUE, NULL, NULL, 6UL, L"Image Files (*.*)|*.*||");
	// 파일 대화상자 실행
	if (ins_dlg.DoModal() == IDOK) {
		setButtonImage(m_ImageButton, ins_dlg.GetPathName());
		m_filePath = ins_dlg.GetPathName();
		//get filepath to Mat class
	}
}


void CBioMFCDlg::OnBnClickedButton5()
{
	proceed1 = (HBITMAP)LoadImage(NULL, m_filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	BITMAP bmp_info;
	int err = GetObject(proceed1, sizeof(bmp_info), &bmp_info);

	m_Size.cx = bmp_info.bmWidth;
	m_Size.cy = bmp_info.bmHeight;
	m_nWidthByte = bmp_info.bmWidthBytes;

	m_pProceed1 = new BYTE[bmp_info.bmWidthBytes * bmp_info.bmHeight * (bmp_info.bmBitsPixel / 8)];
	memset(m_pProceed1, 0, bmp_info.bmWidthBytes * bmp_info.bmHeight * (bmp_info.bmBitsPixel / 8));
	GetBitmapBits(proceed1, bmp_info.bmWidthBytes * bmp_info.bmHeight, m_pProceed1);
	
	//TODO : 갯수 카운팅

	//조작된 픽셀을 비트맵에 넣기
	SetBitmapBits(proceed1, m_Size.cx * m_Size.cy * 3, m_pProceed1);
	m_proceed1.SetImage(proceed1, TRUE);
	Invalidate();
}


void CBioMFCDlg::OnBnClickedButton4()
{
	proceed2 = (HBITMAP)LoadImage(NULL, m_filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	BITMAP bmp_info;
	int err = GetObject(proceed2, sizeof(bmp_info), &bmp_info);

	m_Size.cx = bmp_info.bmWidth;
	m_Size.cy = bmp_info.bmHeight;
	m_nWidthByte = bmp_info.bmWidthBytes;

	m_pProceed2 = new BYTE[bmp_info.bmWidthBytes * bmp_info.bmHeight * (bmp_info.bmBitsPixel / 8)];
	memset(m_pProceed2, 0, bmp_info.bmWidthBytes * bmp_info.bmHeight * (bmp_info.bmBitsPixel / 8));
	GetBitmapBits(proceed2, bmp_info.bmWidthBytes * bmp_info.bmHeight, m_pProceed2);
	
	//TODO : 굵기 측정

	//조작된 픽셀을 비트맵에 넣기
	SetBitmapBits(proceed2, m_Size.cx * m_Size.cy * 3, m_pProceed2);
	m_proceed2.SetImage(proceed2, TRUE);
	Invalidate();
}
