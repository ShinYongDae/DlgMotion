#pragma once

//#define USE_NMC

#include "MotionParam.h"
#include "MyFileErrMap.h"

#ifdef USE_NMC
#include "NmcDevice.h"
#else
#include "NMC.h"
#endif



#define PATH_MOTION_PARAM		_T("MotionParam.ini")
#define MAX_AXIS 4
typedef enum { M_CCW = -1, M_CW = 1 } MOTION_DIR;

class CEtherCat : public CWnd
{
	CWnd* m_pParent;
	UINT16	m_nBoardId;
	UINT16	m_nDevIdIoIn;
	UINT16	m_nDevIdIoOut;
	INT		m_nOffsetAxisID;
	int		m_nGroupID_Interpolation[2];

#ifdef USE_NMC
	CNmcDevice *m_pMotionCard;
#endif

	DWORD m_dwSt, m_dwEd;
	double m_dStMsLsrOffsetX, m_dStMsLsrOffsetY, m_dEdMsLsrOffsetX, m_dEdMsLsrOffsetY;

	void FreeAll();
	void LoadParam();
	BOOL LoadErrMapFile(CString sPath);
	BOOL InitNmcBoard();
	void SetConfigure();
	void SetMotionParam();
	BOOL CreateObject();
	// Construction
public:
	CEtherCat(CWnd* pParent = NULL);
	//CCriticalSection m_csGetActualPosition;
	//CCriticalSection m_csGetActualVelocity;
	//CCriticalSection m_csReadAdc;

	// Attributes
public:
	CString m_sPathMotionParam;
	CMyFileErrMap *m_pMyFileErrMap;
	int m_nTotAxis;
	MotionSingle* m_pParam;

	MotionControl m_ParamCtrl;
	MotionMotion* m_pParamMotion;
	MotionAxis* m_pParamAxis;
	MotionMotor* m_pParamMotor;

	double m_dPinPosX[2], m_dPinPosY[2];
	double m_dAlignPosX[2][2], m_dAlignPosY[2][2]; // [nCam][nPos]
	double m_dStBufPos, m_dScaleFdBuf;

	double m_dBaseFocusZ;
	double m_dPanelThicknessByUser;
	BOOL m_bResetElementID;
	BOOL m_bSetPnlThickness;
	int m_nElementID;
	BOOL m_bMarkOffset;
	double m_dMarkOffsetX, m_dMarkOffsetY;
	BOOL m_bDO[32];
	double m_dFeedRate[4];
	double m_dTotMarkDist, m_dTotJumpDist, m_dTotMarkTime, m_dTotJumpTime;
	unsigned long m_InputFlag;

	BOOL m_bUseSaftyCover, m_bUseVrsSkip;

	// Operations
public:
	double GetMotionTime(double dLen, double dVel, double dAcc, double dJerk);
	double GetSCurveVelocity(double dLen, double &dVel, double &dAcc, double &dJerk, double dMinJerkTime);
	double GetSpeedProfile(int nMode, int nAxisID, double fMovingLength, double &fVel, double &fAcc, double &fJerk, int nSpeedType = HIGH_SPEED);

	BOOL Abort(int nMotionId);
	long GetState(int nMotionId);
	BOOL InitBoard();
	BOOL SearchHome();
	BOOL SearchHomePos(int nMotionId, BOOL bThread = TRUE);
	BOOL IsHome(int nMotionId);
	BOOL IsHomeDone();
	BOOL IsHomeDone(int nMotionId);
	BOOL IsMotionDone(int nMotionId);
	BOOL IsInPosition(int nMotionId);
	BOOL ServoOnOff(int nAxis, BOOL bOn);
	BOOL AmpReset(int nMsId);

	BOOL Move(int nMotionId, double *pTgtPos, BOOL bAbs = ABS, BOOL bWait = NO_WAIT);
	BOOL Move(int nMotionId, double *pTgtPos, double dRatio, BOOL bAbs = ABS, BOOL bWait = NO_WAIT);
	BOOL Move(int nMotionId, double *pTgtPos, double dSpd, double dAcc, double dDec, BOOL bAbs = ABS, BOOL bWait = WAIT);
	BOOL Move(int nMotionId, double dTgtPos, double dSpd, double dAcc, double dDec, BOOL bAbs = ABS, BOOL bWait = WAIT);

	//BOOL MovePath(int nMotionId);
	//BOOL SetErrMap(CMyFileErrMap *pMyFile);
	double GetActualPosition(int nAxisId);
	BOOL Stop(int nMotionId);
	BOOL EStop(int nMotionId);
	BOOL Clear(int nMotionId);
	BOOL SetVMove(int nMotionId, double fVel, double fAcc);
	BOOL VMove(int nMotionId, int nDir = 1);


	BOOL VMoveStop(int nMotionId, int nDir);
	BOOL IsLimit(int nMotionId, int nDir);

	double GetActualVelocity(int nAxisId);

	double GetLeadPitch(int nAxisId);

	BOOL IsEnable(int nMsId);
	BOOL IsServoOn(int nMotorID);

	void WriteData(long lData);
	void WriteBit(BYTE cBit, BOOL bOn);
	BOOL ReadBit(BYTE cBit, BOOL bInput = TRUE);
	unsigned long ReadAllBit(BOOL bInput);
	void MotionAbortAll();
	BOOL MotionAbort(int nMsId);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEtherCat)
	//}}AFX_VIRTUAL

	// Implementation
public:
	~CEtherCat();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEtherCat)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

