
// DlgMotion.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

#define WM_MYBTN_DOWN					(WM_USER + 1)
#define WM_MYBTN_UP						(WM_USER + 2)
#define WM_MYBTN_DBLCLK					(WM_USER + 3)

typedef enum { BTN_UP = 1, BTN_DN = 2 } BTN_ACT;

#define RGB_BLACK       RGB(0,0,0)
#define RGB_WHITE       RGB(255,255,255)       
#define RGB_GRAY        RGB(0x80, 0x80, 0x80)
#define RGB_RED         RGB(255,0,0)
#define RGB_YELLOW      RGB(255,255,0)
#define RGB_DARKYELLOW  RGB(128,128,0)
#define RGB_GREEN       RGB(0,255,0)
#define RGB_LTGREEN     RGB(0,255,128)
#define RGB_DARKGREEN   RGB(64,128,128)
#define RGB_CYAN        RGB(0,255,255)
#define RGB_BLUE        RGB(0,0,255)
#define RGB_LTBLUE		RGB(82, 200, 200)
#define RGB_CLOUDBLUE	RGB(128,184,223)
#define RGB_MAGENTA     RGB(255,0,255)
#define RGB_LTMAGENTA   RGB(255,64,255)
#define RGB_DARKMAGENTA RGB(193,0,130)
#define RGB_LTGRAY      RGB(192,192,192)
#define RGB_DARKGRAY    RGB(128,128,128)
#define RGB_DARKCYAN    RGB(0,128,128)
#define RGB_LTCYAN      RGB(128,255,255)
#define RGB_BOON        RGB(255,0,128)
#define RGB_DARKBOON    RGB(64,0,128)
#define RGB_DARKBLUE    RGB(0,0,128)
#define RGB_PINK        RGB(255,0,128)
#define RGB_LTPINK      RGB(255,64,128)
#define RGB_SKYBLUE		RGB(128,255,255)
#define RGB_PURPLE		RGB(128,0,255)
#define RGB_LTPURPLE	RGB(226,233,251)
#define RGB_LTPURPLE2   RGB(255,128,255)
#define RGB_YELLOWGREEN RGB(128,255,0)
#define RGB_LTYELLOW    RGB(255,255,128)
#define RGB_BROWN       RGB(255,128,0)
#define RGB_CHESTNUT	RGB(128,64,64)
#define RGB_NAVY		RGB(0,0,128)
#define RGB_LLTGREEN    RGB(128,255,128)
#define RGB_LTRED       RGB(255,128,64)
#define RGB_DARKFINGER	RGB(128,0,128)
#define RGB_LAVENDER	RGB(0xe6,0xe6,0xfa)
#define RGB_PLURM		RGB(0xdd,0xa0,0xdd)

#define MRGB_BLACK       M_RGB888(0,0,0)
#define MRGB_WHITE       M_RGB888(255,255,255)
#define MRGB_GRAY        M_RGB888(0x80, 0x80, 0x80)
#define MRGB_RED         M_RGB888(255,0,0)
#define MRGB_YELLOW      M_RGB888(255,255,0)
#define MRGB_DARKYELLOW  M_RGB888(128,128,0)
#define MRGB_GREEN       M_RGB888(0,255,0)
#define MRGB_LTGREEN     M_RGB888(0,255,128)
#define MRGB_DARKGREEN   M_RGB888(0,64,64)
#define MRGB_CYAN        M_RGB888(0,255,255)
#define MRGB_BLUE        M_RGB888(0,0,255)
#define MRGB_MAGENTA     M_RGB888(255,0,255)
#define MRGB_DARKMAGENTA M_RGB888(193,0,130)
#define MRGB_LTGRAY      M_RGB888(192,192,192)
#define MRGB_DARKGRAY    M_RGB888(128,128,128)
#define MRGB_DARKCYAN    M_RGB888(0,128,128)
#define MRGB_LTCYAN      M_RGB888(128,255,255)
#define MRGB_BOON        M_RGB888(255,0,128)
#define MRGB_DARKBOON    M_RGB888(64,0,128)
#define MRGB_DARKBLUE    M_RGB888(0,0,128)
#define MRGB_DARKFINGER	 M_RGB888(128,0,128)

#define RGB_BLACK       RGB(0,0,0)
#define RGB_WHITE       RGB(255,255,255)
#define RGB_GRAY        RGB(0x80, 0x80, 0x80)
#define RGB_RED         RGB(255,0,0)
#define RGB_DARKRED     RGB(207,0,0)
#define RGB_YELLOW      RGB(255,255,0)
#define RGB_DARKYELLOW  RGB(128,128,0)
#define RGB_GREEN       RGB(0,255,0)
#define RGB_LTGREEN     RGB(0,255,128)
#define RGB_CYAN        RGB(0,255,255)
#define RGB_BLUE        RGB(0,0,255)
#define RGB_LTBLUE		RGB(82, 200, 200)
#define RGB_CLOUDBLUE	RGB(128,184,223)
#define RGB_MAGENTA     RGB(255,0,255)
#define RGB_DARKMAGENTA RGB(193,0,130)
#define RGB_WHGRAY      RGB(218,218,218)
#define RGB_LTGRAY      RGB(192,192,192)
#define RGB_DARKCYAN    RGB(0,128,128)
#define RGB_LTCYAN      RGB(128,255,255)
#define RGB_BOON        RGB(255,0,128)
#define RGB_DARKBOON    RGB(64,0,128)
#define RGB_DARKBLUE    RGB(0,0,128)
#define RGB_PINK        RGB(255,0,128)
#define RGB_DARKPINK	RGB(227,64,128)
#define RGB_SKYBLUE		RGB(128,255,255)
#define RGB_DKSKYBLUE	RGB(82,200,200)
#define RGB_PURPLE		RGB(128,0,255)
#define RGB_YELLOWGREEN RGB(128,255,0)
#define RGB_WHYELLOW    RGB(255,255,128)
#define RGB_ORANGE      RGB(255,128,0)
#define RGB_LTDKORANGE  RGB(255,172,89)
#define RGB_DARKORANGE  RGB(220,70,0)
#define RGB_CHESTNUT	RGB(128,64,64)
#define RGB_NAVY		RGB(0,0,128)
#define RGB_LLTGREEN    RGB(128,255,128)
#define RGB_LT_ORANGE   RGB(255,128,64)
#define RGB_DARKFINGER	RGB(128,0,128)
#define RGB_DLG_FRM		RGB(212,208,200)
#define RGB_DLG_FRM2	RGB(240,240,240)
#define RGB_DARKBROWN	RGB(64,0,0)
#define RGB_DIALOG		RGB(200,200,192)
#define RGB_POSTIT		RGB(240,233,134)
#define RGB_DARK_BLUE	RGB(68,136,204)
#define RGB_FRAME		RGB(212,208,200)

#define RGB_DARK_GREEN	RGB(0,125,60)
#define RGB_LT_PURPLE	RGB(179,179,255)
#define RGB_LT_YELLOW	RGB(255,255,150)
#define RGB_LT_PINK		RGB(255,200,200)
#define RGB_LT_GREEN	RGB(195,255,195)
#define RGB_LT_BLUE		RGB(210,255,255)
#define RGB_WH_ORANGE	RGB(255,220,190)

// CDlgMotionApp:
// 이 클래스의 구현에 대해서는 DlgMotion.cpp을 참조하십시오.
//

class CDlgMotionApp : public CWinApp
{
public:
	CDlgMotionApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CDlgMotionApp theApp;