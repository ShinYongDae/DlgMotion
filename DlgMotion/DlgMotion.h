
// DlgMotion.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDlgMotionApp:
// �� Ŭ������ ������ ���ؼ��� DlgMotion.cpp�� �����Ͻʽÿ�.
//

class CDlgMotionApp : public CWinApp
{
public:
	CDlgMotionApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDlgMotionApp theApp;