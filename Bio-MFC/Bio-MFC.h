
// Bio-MFC.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CBioMFCApp:
// �� Ŭ������ ������ ���ؼ��� Bio-MFC.cpp�� �����Ͻʽÿ�.
//

class CBioMFCApp : public CWinApp
{
public:
	CBioMFCApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBioMFCApp theApp;