
// Bio-MFCDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "opencv2/opencv.hpp"
#include "highgui.h"
#include "cv.h"
#include <iostream>

// CBioMFCDlg ��ȭ ����
class CBioMFCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CBioMFCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BIOMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	void OnDraw(CDC* pDC);
	void setButtonImage(CMFCButton &button, LPCTSTR str);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSize	m_Size;
	int		m_nWidthByte;
	HBITMAP original;
	CString m_filePath;
	cv::Mat img;

	HBITMAP proceed1;
	HBITMAP proceed2;
	CMFCButton m_proceed1;
	CMFCButton m_proceed2;
	BYTE* m_pProceed1;
	BYTE* m_pProceed2;
	CMFCButton m_ImageButton;
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	void Thinning(IplImage * input_, int row, int col);
	int bfs(IplImage * visit, int x, int y);
};
