
// DlgMotionDlg.h : 헤더 파일
//

#pragma once
#include <thread>
#include "Devices/EtherCat.h"
#include "MyBtn.h"

#define MAX_THREAD				1
#define TIM_DISP_ENC			0

enum OnOffAction { OFF, ON };

#define PATH_REPEAT_CONF		_T("RepeatConf.ini")

typedef struct stRepeatTest
{
	int			nAxis, nRepeat;
	double		dPosStart, dStep, dPosEnd;
	BOOL		bReverse, bOptimize, bManual;

	stRepeatTest()
	{
		nAxis = -1;
		nRepeat = 0;
		dPosStart = 0.0;
		dStep = 0.0;
		dPosEnd = 0.0;
		bReverse = FALSE;
		bOptimize = FALSE;
		bManual = FALSE;
	}
}RptTest;


// CDlgMotionDlg 대화 상자
class CDlgMotionDlg : public CDialog
{
	BOOL m_bThreadAlive;
	std::thread t0;
	void ThreadStart();
	void ThreadStop();

	CEtherCat *m_pEtherCat;
	int m_nStatus[MAX_AXIS];
	BOOL m_bTIM_DISP_ENC;
	int m_nCurSelMaster, m_nCurSelSlaver, m_nCurSelRepeatAxis, m_nCurSelAxis;
	CMyBtn myBtnJogP[4], myBtnJogM[4];

	double m_dEncAct[MAX_AXIS], m_dEncCmd[MAX_AXIS];
	unsigned long m_ulDispIn, m_ulDispOut, m_ulOut;

	void InitDlg();
	BOOL Init();
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
	BOOL Move(int nID, double dTgtPos, BOOL bOptimize = FALSE);
	BOOL Move(int nID, CWnd* pWndTgtPos, CWnd* pWndSpd, CWnd* pWndAcc, CWnd* pWndDec);

	stRepeatTest m_stRepeatConf;
	void DispRepeatConf();
	void LoadRepeatConf();
	void SaveRepeatConf();
	void StartRepeatTest();
	void StopRepeatTest();

	BOOL m_bRepeatTest, m_bReverse, m_bStepNext;
	int m_nStepRptTest, m_nRepeat, m_nMoveStep;
	void DoRepeatTest();
	void UpdateRepeatConf();
	void EnableCtrl(BOOL bEnable=TRUE);
	BOOL MovePosSt();
	BOOL MoveStep();
	BOOL MovePosEnd();
	BOOL IsPosEnd();
	BOOL IsMoveDone();
	BOOL IsInc();
	void DispBlank();
	void DispPos(double dPosCmd, double dPosAct);
	void ResetRepeatTest();
	BOOL IsRepeatCount();
	void IncRepeat();
	void ResetRepeat();
	void DispProgress();
	double GetProgress();
	void IncMoveStep();
	void ResetMoveStep();
	void DoStepNext(BOOL bNext);
	void DispChangeAxis(int nAxis=0);
	void DispAix();
	void DispMotorEnable(int nWndIdx);

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

	static void ProcThrd0(const LPVOID lpContext);
	BOOL IsRepeatTest();
	BOOL IsStepNext();
	BOOL IsManual();
	CString GetDateTime();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGMOTION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

protected:
	BOOL Proc0();
	BOOL ThreadIsAlive();

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
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnBnClickedCheck27();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedCheck29();
	afx_msg void OnBnClickedCheck30();
	afx_msg void OnSelchangeCombo4();
};
