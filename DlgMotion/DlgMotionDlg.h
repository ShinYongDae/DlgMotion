
// DlgMotionDlg.h : 헤더 파일
//

#pragma once

#include "Devices/EtherCat.h"
#include "MyBtn.h"

#define MAX_THREAD				1
#define TIM_DISP_ENC			0

enum OnOffAction { OFF, ON };


// CDlgMotionDlg 대화 상자
class CDlgMotionDlg : public CDialog
{
	CEtherCat *m_pEtherCat;
	int m_nStatus[MAX_AXIS];
	BOOL m_bTIM_DISP_ENC;
	int m_nCurSelMaster, m_nCurSelSlaver;
	CMyBtn myBtnJogP[4], myBtnJogM[4];

	double m_dEncAct[MAX_AXIS], m_dEncCmd[MAX_AXIS];
	unsigned long m_ulDispIn, m_ulDispOut, m_ulOut;

	void InitDlg();
	void Init();
	void InitBtn();
	void Close();

	void ThreadInit();
	void ThreadKill();

	void DispEnc();
	void DispStatus();
	void DispMotorType();
	void DispMoveConf();
	void DispLimitSens();
	void DispIoIn();
	void DispIoOut();

	void SetIoOut();

	void CheckBtnStatus();

	void InitCombo();
	CString GetMotorName(int nID);

	BOOL Move(int nID, CWnd* pWndTgtPos, CWnd* pWndSpd, CWnd* pWndAcc, CWnd* pWndDec);

// 생성입니다.
public:
	CDlgMotionDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CDlgMotionDlg();

	DWORD m_dwThreadTick[MAX_THREAD];
	BOOL m_bThread[MAX_THREAD];
	CThreadTask m_Thread[MAX_THREAD];
	static UINT ThreadProc0(LPVOID lpContext);
	void GetEnc();
	void GetIoIn();
	void GetIoOut();

	void SwMyBtnDown(int nCtrlID);
	void SwMyBtnUp(int nCtrlID);
	void ResetMotion(int nMsId);

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
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnBnClickedCheck21();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();

	afx_msg LRESULT OnMyBtnDown(WPARAM wPara, LPARAM lPara);
	afx_msg LRESULT OnMyBtnUp(WPARAM wPara, LPARAM lPara);
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedCheck22();
	afx_msg void OnBnClickedCheck23();
	afx_msg void OnBnClickedCheck24();
	afx_msg void OnBnClickedCheck25();
};
