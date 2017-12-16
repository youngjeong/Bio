
// Bio-MFCDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CBioMFCDlg ��ȭ ����



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


// CBioMFCDlg �޽��� ó����

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

	g_editFont.CreatePointFont(200, TEXT("����"));

	GetDlgItem(IDC_EDIT1)->SetFont(&g_editFont);
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(L"Ż���ϱ�� �ƴұ��?");

	setButtonImage(m_ImageButton, L"../button.png");

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CBioMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CBioMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBioMFCDlg::OnBnClickedButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog ins_dlg(TRUE, NULL, NULL, 6UL, L"Image Files (*.*)|*.*||");
	// ���� ��ȭ���� ����
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
	
	//TODO : ���� ī����

	//���۵� �ȼ��� ��Ʈ�ʿ� �ֱ�
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
	
	//TODO : ���� ����

	//���۵� �ȼ��� ��Ʈ�ʿ� �ֱ�
	SetBitmapBits(proceed2, m_Size.cx * m_Size.cy * 3, m_pProceed2);
	m_proceed2.SetImage(proceed2, TRUE);
	Invalidate();
}
