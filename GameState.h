//----------------------------------------------------------------------------------------------
//
// GameState.h : Header file for CGameState class and global defines for the class properties 
//  			 and methods for use with the Elite Keno Slot Machine Application.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, & Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "main.h"

typedef struct GAME_STATE_STRUCT	FAR *LPGAMESTATE;
typedef struct RATE_TABLE_STRUCT	FAR *LPRATETABLE;
typedef struct SPECIAL_TABLE_STRUCT FAR *LPSPECIALTABLE;

//-----------------------------------------------------------------------------
// Miscellaneous helper functions
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }



//-----------------------------------------------------------------------------
// Class defined in this header file 
//-----------------------------------------------------------------------------
class CGameState;



//-----------------------------------------------------------------------------
// Flags for the CGameState methods
//-----------------------------------------------------------------------------
#define DGAMESTATELOCK_READ
#define DGAMESTATELOCK_WRITE



//-----------------------------------------------------------------------------
// Name: class CGameState
// Desc: Class to handle all aspects of the current GameState, including creation 
//       and destruction of the class itself. We will create methods for loading,
//       and updating the game state file as well as preserving the state in the
//		 event of a watchdog timer power failure event.
//-----------------------------------------------------------------------------
class CGameState
{
public:
    GAME_STATE_STRUCT		m_pGS;
	BOOL					m_bRedraw;
protected:
    HWND					m_hWnd;
    LPRATETABLE				m_pRT;
    LPSPECIALTABLE			m_pST;
    DWORD					m_dwAT;
    BOOL					m_bActive;
public:
	// Construction
    CGameState();

	// Destructor
    ~CGameState();

    // Access functions
    HWND				GetHWnd()           { return m_hWnd;		}
    GAME_STATE_STRUCT	GetGameState()		{ return m_pGS;			}
    LPRATETABLE			GetRateTable()		{ return m_pRT;			}
    LPSPECIALTABLE		GetSpecialTable()	{ return m_pST;			}
    DWORD				GetActiveTicket()	{ return m_dwAT;		}
	void		SetActiveTicket(DWORD dwAT)	{ m_dwAT = dwAT;		}

	/* Functions to set info */
	void				SetHWnd(HWND hWnd)	{ m_hWnd = hWnd;		}
    // Status functions
    BOOL				IsActive()			{ return m_bActive;		}

    // Creation/destruction methods
    HRESULT DestroyObjects();
	// Methods to create child objects

	// Attributes
    
	// Operations
	HRESULT LoadGameState();
	HRESULT UpdateGameState();
	
	// Display methods

	// Implementation
};


#endif // GAMESTATE_H
