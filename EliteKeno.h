// Linker switches: /OUT:".\Debug/EliteKeno.exe" /INCREMENTAL:NO /NOLOGO /DEBUG /PDB:".\Debug/EliteKeno.pdb" /SUBSYSTEM:WINDOWS /MACHINE:X86 winmm.lib dxguid.lib dxerr8.lib ddraw.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
// Compiler switches: /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FD /EHsc /MLd /Fp".\Debug/EliteKeno.pch" /Fo".\Debug/" /Fd".\Debug/" /FR".\Debug/" /W3 /nologo /c /ZI /TP

//----------------------------------------------------------------------------------------------
//
// EliteKeno.h : Global Defines for the Elite Keno Slot Machine Application.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, & Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------
#include "main.h"
#include "ddutil.h"
#include "DecodePosition.h"
#include "DrawingTasks.h"
#include "GameState.h"
//---------------------------------------------------------------------------

#ifndef EliteKenoH
#define EliteKenoH
//---------------------------------------------------------------------------
// EliteKeno.cpp
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define SPRITE_DIAMETER 48
#define NUM_SPRITES     25

struct SPRITE_STRUCT
{
    FLOAT                fPosX; 
    FLOAT                fPosY;
    FLOAT                fVelX; 
    FLOAT                fVelY;
};
 
CDisplay*            g_pDisplay				= NULL;
static CGameState*	 gs						= NULL;
CSurface*            g_pDXLogoSurface		= NULL;
CSurface*            g_pEKLogoSurface		= NULL;
CSurface*			 g_pEKBaseSurface		= NULL;
CSurface*			 g_pEKGameStatSurface   = NULL;
CSurface*			 g_pEKOrLabelSurface	= NULL;
CSurface*			 g_pEKSTBaseSurface		= NULL;  
CSurface*			 g_pEKSTHdr1Surface		= NULL;
CSurface*			 g_pEKSTHdr2Surface		= NULL;
CSurface*			 g_pEKSTHdr3Surface		= NULL;
CSurface*			 g_pEKSTHdr4Surface		= NULL;
CSurface*			 g_pEKSTSpotSurface		= NULL;
CSurface*			 g_pEKBTBaseSurface		= NULL;  
CSurface*			 g_pEKBTHdrSurface		= NULL;  
CSurface*			 g_pEKBTSpotSurface		= NULL;  
CSurface*			 g_pEKMsgCtrSurface		= NULL;  
CSurface*            g_pTextSurface			= NULL;
CSurface*			 g_pEKRMsgSurface		= NULL;
CSurface*			 g_pEKFrame1Surface		= NULL;
CSurface*			 g_pEKFrame2Surface		= NULL;
CSurface*			 g_pEKFrame3Surface		= NULL;
CSurface*			 g_pEKFrame4Surface		= NULL;
CSurface*			 g_pEKFrame5Surface		= NULL;
CSurface*			 g_pEKBetMtrSurface		= NULL;
CSurface*			 g_pEKWonMtrSurface		= NULL;
CSurface*			 g_pEKCreditSurface		= NULL;  
CSurface*			 g_pEKButtonSurface		= NULL;
CSurface*			 g_pEKCashOutSurface	= NULL;
CSurface*			 g_pEKTchOneSurface		= NULL;
CSurface*			 g_pEKChgBetSurface		= NULL;
/* Zebs surfaces */
CSurface*			 g_pEKPayScreenSurface	= NULL;
CSurface*			 g_pEKTktTypeSurface	= NULL;
CSurface*			 g_pEKWayBoxSurface		= NULL;
CSurface*			 g_pEKHelpBGSurface		= NULL;
CSurface*			 g_pEKSTOvalSurface		= NULL;
CSurface*			 g_pEKBlowerSurface		= NULL;
CSurface*			 g_pEKBigClearSurface	= NULL;

BOOL                 g_bActive				= FALSE; 
DWORD                g_dwLastTick;
SPRITE_STRUCT        g_Sprite[NUM_SPRITES]; 
HWND                 g_hWndDlg         = NULL;

#endif

