
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

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
//  이 함수를 호출합니다.
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

	ThreadInit();

	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
	m_pEtherCat->ServoOnOff(0, FALSE);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(FALSE);
	m_pEtherCat->ServoOnOff(1, FALSE);
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(FALSE);
	m_pEtherCat->ServoOnOff(2, FALSE);
	((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(FALSE);
	m_pEtherCat->ServoOnOff(3, FALSE);

	m_bTIM_DISP_ENC = TRUE;
	SetTimer(TIM_DISP_ENC, 100, NULL);
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

		if (m_bTIM_DISP_ENC)
			SetTimer(TIM_DISP_ENC, 100, NULL);
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgMotionDlg::DispEnc()
{
	CString strCmd, strAct;
	for (int i = 0; i < m_pEtherCat->m_ParamCtrl.nTotAxis; i++)
	{
		strCmd.Format(_T("%.3f"), m_dEncCmd[i]);
		strAct.Format(_T("%.3f"), m_dEncAct[i]);
		switch (i)
		{
		case 0:
			GetDlgItem(IDC_STATIC_COMMAND_AXIS0)->SetWindowText(strCmd);
			GetDlgItem(IDC_STATIC_ACTUAL_AXIS0)->SetWindowText(strAct);
			break;
		case 1:
			GetDlgItem(IDC_STATIC_COMMAND_AXIS1)->SetWindowText(strCmd);
			GetDlgItem(IDC_STATIC_ACTUAL_AXIS1)->SetWindowText(strAct);
			break;
		case 2:
			GetDlgItem(IDC_STATIC_COMMAND_AXIS2)->SetWindowText(strCmd);
			GetDlgItem(IDC_STATIC_ACTUAL_AXIS2)->SetWindowText(strAct);
			break;
		case 3:
			GetDlgItem(IDC_STATIC_COMMAND_AXIS3)->SetWindowText(strCmd);
			GetDlgItem(IDC_STATIC_ACTUAL_AXIS3)->SetWindowText(strAct);
			break;
		}
	}
}

void CDlgMotionDlg::DispStatus()
{
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
			GetDlgItem(IDC_STATIC_STATUS_AXIS0)->SetWindowText(str);
			break;
		case 1:
			GetDlgItem(IDC_STATIC_STATUS_AXIS1)->SetWindowText(str);
			break;
		case 2:
			GetDlgItem(IDC_STATIC_STATUS_AXIS2)->SetWindowText(str);
			break;
		case 3:
			GetDlgItem(IDC_STATIC_STATUS_AXIS3)->SetWindowText(str);
			break;
		}
	}
}

void CDlgMotionDlg::DispMotorType()
{
	CString str;
	for (int i = 0; i < m_pEtherCat->m_ParamCtrl.nTotAxis; i++)
	{
		BOOL bChk = m_pEtherCat->m_pParamMotor[i].bType;
		switch (i)
		{
		case 0:
			((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(bChk);
			((CButton*)GetDlgItem(IDC_CHECK5))->EnableWindow(FALSE);
			break;
		case 1:
			((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(bChk);
			((CButton*)GetDlgItem(IDC_CHECK6))->EnableWindow(FALSE);
			break;
		case 2:
			((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(bChk);
			((CButton*)GetDlgItem(IDC_CHECK7))->EnableWindow(FALSE);
			break;
		case 3:
			((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(bChk);
			((CButton*)GetDlgItem(IDC_CHECK8))->EnableWindow(FALSE);
			break;
		}
	}
}

void CDlgMotionDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 0)
	{
		BOOL bChk = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
		m_pEtherCat->ServoOnOff(0, bChk);
	}
}


void CDlgMotionDlg::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 1)
	{
		BOOL bChk = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
		m_pEtherCat->ServoOnOff(1, bChk);
	}
}


void CDlgMotionDlg::OnBnClickedCheck3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 2)
	{
		BOOL bChk = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();
		m_pEtherCat->ServoOnOff(2, bChk);
	}
}


void CDlgMotionDlg::OnBnClickedCheck4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pEtherCat->m_ParamCtrl.nTotAxis > 3)
	{
		BOOL bChk = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
		m_pEtherCat->ServoOnOff(3, bChk);
	}
}
