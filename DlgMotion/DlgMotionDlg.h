
// DlgMotionDlg.h : ��� ����
//

#pragma once

#include "Devices/EtherCat.h"

enum OnOffAction { OFF, ON };


// CDlgMotionDlg ��ȭ ����
class CDlgMotionDlg : public CDialog
{
	CEtherCat *m_pEtherCat;

	void Init();
	void Close();

// �����Դϴ�.
public:
	CDlgMotionDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGMOTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
