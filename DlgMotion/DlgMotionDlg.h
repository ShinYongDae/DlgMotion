
// DlgMotionDlg.h : 헤더 파일
//

#pragma once

#include "Devices/EtherCat.h"

#define MAX_THREAD				1
#define TIM_DISP_ENC			0

enum OnOffAction { OFF, ON };


// CDlgMotionDlg 대화 상자
class CDlgMotionDlg : public CDialog
{
	CEtherCat *m_pEtherCat;
	double m_dEncAct[MAX_AXIS], m_dEncCmd[MAX_AXIS];
	int m_nStatus[MAX_AXIS];
	BOOL m_bTIM_DISP_ENC;

	void Init();
	void Close();

	void ThreadInit();
	void ThreadKill();

	void DispEnc();
	void DispStatus();
	void DispMotorType();

// 생성입니다.
public:
	CDlgMotionDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CDlgMotionDlg();

	DWORD m_dwThreadTick[MAX_THREAD];
	BOOL m_bThread[MAX_THREAD];
	CThreadTask m_Thread[MAX_THREAD];
	static UINT ThreadProc0(LPVOID lpContext);
	void GetEnc();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGMOTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
};
