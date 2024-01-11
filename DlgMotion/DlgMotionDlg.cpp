
// DlgMotionDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "DlgMotion.h"
#include "DlgMotionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgMotionDlg 대화 상자



CDlgMotionDlg::CDlgMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLGMOTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pEtherCat = NULL;
	m_bThread[0] = FALSE;
	m_dwThreadTick[0] = 0;
	m_bTIM_DISP_ENC = FALSE;
	m_nCurSelMaster = -1;
	m_nCurSelSlaver = -1;
}

CDlgMotionDlg::~CDlgMotionDlg()
{
	Close();
}

void CDlgMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgMotionDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDlgMotionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgMotionDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, &CDlgMotionDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgMotionDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgMotionDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgMotionDlg::OnBnClickedCheck4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgMotionDlg::OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDlgMotionDlg::OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_CHECK21, &CDlgMotionDlg::OnBnClickedCheck21)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgMotionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgMotionDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgMotionDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgMotionDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgMotionDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgMotionDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgMotionDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgMotionDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgMotionDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlgMotionDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlgMotionDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CDlgMotionDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlgMotionDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgMotionDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CDlgMotionDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CDlgMotionDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON25, &CDlgMotionDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CDlgMotionDlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &CDlgMotionDlg::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &CDlgMotionDlg::OnBnClickedButton28)
	ON_MESSAGE(WM_MYBTN_DOWN, OnMyBtnDown)
	ON_MESSAGE(WM_MYBTN_UP, OnMyBtnUp)
	ON_BN_CLICKED(IDC_BUTTON29, &CDlgMotionDlg::OnBnClickedButton29)
END_MESSAGE_MAP()


// CDlgMotionDlg 메시지 처리기

BOOL CDlgMotionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	Init(); // Load MotionParam.ini

	DispMotorType();
	DispMoveConf();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
// 아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CDlgMotionDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
// 이 함수를 호출합니다.
HCURSOR CDlgMotionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDlgMotionDlg::Init()
{
	if (!m_pEtherCat)
	{
		m_pEtherCat = new CEtherCat(this);
		if (!m_pEtherCat->InitBoard())
		{
			AfxMessageBox(_T("XMP 보드 초기화 실패, 다시 시작하세요.!!!"));
			PostMessage(WM_CLOSE);
		}
	}

	m_pEtherCat->WriteBit(16, ON);   //MC_ON
	Sleep(300);

	SetIoOut();

	ThreadInit();	// GetEnc();

	CButton* pCtlChkBtn = NULL;

	pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	pCtlChkBtn->SetCheck(FALSE);
	pCtlChkBtn->SetWindowText(_T("OFF"));
	m_pEtherCat->ServoOnOff(0, FALSE);

	pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK2);
	pCtlChkBtn->SetCheck(FALSE);
	pCtlChkBtn->SetWindowText(_T("OFF"));
	m_pEtherCat->ServoOnOff(1, FALSE);

	pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK3);
	pCtlChkBtn->SetCheck(FALSE);
	pCtlChkBtn->SetWindowText(_T("OFF"));
	m_pEtherCat->ServoOnOff(2, FALSE);

	pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK4);
	pCtlChkBtn->SetCheck(FALSE);
	pCtlChkBtn->SetWindowText(_T("OFF"));
	m_pEtherCat->ServoOnOff(3, FALSE);

	m_bTIM_DISP_ENC = TRUE;
	SetTimer(TIM_DISP_ENC, 100, NULL);

	InitCombo();
}

void CDlgMotionDlg::InitBtn()
{
	myBtnJogM[0].SubclassDlgItem(IDC_BUTTON17, this);
	myBtnJogM[0].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON17);
	myBtnJogP[0].SubclassDlgItem(IDC_BUTTON18, this);
	myBtnJogP[0].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON18);

	myBtnJogM[1].SubclassDlgItem(IDC_BUTTON19, this);
	myBtnJogM[1].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON19);
	myBtnJogP[1].SubclassDlgItem(IDC_BUTTON20, this);
	myBtnJogP[1].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON20);

	myBtnJogM[2].SubclassDlgItem(IDC_BUTTON21, this);
	myBtnJogM[2].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON21);
	myBtnJogP[2].SubclassDlgItem(IDC_BUTTON22, this);
	myBtnJogP[2].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON22);

	myBtnJogM[3].SubclassDlgItem(IDC_BUTTON23, this);
	myBtnJogM[3].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON23);
	myBtnJogP[3].SubclassDlgItem(IDC_BUTTON24, this);
	myBtnJogP[3].SetHwnd(this->GetSafeHwnd(), IDC_BUTTON24);
}

void CDlgMotionDlg::Close()
{
	ThreadKill();

	m_bTIM_DISP_ENC = FALSE;

	if (m_pEtherCat)
	{
		delete m_pEtherCat;
		m_pEtherCat = NULL;
	}
}


void CDlgMotionDlg::ThreadInit()
{
	if (!m_bThread[0])
		m_Thread[0].Start(GetSafeHwnd(), this, ThreadProc0);
}


UINT CDlgMotionDlg::ThreadProc0(LPVOID lpContext)
{
	// Turn the passed in 'this' pointer back into a CProgressMgr instance
	CDlgMotionDlg* pThread = reinterpret_cast<CDlgMotionDlg*>(lpContext);

	DWORD dwTick = GetTickCount();
	DWORD dwShutdownEventCheckPeriod = 0; // thread shutdown event check period

	pThread->m_bThread[0] = TRUE;
	while (WAIT_OBJECT_0 != WaitForSingleObject(pThread->m_Thread[0].GetShutdownEvent(), dwShutdownEventCheckPeriod))
	{
		pThread->m_dwThreadTick[0] = GetTickCount() - dwTick;
		dwTick = GetTickCount();

		pThread->GetEnc();
		pThread->GetIoIn();
		pThread->GetIoOut();
		Sleep(30);
	}
	pThread->m_bThread[0] = FALSE;

	return 0;
}

void CDlgMotionDlg::GetEnc()
{
	if (!m_pEtherCat)
		return;

	for (int i = 0; i < m_pEtherCat->m_ParamCtrl.nTotAxis; i++)
	{
		m_dEncCmd[i] = m_pEtherCat->GetCommandPosition(i);
		m_dEncAct[i] = m_pEtherCat->GetActualPosition(i);
		m_nStatus[i] = m_pEtherCat->GetState(i);
	}
}

void CDlgMotionDlg::GetIoIn()
{
	if (!m_pEtherCat)
		return;

	m_ulDispIn = m_pEtherCat->ReadAllBit(TRUE);
}

void CDlgMotionDlg::GetIoOut()
{
	if (!m_pEtherCat)
		return;

	m_ulDispOut = m_pEtherCat->ReadAllBit(FALSE);
}

void CDlgMotionDlg::ThreadKill()
{
	if (m_bThread[0])
	{
		m_Thread[0].Stop();
		Sleep(20);
		while (m_bThread[0])
		{
			Sleep(20);
		}
	}
}

void CDlgMotionDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Close();

	CDialog::OnOK();
}


void CDlgMotionDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Close();

	CDialog::OnCancel();
}


void CDlgMotionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == TIM_DISP_ENC)
	{
		KillTimer(TIM_DISP_ENC);

		DispEnc();
		DispStatus();
		DispLimitSens();
		DispIoIn();
		DispIoOut();

		CheckBtnStatus();

		if (m_bTIM_DISP_ENC)
			SetTimer(TIM_DISP_ENC, 100, NULL);
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgMotionDlg::DispEnc()
{
	if (!m_pEtherCat)
		return;

	CWnd* pWndCmd = NULL;
	CWnd* pWndAct = NULL;
	CString strCmd, strAct;

	for (int i = 0; i < m_pEtherCat->m_ParamCtrl.nTotAxis; i++)
	{
		switch (i)
		{
		case 0:
			pWndCmd = GetDlgItem(IDC_STATIC_COMMAND_AXIS0);
			pWndAct = GetDlgItem(IDC_STATIC_ACTUAL_AXIS0);
			break;
		case 1:
			pWndCmd = GetDlgItem(IDC_STATIC_COMMAND_AXIS1);
			pWndCmd = GetDlgItem(IDC_STATIC_ACTUAL_AXIS1);
			break;
		case 2:
			pWndCmd = GetDlgItem(IDC_STATIC_COMMAND_AXIS2);
			pWndCmd = GetDlgItem(IDC_STATIC_ACTUAL_AXIS2);
			break;
		case 3:
			pWndCmd = GetDlgItem(IDC_STATIC_COMMAND_AXIS3);
			pWndCmd = GetDlgItem(IDC_STATIC_ACTUAL_AXIS3);
			break;
		}

		strCmd.Format(_T("%.3f"), m_dEncCmd[i]);
		strAct.Format(_T("%.3f"), m_dEncAct[i]);
		pWndCmd->SetWindowText(strCmd);
		pWndAct->SetWindowText(strAct);
	}
}

void CDlgMotionDlg::DispLimitSens()
{
	if (!m_pEtherCat)
		return;

	CButton* pCtlChkBtnLimitNeg[4] = { 0 };
	CButton* pCtlChkBtnLimitHome[4] = { 0 };
	CButton* pCtlChkBtnLimitPos[4] = { 0 };

	pCtlChkBtnLimitNeg[0] = (CButton*)GetDlgItem(IDC_CHECK9);
	pCtlChkBtnLimitNeg[1] = (CButton*)GetDlgItem(IDC_CHECK10);
	pCtlChkBtnLimitNeg[2] = (CButton*)GetDlgItem(IDC_CHECK11);
	pCtlChkBtnLimitNeg[3] = (CButton*)GetDlgItem(IDC_CHECK12);

	pCtlChkBtnLimitHome[0] = (CButton*)GetDlgItem(IDC_CHECK13);
	pCtlChkBtnLimitHome[1] = (CButton*)GetDlgItem(IDC_CHECK14);
	pCtlChkBtnLimitHome[2] = (CButton*)GetDlgItem(IDC_CHECK15);
	pCtlChkBtnLimitHome[3] = (CButton*)GetDlgItem(IDC_CHECK16);

	pCtlChkBtnLimitPos[0] = (CButton*)GetDlgItem(IDC_CHECK17);
	pCtlChkBtnLimitPos[1] = (CButton*)GetDlgItem(IDC_CHECK18);
	pCtlChkBtnLimitPos[2] = (CButton*)GetDlgItem(IDC_CHECK19);
	pCtlChkBtnLimitPos[3] = (CButton*)GetDlgItem(IDC_CHECK20);

	for (int i = 0; i < m_pEtherCat->m_ParamCtrl.nTotAxis; i++)
	{
	}
}

void CDlgMotionDlg::DispStatus()
{
	if (!m_pEtherCat)
		return;

	CWnd* pWnd = NULL;
	CString str;
	for (int i = 0; i < m_pEtherCat->m_ParamCtrl.nTotAxis; i++)
	{
		switch (m_nStatus[i])
		{
		case MPIStateINVALID:
			str = "Invalid";
			break;
		case MPIStateIDLE:
			str = "Idle";
			break;
		case MPIStateMOVING:
			str = "Moving";
			break;
		case MPIStateSTOPPING:
			str = "Stopping";
			break;
		case MPIStateSTOPPED:
			str = "Stopped";
			break;
		case MPIStateSTOPPING_ERROR:
			str = "StoppingError";
			break;
		case MPIStateERROR:
			str = "Error";
			break;
		case MPIStateEND:
			str = "End";
			break;
		default:
			str = "Unknown";
			break;
		}

		switch (i)
		{
		case 0:
			pWnd = GetDlgItem(IDC_STATIC_STATUS_AXIS0); 
			break;
		case 1:
			pWnd = GetDlgItem(IDC_STATIC_STATUS_AXIS1);
			break;
		case 2:
			pWnd = GetDlgItem(IDC_STATIC_STATUS_AXIS2);
			break;
		case 3:
			pWnd = GetDlgItem(IDC_STATIC_STATUS_AXIS3);
			break;
		}

		pWnd->SetWindowText(str);
	}
}

void CDlgMotionDlg::DispMotorType()
{
	if (!m_pEtherCat)
		return;

	CButton* pCtlChkBtn = NULL;

	for (int i = 0; i < m_pEtherCat->m_ParamCtrl.nTotAxis; i++)
	{
		switch (i)
		{
		case 0:
			pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK5);
			break;
		case 1:
			pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK6);
			break;
		case 2:
			pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK7);
			break;
		case 3:
			pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK8);
			break;
		}

		BOOL bChk = m_pEtherCat->m_pParamMotor[i].bType;

		pCtlChkBtn->SetCheck(bChk);
		if (bChk)
			pCtlChkBtn->SetWindowText(_T("Stepper"));
		else
			pCtlChkBtn->SetWindowText(_T("Servo"));
		pCtlChkBtn->EnableWindow(FALSE);
	}
}

void CDlgMotionDlg::DispMoveConf()
{
	CWnd* pWnd[16] = { 0 };

	// P2P Speed
	pWnd[0] = GetDlgItem(IDC_EDIT1);
	pWnd[1] = GetDlgItem(IDC_EDIT2);
	pWnd[2] = GetDlgItem(IDC_EDIT3);
	pWnd[3] = GetDlgItem(IDC_EDIT4);

	// Jog Speed
	pWnd[4] = GetDlgItem(IDC_EDIT13);
	pWnd[5] = GetDlgItem(IDC_EDIT14);
	pWnd[6] = GetDlgItem(IDC_EDIT15);
	pWnd[7] = GetDlgItem(IDC_EDIT16);

	// Acceleration
	pWnd[8] = GetDlgItem(IDC_EDIT5);
	pWnd[9] = GetDlgItem(IDC_EDIT6);
	pWnd[10] = GetDlgItem(IDC_EDIT7);
	pWnd[11] = GetDlgItem(IDC_EDIT8);

	// Deceleration
	pWnd[12] = GetDlgItem(IDC_EDIT9);
	pWnd[13] = GetDlgItem(IDC_EDIT10);
	pWnd[14] = GetDlgItem(IDC_EDIT11);
	pWnd[15] = GetDlgItem(IDC_EDIT12);

	CString sVal;
	for (int nID = 0; nID < m_pEtherCat->m_ParamCtrl.nTotMotion; nID++)
	{
		// P2P Speed
		sVal.Format(_T("%.3f"), m_pEtherCat->m_pParamMotion[nID].Speed.fSpd);
		pWnd[nID]->SetWindowText(sVal);

		// Jog Speed
		sVal.Format(_T("%.3f"), m_pEtherCat->m_pParamMotion[nID].Speed.fJogMidSpd);
		pWnd[nID + 4]->SetWindowText(sVal);

		// Acceleration
		sVal.Format(_T("%.3f"), m_pEtherCat->m_pParamMotion[nID].Speed.fAcc);
		pWnd[nID + 8]->SetWindowText(sVal);

		// Deceleration
		sVal.Format(_T("%.3f"), m_pEtherCat->m_pParamMotion[nID].Speed.fDec);
		pWnd[nID + 12]->SetWindowText(sVal);
	}
}

void CDlgMotionDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 0)
	{
		BOOL bChk = pCtlChkBtn->GetCheck();
		m_pEtherCat->ServoOnOff(0, bChk);
		if (bChk)
			pCtlChkBtn->SetWindowText(_T("ON"));
		else
			pCtlChkBtn->SetWindowText(_T("OFF"));
	}
}


void CDlgMotionDlg::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK2);
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 1)
	{
		BOOL bChk = pCtlChkBtn->GetCheck();
		m_pEtherCat->ServoOnOff(1, bChk);
		if (bChk)
			pCtlChkBtn->SetWindowText(_T("ON"));
		else
			pCtlChkBtn->SetWindowText(_T("OFF"));
	}
}


void CDlgMotionDlg::OnBnClickedCheck3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK3);
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 2)
	{
		BOOL bChk = pCtlChkBtn->GetCheck();
		m_pEtherCat->ServoOnOff(2, bChk);
		if (bChk)
			pCtlChkBtn->SetWindowText(_T("ON"));
		else
			pCtlChkBtn->SetWindowText(_T("OFF"));
	}
}


void CDlgMotionDlg::OnBnClickedCheck4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK4);
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 3)
	{
		BOOL bChk = pCtlChkBtn->GetCheck();
		m_pEtherCat->ServoOnOff(3, bChk);
		if (bChk)
			pCtlChkBtn->SetWindowText(_T("ON"));
		else
			pCtlChkBtn->SetWindowText(_T("OFF"));
	}
}

void CDlgMotionDlg::InitCombo()
{
	if (!m_pEtherCat)
		return;

	int nID = 0;

	CComboBox* pCtlComboMaster = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CComboBox* pCtlComboSlaver = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK21);

	pCtlComboMaster->ResetContent();
	pCtlComboSlaver->ResetContent();

	for (nID = 0; nID < MAX_AXIS; nID++)
	{
		pCtlComboMaster->InsertString(nID, m_pEtherCat->m_pParamAxis[nID].sName);
	}

	pCtlComboSlaver->EnableWindow(FALSE);
	pCtlChkBtn->EnableWindow(FALSE);
}

void CDlgMotionDlg::OnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nID = 0;

	CComboBox* pCtlComboMaster = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CComboBox* pCtlComboSlaver = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK21);

	int nIndex = m_nCurSelMaster = pCtlComboMaster->GetCurSel();

	if (nIndex == LB_ERR)
		return;

	if(!pCtlComboSlaver->IsWindowEnabled())
		pCtlComboSlaver->EnableWindow(TRUE);

	int nCount = pCtlComboSlaver->GetCount();
	if(nCount > 0)
		pCtlComboSlaver->ResetContent();

	for (nID = 0; nID < MAX_AXIS; nID++)
	{
		if (nID != nIndex)
		{
			if (m_pEtherCat)
				pCtlComboSlaver->InsertString(nID, m_pEtherCat->m_pParamAxis[nID].sName);
		}
	}

	pCtlComboSlaver->SetWindowText(_T(""));
	m_nCurSelSlaver = -1;
	pCtlChkBtn->EnableWindow(FALSE);
}


void CDlgMotionDlg::OnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nID = 0;
	CString sSelName = _T("");

	CComboBox* pCtlComboSlaver = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK21);

	int nIndex = pCtlComboSlaver->GetCurSel();
	pCtlComboSlaver->GetLBText(nIndex, sSelName);

	for (nID = 0; nID < MAX_AXIS; nID++)
	{
		if (GetMotorName(nID) == sSelName)
		{
			m_nCurSelSlaver = nID;
			pCtlChkBtn->EnableWindow(TRUE);
			break;
		}
	}
}


void CDlgMotionDlg::OnBnClickedCheck21()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	if (m_nCurSelMaster < 0 || m_nCurSelSlaver < 0)
	{
		if (m_nCurSelMaster < 0 && m_nCurSelSlaver > -1)
			AfxMessageBox(_T("Select Master in ComboBox."));
		else if (m_nCurSelMaster > -1 && m_nCurSelSlaver < 0)
			AfxMessageBox(_T("Select Slaver in ComboBox."));
		else
			AfxMessageBox(_T("Select Master && Slaver in ComboBox."));
		return;
	}

	long lOnOff;
	CString strMsg;

	BOOL bServoOn[2] = { 0 };
	bServoOn[0] = m_pEtherCat->IsServoOn(m_nCurSelMaster);
	bServoOn[1] = m_pEtherCat->IsServoOn(m_nCurSelSlaver);

	CButton* pCtlChkBtn = (CButton*)GetDlgItem(IDC_CHECK21);

	BOOL bOn = pCtlChkBtn->GetCheck();
	if (bOn)
	{
		if (bServoOn[0] && bServoOn[1])
		{
			if (!m_pEtherCat->GetGantry(m_nCurSelMaster, m_nCurSelSlaver, &lOnOff))
			{
				pCtlChkBtn->SetCheck(FALSE);
				strMsg.Format(_T("Failed Gantry Get. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
				AfxMessageBox(strMsg);
				return;
			}

			if (!lOnOff)
			{
				if (!m_pEtherCat->SetGantry(m_nCurSelMaster, m_nCurSelSlaver, TRUE))
				{
					pCtlChkBtn->SetCheck(FALSE);
					strMsg.Format(_T("Failed Gantry Set. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
					AfxMessageBox(strMsg);
					return;
				}
			}

			if (!m_pEtherCat->GetGantry(m_nCurSelMaster, m_nCurSelSlaver, &lOnOff))
			{
				pCtlChkBtn->SetCheck(FALSE);
				strMsg.Format(_T("Failed Gantry Get. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
				AfxMessageBox(strMsg);
				return;
			}

			if (!lOnOff)
			{
				pCtlChkBtn->SetCheck(FALSE);
				strMsg.Format(_T("Failed Gantry Set. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
				AfxMessageBox(strMsg);
				return;
			}

			strMsg.Format(_T("Succeed Gantry Set. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
			AfxMessageBox(strMsg);
			return;
		}
		else
		{
			pCtlChkBtn->SetCheck(FALSE);

			if (!bServoOn[0] && bServoOn[1])
				AfxMessageBox(_T("Master servo is disabled."));
			else if (bServoOn[0] && !bServoOn[1])
				AfxMessageBox(_T("Slaver servo is disabled."));
			else
				AfxMessageBox(_T("Master && Slaver servos are disabled."));
			return;
		}
	}
	else
	{
		if (!m_pEtherCat->GetGantry(m_nCurSelMaster, m_nCurSelSlaver, &lOnOff))
		{
			pCtlChkBtn->SetCheck(TRUE);
			strMsg.Format(_T("Failed Gantry Get. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
			AfxMessageBox(strMsg);
			return;
		}

		if (lOnOff)
		{
			if (!m_pEtherCat->SetGantry(m_nCurSelMaster, m_nCurSelSlaver, FALSE))
			{
				pCtlChkBtn->SetCheck(TRUE);
				strMsg.Format(_T("Failed Gantry Reset. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
				AfxMessageBox(strMsg);
				return;
			}

			strMsg.Format(_T("Succeed Gantry Reset. - %s axis(master) and %s axis(slaver)."), GetMotorName(m_nCurSelMaster), GetMotorName(m_nCurSelSlaver));
			AfxMessageBox(strMsg);
			return;
		}
		else
		{
			strMsg.Format(_T("Gantry was already disabled."));
			AfxMessageBox(strMsg);
			return;
		}
	}
}

CString CDlgMotionDlg::GetMotorName(int nID)
{
	if (!m_pEtherCat)
		return _T("");

	return m_pEtherCat->m_pParamAxis[nID].sName;
}

void CDlgMotionDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->Clear(0);
}


void CDlgMotionDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->Clear(1);
}


void CDlgMotionDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->Clear(2);
}


void CDlgMotionDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->Clear(3);
}


void CDlgMotionDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->SetPosition(0, 0.0);
}


void CDlgMotionDlg::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->SetPosition(1, 0.0);
}


void CDlgMotionDlg::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->SetPosition(2, 0.0);
}


void CDlgMotionDlg::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	m_pEtherCat->SetPosition(3, 0.0);
}


void CDlgMotionDlg::OnBnClickedButton9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos1
	CWnd* pWndPos1 = GetDlgItem(IDC_EDIT17);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT1);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT5);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT9);

	Move(0, pWndPos1, pWndSpd, pWndAcc, pWndDec);
}


void CDlgMotionDlg::OnBnClickedButton10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos1
	CWnd* pWndPos1 = GetDlgItem(IDC_EDIT18);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT2);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT6);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT10);

	Move(1, pWndPos1, pWndSpd, pWndAcc, pWndDec);
}


void CDlgMotionDlg::OnBnClickedButton11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos1
	CWnd* pWndPos1 = GetDlgItem(IDC_EDIT19);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT3);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT7);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT11);

	Move(2, pWndPos1, pWndSpd, pWndAcc, pWndDec);
}


void CDlgMotionDlg::OnBnClickedButton12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos1
	CWnd* pWndPos1 = GetDlgItem(IDC_EDIT20);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT4);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT8);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT12);

	Move(3, pWndPos1, pWndSpd, pWndAcc, pWndDec);
}


void CDlgMotionDlg::OnBnClickedButton13()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos2
	CWnd* pWndPos2 = GetDlgItem(IDC_EDIT21);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT1);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT5);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT9);

	Move(0, pWndPos2, pWndSpd, pWndAcc, pWndDec);
}


void CDlgMotionDlg::OnBnClickedButton14()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos2
	CWnd* pWndPos2 = GetDlgItem(IDC_EDIT22);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT2);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT6);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT10);

	Move(1, pWndPos2, pWndSpd, pWndAcc, pWndDec);
}


void CDlgMotionDlg::OnBnClickedButton15()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos2
	CWnd* pWndPos2 = GetDlgItem(IDC_EDIT23);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT3);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT7);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT11);

	Move(2, pWndPos2, pWndSpd, pWndAcc, pWndDec);
}


void CDlgMotionDlg::OnBnClickedButton16()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Move Pos2
	CWnd* pWndPos2 = GetDlgItem(IDC_EDIT24);
	CWnd* pWndSpd = GetDlgItem(IDC_EDIT4);
	CWnd* pWndAcc = GetDlgItem(IDC_EDIT8);
	CWnd* pWndDec = GetDlgItem(IDC_EDIT12);

	Move(3, pWndPos2, pWndSpd, pWndAcc, pWndDec);
}

BOOL CDlgMotionDlg::Move(int nID, CWnd* pWndTgtPos, CWnd* pWndSpd, CWnd* pWndAcc, CWnd* pWndDec)
{
	if (!m_pEtherCat)
	{
		AfxMessageBox(_T("m_pEtherCat is NULL."));
		return FALSE;
	}

	CString sPos, sSpd, sAcc, sDec, sMsg;

	pWndTgtPos->GetWindowText(sPos);
	pWndSpd->GetWindowText(sSpd);
	pWndAcc->GetWindowText(sAcc);
	pWndDec->GetWindowText(sDec);

	if (sPos.IsEmpty() || sSpd.IsEmpty() || sAcc.IsEmpty() || sDec.IsEmpty())
	{
		AfxMessageBox(_T("Move Parmeter is empty."));
		return FALSE;
	}

	double dTgtPos = _tstof(sPos);
	double dSpd = _tstof(sSpd);
	double dAcc = _tstof(sAcc);
	double dDec = _tstof(sDec);

	if (!m_pEtherCat->Move(nID, dTgtPos, dSpd, dAcc, dDec))
	{
		sMsg.Format(_T("Error Move. - %s ."), GetMotorName(nID));
		AfxMessageBox(sMsg);
		return FALSE;
	}

	return TRUE;
}

LRESULT CDlgMotionDlg::OnMyBtnDown(WPARAM wPara, LPARAM lPara)
{
	int nCtrlID = (int)lPara;
	SwMyBtnDown(nCtrlID);

	return 0L;
}

LRESULT CDlgMotionDlg::OnMyBtnUp(WPARAM wPara, LPARAM lPara)
{
	int nCtrlID = (int)lPara;
	SwMyBtnUp(nCtrlID);
	return 0L;
}

void CDlgMotionDlg::SwMyBtnDown(int nCtrlID)
{
	if (!m_pEtherCat)
		return;

	switch (nCtrlID)
	{
	case IDC_BUTTON17: // Jog -
		m_pEtherCat->VMove(0, M_CCW);
		break;
	case IDC_BUTTON18: // Jog +
		m_pEtherCat->VMove(0, M_CW);
		break;
	case IDC_BUTTON19: // Jog -
		m_pEtherCat->VMove(1, M_CCW);
		break;
	case IDC_BUTTON20: // Jog +
		m_pEtherCat->VMove(1, M_CW);
		break;
	case IDC_BUTTON21: // Jog -
		m_pEtherCat->VMove(2, M_CCW);
		break;
	case IDC_BUTTON22: // Jog +
		m_pEtherCat->VMove(2, M_CW);
		break;
	case IDC_BUTTON23: // Jog -
		m_pEtherCat->VMove(3, M_CCW);
		break;
	case IDC_BUTTON24: // Jog +
		m_pEtherCat->VMove(3, M_CW);
		break;
	}
}

void CDlgMotionDlg::SwMyBtnUp(int nCtrlID)
{
	if (!m_pEtherCat)
		return;

	switch (nCtrlID)
	{
	case IDC_BUTTON17: // Jog -
		m_pEtherCat->EStop(0);
		ResetMotion(0);
		break;
	case IDC_BUTTON18: // Jog +
		m_pEtherCat->EStop(0);
		ResetMotion(0);
		break;
	case IDC_BUTTON19: // Jog -
		m_pEtherCat->EStop(1);
		ResetMotion(1);
		break;
	case IDC_BUTTON20: // Jog +
		m_pEtherCat->EStop(1);
		ResetMotion(1);
		break;
	case IDC_BUTTON21: // Jog -
		m_pEtherCat->EStop(2);
		ResetMotion(2);
		break;
	case IDC_BUTTON22: // Jog +
		m_pEtherCat->EStop(2);
		ResetMotion(2);
		break;
	case IDC_BUTTON23: // Jog -
		m_pEtherCat->EStop(3);
		ResetMotion(3);
		break;
	case IDC_BUTTON24: // Jog +
		m_pEtherCat->EStop(3);
		ResetMotion(3);
		break;
	}
}

void CDlgMotionDlg::ResetMotion(int nMsId)
{
	if (!m_pEtherCat)
		return;

	long lRtn = m_pEtherCat->GetState(nMsId);  // -1 : MPIStateERROR, 0 : MPIStateIDLE, 1 : MPIStateSTOPPING, 2 : MPIStateMOVING
	if (lRtn == 2)
	{
		m_pEtherCat->Abort(nMsId);
		Sleep(30);
	}

	m_pEtherCat->Clear(nMsId);
	Sleep(30);

	if (!m_pEtherCat->IsEnable(nMsId))
	{
		m_pEtherCat->ServoOnOff(nMsId, TRUE);
		Sleep(30);
	}
}

void CDlgMotionDlg::CheckBtnStatus()
{
	if (!m_pEtherCat)
		return;

	CButton* pBtnHome[4] = { 0 };
	pBtnHome[0] = (CButton*)GetDlgItem(IDC_BUTTON25);
	pBtnHome[1] = (CButton*)GetDlgItem(IDC_BUTTON26);
	pBtnHome[2] = (CButton*)GetDlgItem(IDC_BUTTON27);
	pBtnHome[3] = (CButton*)GetDlgItem(IDC_BUTTON28);

	for (int nID = 0; nID < MAX_AXIS; nID++)
	{
		if (m_pEtherCat->IsHomeDone(nID))
		{
			pBtnHome[nID]->EnableWindow(TRUE);
		}
		else
		{
			pBtnHome[nID]->EnableWindow(FALSE);
		}
	}
}

void CDlgMotionDlg::OnBnClickedButton25()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CString sMsg;

	// Homming
	if(m_pEtherCat->IsHomeDone(0))
		m_pEtherCat->SearchHomePos(0);
	else
	{
		sMsg.Format(_T("%s is homming now."), GetMotorName(0));
		AfxMessageBox(sMsg);
	}
}


void CDlgMotionDlg::OnBnClickedButton26()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CString sMsg;

	// Homming
	if (m_pEtherCat->IsHomeDone(1))
		m_pEtherCat->SearchHomePos(1);
	else
	{
		sMsg.Format(_T("%s is homming now."), GetMotorName(1));
		AfxMessageBox(sMsg);
	}
}


void CDlgMotionDlg::OnBnClickedButton27()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CString sMsg;

	// Homming
	if (m_pEtherCat->IsHomeDone(2))
		m_pEtherCat->SearchHomePos(2);
	else
	{
		sMsg.Format(_T("%s is homming now."), GetMotorName(2));
		AfxMessageBox(sMsg);
	}
}


void CDlgMotionDlg::OnBnClickedButton28()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CString sMsg;

	// Homming
	if (m_pEtherCat->IsHomeDone(3))
		m_pEtherCat->SearchHomePos(3);
	else
	{
		sMsg.Format(_T("%s is homming now."), GetMotorName(3));
		AfxMessageBox(sMsg);
	}
}


void CDlgMotionDlg::DispIoIn()
{
	if (!m_pEtherCat)
		return;

	CString sDisp[4], sTemp;

	sDisp[0] = _T("");
	sDisp[1] = _T("");
	sDisp[2] = _T("");
	sDisp[3] = _T("");

	for (int i = 31; i <= 0; i--)
	{
		sTemp.Format(_T("%d"), (m_ulDispIn & (0x00000001 << i)) ? 1 : 0);

		if (i >= 24)
			sDisp[3] += sTemp;
		else if(i >= 16)
			sDisp[2] += sTemp;
		else if (i >= 8)
			sDisp[1] += sTemp;
		else
			sDisp[0] += sTemp;
	}

	GetDlgItem(IDC_STATIC_DISP_IO_IN_3)->SetWindowText(sDisp[3]);
	GetDlgItem(IDC_STATIC_DISP_IO_IN_2)->SetWindowText(sDisp[2]);
	GetDlgItem(IDC_STATIC_DISP_IO_IN_1)->SetWindowText(sDisp[1]);
	GetDlgItem(IDC_STATIC_DISP_IO_IN_0)->SetWindowText(sDisp[0]);
}

void CDlgMotionDlg::DispIoOut()
{
	if (!m_pEtherCat)
		return;

	CString sDisp[4], sTemp;

	sDisp[0] = _T("");
	sDisp[1] = _T("");
	sDisp[2] = _T("");
	sDisp[3] = _T("");

	for (int i = 31; i <= 0; i--)
	{
		sTemp.Format(_T("%d"), (m_ulDispOut & (0x00000001 << i)) ? 1 : 0);

		if (i >= 24)
			sDisp[3] += sTemp;
		else if (i >= 16)
			sDisp[2] += sTemp;
		else if (i >= 8)
			sDisp[1] += sTemp;
		else
			sDisp[0] += sTemp;
	}

	GetDlgItem(IDC_STATIC_DISP_IO_OUT_3)->SetWindowText(sDisp[3]);
	GetDlgItem(IDC_STATIC_DISP_IO_OUT_2)->SetWindowText(sDisp[2]);
	GetDlgItem(IDC_STATIC_DISP_IO_OUT_1)->SetWindowText(sDisp[1]);
	GetDlgItem(IDC_STATIC_DISP_IO_OUT_0)->SetWindowText(sDisp[0]);
}

void CDlgMotionDlg::SetIoOut()
{
	if (!m_pEtherCat)
		return;

	CString sDisp[4], sTemp;

	sDisp[0] = _T("");
	sDisp[1] = _T("");
	sDisp[2] = _T("");
	sDisp[3] = _T("");

	m_ulDispOut = m_pEtherCat->ReadAllBit(FALSE);
	m_ulOut = m_ulDispOut;

	for (int i = 31; i <= 0; i--)
	{
		sTemp.Format(_T("%d"), (m_ulDispOut & (0x00000001 << i)) ? 1 : 0);

		if (i >= 24)
			sDisp[3] += sTemp;
		else if (i >= 16)
			sDisp[2] += sTemp;
		else if (i >= 8)
			sDisp[1] += sTemp;
		else
			sDisp[0] += sTemp;
	}

	GetDlgItem(IDC_EDIT_IO_OUT_3)->SetWindowText(sDisp[3]);
	GetDlgItem(IDC_EDIT_IO_OUT_2)->SetWindowText(sDisp[2]);
	GetDlgItem(IDC_EDIT_IO_OUT_1)->SetWindowText(sDisp[1]);
	GetDlgItem(IDC_EDIT_IO_OUT_0)->SetWindowText(sDisp[0]);
}

void CDlgMotionDlg::OnBnClickedButton29()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pEtherCat)
		return;

	CString sDisp[4], sTemp[2];

	GetDlgItem(IDC_EDIT_IO_OUT_3)->GetWindowText(sDisp[3]);
	GetDlgItem(IDC_EDIT_IO_OUT_2)->GetWindowText(sDisp[2]);
	GetDlgItem(IDC_EDIT_IO_OUT_1)->GetWindowText(sDisp[1]);
	GetDlgItem(IDC_EDIT_IO_OUT_0)->GetWindowText(sDisp[0]);

	if (sDisp[3].GetLength() < 8 || sDisp[2].GetLength() < 8 ||
		sDisp[1].GetLength() < 8 || sDisp[0].GetLength() < 8)
	{
		AfxMessageBox(_T("Error - Output Data Length."));
		return;
	}

	m_ulOut = 0;

	for (int i = 31; i <= 0; i--)
	{
		if (i >= 24)
		{
			sTemp[0] = sDisp[3].Left(32 - i);
			sTemp[1] = sTemp[0].Right(1);
			m_ulOut += (2 ^ i) * _tstoi(sTemp[1]);
		}
		else if (i >= 16)
		{
			sTemp[0] = sDisp[2].Left(24 - i);
			sTemp[1] = sTemp[0].Right(1);
			m_ulOut += (2 ^ i) * _tstoi(sTemp[1]);
		}
		else if (i >= 8)
		{
			sTemp[0] = sDisp[1].Left(16 - i);
			sTemp[1] = sTemp[0].Right(1);
			m_ulOut += (2 ^ i) * _tstoi(sTemp[1]);
		}
		else
		{
			sTemp[0] = sDisp[0].Left(8 - i);
			sTemp[1] = sTemp[0].Right(1);
			m_ulOut += (2 ^ i) * _tstoi(sTemp[1]);
		}
	}

	m_pEtherCat->WriteData(m_ulOut);
}

