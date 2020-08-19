//----------------------------------------------------------------------------------------------
//
// GameState.cpp: Defines the various state data for the application as loaded from the
//				  STATE.GAM file or the NVRAM base address defined in NVRAM_BASE.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------

#define STRICT
#include "GameState.h"

//-----------------------------------------------------------------------------
// Name: CDisplay()
// Desc:
//-----------------------------------------------------------------------------
CGameState::CGameState()
{
	HRESULT	hr=NULL;

	m_hWnd		= NULL;
    ZeroMemory( &m_pGS, sizeof(m_pGS) );
    m_pRT		= NULL;
    m_pST		= NULL;
    m_dwAT		= NULL;
	m_bActive	= NULL;

	hr = LoadGameState();

}




//-----------------------------------------------------------------------------
// Name: ~CDisplay()
// Desc:
//-----------------------------------------------------------------------------
CGameState::~CGameState()
{
    DestroyObjects();
}




//-----------------------------------------------------------------------------
// Name: DestroyObjects()
// Desc: Internal helper Function used to help the class destructor release objects
//		 in a clean and safe fashion.
//-----------------------------------------------------------------------------
HRESULT CGameState::DestroyObjects()
{
    SAFE_DELETE( m_hWnd    );
    ZeroMemory( &m_pGS, sizeof(m_pGS) );
    SAFE_DELETE( m_pRT     );
    SAFE_DELETE( m_pST     );
    m_bActive = NULL;
	m_dwAT = NULL;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: LoadGameState()
// Desc: Internal helper Function used to load the CGameState class values. Loading
//		 can occur at anytime not just initialization time.
//-----------------------------------------------------------------------------
HRESULT CGameState::LoadGameState()
{
	int t,active=0;
	FILE *fp;

	if( (fp = fopen("state.gam","rb") ) == NULL) 
	{
		if( (fp = fopen("state.gam","a+b") ) == NULL)	// cant open file so create a new one
		{ 
         	return(-1);
      	}
      	else											// default settings
		{		
        	m_pGS.basex=0;
            m_pGS.basey=0;
        	memset(&m_pGS.tkt,0,sizeof(m_pGS.tkt));
        	m_pGS.played=0;							// initial meter values
            m_pGS.won=0;           
            m_pGS.credits=1000;						// during debugging phase only
            sprintf(m_pGS.port,"com2:");
        	fwrite(&m_pGS,sizeof(m_pGS),1,fp);			// write the default values to the file.
		   	fclose(fp);
            return(0);
      	}
	}
   	if(fread(&m_pGS,sizeof(m_pGS),1,fp) == NULL) 
	{
        fclose(fp);
      	return(-1);
   	}
   	m_pGS.played=0;
    for(t=0;t<4;t++) 
	{
       	if(m_pGS.tkt[t].grpcount) 						// ALL TKTS SHOULD USE .price !!!!!
		{
        	m_pGS.played+=m_pGS.tkt[t].bet*m_pGS.tkt[t].combo;
           	active+=1;
        }
    }
   	fclose(fp);
	return(active);
}




//--------------------------------------------------------------------------------
// Name: UpdateGameState()
// Desc: Is a helper function used to dump the current game state to a disk file 
//		 called state.gam. or a memory location in the embedded system's NVRAM
//--------------------------------------------------------------------------------
HRESULT CGameState::UpdateGameState()
{
	FILE *fp;

	if( (fp = fopen("state.gam","r+b") ) != NULL) 
	{
    	rewind(fp);
       	fwrite(&m_pGS,sizeof(m_pGS),1,fp);
	   	fclose(fp);
    }
	return S_OK;
}

