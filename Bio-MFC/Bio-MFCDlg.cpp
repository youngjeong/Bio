
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
}

BEGIN_MESSAGE_MAP(CBioMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CBioMFCDlg::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON5, &CBioMFCDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CBioMFCDlg �޽��� ó����

BOOL CBioMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ImageButton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_ImageButton.m_bTransparent = TRUE;
	m_ImageButton.m_bDrawFocus = FALSE;

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
	}
}


void CBioMFCDlg::OnBnClickedButton5()
{
	const int Threshold = 85; // Threshold ����

	IplImage *image = cvLoadImage(((string)(CStringA)m_filePath).c_str());
	IplImage *grayimg = 0;
	IplImage *outimg = 0;

	/* ����ȭ */
	if (!outimg)
	{
		grayimg = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
		outimg = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	}

	cvCvtColor(image, grayimg, CV_RGB2GRAY); // ����̹����� ��ȯ
	cvThreshold(grayimg, outimg, Threshold, 255, CV_THRESH_BINARY); // ����ȭ
	outimg->origin = image->origin; // �������� ������ �����
	
	cvSaveImage("binary.jpg", outimg);
	
	CRect rect;
	this->GetWindowRect(&rect);

	cvNamedWindow("result", 0);
	cvResizeWindow("result", rect.Width(), rect.Height());
	cvMoveWindow("result", rect.left, rect.top);
	cvShowImage("result", outimg);
	cvWaitKey(0);
	cvReleaseImage(&outimg);
	cvDestroyWindow("result");	

	/* ��������(��â -> ħ��) */
	IplImage *src = cvLoadImage("binary.jpg", -1);
	IplImage *dst = cvCloneImage(src);
	
	for (int i = 0; i < src->width; i++) {
		for (int j = 0; j < src->height; j++) {
			if ((src->imageData)[src->height * i + j] == 0) {
				(src->imageData)[src->height * i + j] = 255;
			}
			else {
				(src->imageData)[src->height * i + j] = 0;
			}
		}
	}
	dst = cvCloneImage(src);

	cvDilate(src, dst, NULL, 1);
	src = cvCloneImage(dst);
	cvErode(src, dst, NULL, 3);
	src = cvCloneImage(dst);
	cvDilate(src, dst, NULL, 2);
	src = cvCloneImage(dst);

	vector<int> hair;
	IplImage *visit_check = cvCloneImage(dst);
	for (int i = 0; i < visit_check->height; i++) {
		for (int j = 0; j < visit_check->width; j++) {
			if (visit_check->imageData[visit_check->width * i + j] != 0) {
				int area = bfs(visit_check, i, j);
				if (area > 50) {
					hair.push_back(area);
				}
				else {
					bfs(dst, i, j);
				}
			}
		}
	}

	//Thinning(src, src->width, src->height);
	//dst = cvCloneImage(src);

	/*
	for (int i = 1; i <= 1; i++) {
		cvDilate(src, dst, NULL, 3);
		src = cvCloneImage(dst);
		Thinning(src, src->width, src->height);
		dst = cvCloneImage(src);
	}
	*/

	//cvDilate(src, dst, NULL, 1);
	//src = cvCloneImage(dst);

	//dst = cvCloneImage(src);

	//cvErode(src, dst, NULL, 3);
	//src = cvCloneImage(dst);
	//cvDilate(src, dst, NULL, 5);
	
	cvNamedWindow("result2", 0);
	cvResizeWindow("result2", rect.Width(), rect.Height());
	cvMoveWindow("result2", rect.left, rect.top);
	cvShowImage("result2", dst);
	cvWaitKey(0);
	cvReleaseImage(&dst);
	cvDestroyWindow("result");

	/* ��ȯ�� �̹��� ��� */
	//TODO

	/*
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
	*/
}

void CBioMFCDlg::Thinning(IplImage * input_, int col, int row)
{
	cv::Mat input = cv::cvarrToMat(input_);
	int x, y, p, q, xp, yp, xm, ym, cc, cd;
	int np1, sp1, hv;
	int cnt = 0, chk = 0, flag = 0;

	unsigned char *m_BufImage;
	unsigned char *m_ResultImg;
	m_BufImage = (unsigned char*)malloc(sizeof(unsigned char)*row*col);
	m_ResultImg = (unsigned char*)malloc(sizeof(unsigned char)*row*col);

	// Result image�� Mat format�� input image Copy
	for (y = 0; y < row; y++) {
		for (x = 0; x < col; x++) {
			*(m_ResultImg + (col*y) + x) = input.at<uchar>(y, x);
		}
	}

	do {
		// Image Buffer�� 0���� ����
		for (y = 1; y < row - 1; y++) {
			for (x = 1; x < col - 1; x++) {
				*(m_BufImage + (col*y) + x) = 0;
			}
		}

		// õ�� ����
		if (chk == 0) flag = 0;
		chk = cnt % 2;
		cnt++;

		for (y = 1; y < row - 1; y++) {
			ym = y - 1;
			yp = y + 1;
			for (x = 1; x < col - 1; x++) {
				if (*(m_ResultImg + (col*y) + x) == 0) continue;

				np1 = 0;
				for (q = y - 1; q <= y + 1; q++) {
					for (p = x - 1; p <= x + 1; p++) {
						if (*(m_ResultImg + (col*q) + p) != 0) np1++;
					}
				}

				if (np1 < 3 || np1 > 7) {
					*(m_BufImage + (col*y) + x) = 255;
					continue;
				}

				xm = x - 1;
				xp = x + 1;
				sp1 = 0;

				if (*(m_ResultImg + (col*ym) + x) == 0 && *(m_ResultImg + (col*ym) + xp) != 0) sp1++;
				if (*(m_ResultImg + (col*ym) + xp) == 0 && *(m_ResultImg + (col*y) + xp) != 0) sp1++;
				if (*(m_ResultImg + (col*y) + xp) == 0 && *(m_ResultImg + (col*yp) + xp) != 0) sp1++;
				if (*(m_ResultImg + (col*yp) + xp) == 0 && *(m_ResultImg + (col*yp) + x) != 0) sp1++;
				if (*(m_ResultImg + (col*yp) + x) == 0 && *(m_ResultImg + (col*yp) + xm) != 0) sp1++;
				if (*(m_ResultImg + (col*yp) + xm) == 0 && *(m_ResultImg + (col*y) + xm) != 0) sp1++;
				if (*(m_ResultImg + (col*y) + xm) == 0 && *(m_ResultImg + (col*ym) + xm) != 0) sp1++;
				if (*(m_ResultImg + (col*ym) + xm) == 0 && *(m_ResultImg + (col*ym) + x) != 0) sp1++;

				if (sp1 != 1) {
					*(m_BufImage + (col*y) + x) = 255;
					continue;
				}

				if (chk == 0) {
					cc = *(m_ResultImg + (col*ym) + x) * *(m_ResultImg + (col*y) + xp);
					cc = cc * *(m_ResultImg + (col*yp) + x);

					cd = *(m_ResultImg + (col*y) + xp) * *(m_ResultImg + (col*yp) + x);
					cd = cd * *(m_ResultImg + (col*y) + xm);
				}
				else {
					cc = *(m_ResultImg + (col*ym) + x) * *(m_ResultImg + (col*y) + xp);
					cc = cc * *(m_ResultImg + (col*y) + xm);

					cd = *(m_ResultImg + (col*ym) + x) * *(m_ResultImg + (col*yp) + x);
					cd = cd * *(m_ResultImg + (col*y) + xm);
				}

				if (cc != 0 || cd != 0) {
					*(m_BufImage + (col*y) + x) = 255;
					continue;
				}
				flag = 1;
			}
		}

		for (y = 1; y < row - 1; y++) {
			for (x = 1; x < col - 1; x++) {
				*(m_ResultImg + (col*y) + x) = *(m_BufImage + (col*y) + x);
			}
		}
	} while (!(chk == 1 && flag == 0));

	// 4������ ó��
	for (y = 1; y < row - 1; y++) {
		yp = y + 1;
		ym = y - 1;
		for (x = 1; x < col - 1; x++) {
			if (*(m_ResultImg + (col*y) + x) == 0) continue;

			xm = x - 1;
			xp = x + 1;
			sp1 = 0;
			if (*(m_ResultImg + (col*ym) + x) == 0 && *(m_ResultImg + (col*ym) + xp) != 0) sp1++;
			if (*(m_ResultImg + (col*ym) + xp) == 0 && *(m_ResultImg + (col*y) + xp) != 0) sp1++;
			if (*(m_ResultImg + (col*y) + xp) == 0 && *(m_ResultImg + (col*yp) + xp) != 0) sp1++;
			if (*(m_ResultImg + (col*yp) + xp) == 0 && *(m_ResultImg + (col*yp) + x) != 0) sp1++;
			if (*(m_ResultImg + (col*yp) + x) == 0 && *(m_ResultImg + (col*yp) + xm) != 0) sp1++;
			if (*(m_ResultImg + (col*yp) + xm) == 0 && *(m_ResultImg + (col*y) + xm) != 0) sp1++;
			if (*(m_ResultImg + (col*y) + xm) == 0 && *(m_ResultImg + (col*ym) + xm) != 0) sp1++;
			if (*(m_ResultImg + (col*ym) + xm) == 0 && *(m_ResultImg + (col*ym) + x) != 0) sp1++;

			hv = 0;
			if (sp1 == 2) {
				if ((*(m_ResultImg + (col*ym) + x) & *(m_ResultImg + (col*y) + xp)) != 0) hv++;
				else if ((*(m_ResultImg + (col*y) + xp) & *(m_ResultImg + (col*yp) + x)) != 0) hv++;
				else if ((*(m_ResultImg + (col*yp) + x) & *(m_ResultImg + (col*y) + xm)) != 0) hv++;
				else if ((*(m_ResultImg + (col*y) + xm) & *(m_ResultImg + (col*ym) + x)) != 0) hv++;

				if (hv == 1) *(m_ResultImg + (col*y) + x) = 0;
			}
			else if (sp1 == 3) {
				if ((*(m_ResultImg + (col*ym) + x) & *(m_ResultImg + (col*y) + xm) & *(m_ResultImg + (col*y) + xp)) != 0) hv++;
				else if ((*(m_ResultImg + (col*yp) + x) & *(m_ResultImg + (col*y) + xm) & *(m_ResultImg + (col*y) + xp)) != 0) hv++;
				else if ((*(m_ResultImg + (col*ym) + x) & *(m_ResultImg + (col*yp) + x) & *(m_ResultImg + (col*y) + xm)) != 0) hv++;
				else if ((*(m_ResultImg + (col*ym) + x) & *(m_ResultImg + (col*yp) + x) & *(m_ResultImg + (col*y) + xp)) != 0) hv++;

				if (hv == 1) *(m_ResultImg + (col*y) + x) = 0;
			}
		}
	}

	// ���� �迭�� �纹��
	for (y = 0; y < row; y++) {
		for (x = 0; x < col; x++) {
			input.at<uchar>(y, x) = *(m_ResultImg + (col*y) + x);
		}
	}

	*input_ = input;

	free(m_BufImage);
	free(m_ResultImg);
}

int CBioMFCDlg::bfs(IplImage * visit, int _x, int _y) {
	int xx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
	int yy[8] = { 1, -1, 0, 0, 1, -1, 1, -1};
	int ret = 0;

	auto inner = [&](int nx, int ny) {
		return 0 <= nx && nx < visit->height && 0 <= ny && ny < visit->width;
	};

	using pii = pair<int, int>;
	queue<pii> qu;

	qu.push(pii(_x, _y));
	visit->imageData[visit->width * _x + _y] = 0;

	while (!qu.empty()) {
		int x, y;
		tie(x, y) = qu.front();
		qu.pop();
		ret++;

		for (int i = 0; i < 8; i++) {
			if (inner(x + xx[i], y + yy[i]) && visit->imageData[visit->width * (x + xx[i]) + y + yy[i]] != 0) {
				visit->imageData[visit->width * (x + xx[i]) + y + yy[i]] = 0;
				qu.push(pii(x + xx[i], y + yy[i]));
			}
		}
	}
	
	return ret;
}