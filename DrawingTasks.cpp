//----------------------------------------------------------------------------------------------
//
// DrawingTasks.cpp : Defines the applications various drawing tasks to be preformed upon the 
//					  applications Direct Draw Display and the surfaces that the application
//					  uses to display its graphics.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------

#define STRICT

#include <tchar.h>
#include "Main.h"
#include "DrawingTasks.h"

int TopNbrs[]= { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40 };
int BotNbrs[]= {41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80 };
int LeftNbrs[]={ 1,2,3,4,5,11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45,51,52,53,54,55,61,62,63,64,65,71,72,73,74,75 };
int RightNbrs[]={6,7,8,9,10,16,17,18,19,20,26,27,28,29,30,36,37,38,39,40,46,47,48,49,50,56,57,58,59,60,66,67,68,69,70,76,77,78,79,80 };
int EdgeNbrs[]={ 1,2,3,4,5,6,7,8,9,10,11,20,21,30,31,40,41,50,51,60,61,70,71,72,73,74,75,76,77,78,79,80 };
int OddNbrs[]= { 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79 };
int EvenNbrs[]={ 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80 };
int UDNbrs[] = { 1,11,21,31,2,12,22,32,3,13,23,33,4,14,24,34,5,15,25,35,6,16,26,36,7,17,27,37,8,18,28,38,9,19,29,39,10,20,30,40,
				41,51,61,71,42,52,62,72,43,53,63,73,44,54,64,74,45,55,65,75,46,56,66,76,47,57,67,77,48,58,68,78,49,59,69,79,50,60,70,80 };
int BOXNbrs[]= { 1,2,11,12,3,4,13,14,5,6,15,16,7,8,17,18,9,10,19,20,21,22,31,32,23,24,33,34,25,26,35,36,27,28,37,38,29,30,39,40,
				41,42,51,52,43,44,53,54,45,46,55,56,47,48,57,58,49,50,59,60,61,62,71,72,63,64,73,74,65,66,75,76,67,68,77,78,69,70,79,80 };
//int POWlines=0;
//int POWpages=0;
//int POWpage=0;
//int POWbtn=0;		// MORE or BACK or both visible
//RECT from,to;
RECT bfrom,bto;

//-----------------------------------------------------------------------------
// Name: DrawBackground(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Background for the entire game display area.
//---------------------------------------------------------------------------
HRESULT DrawBackground(CDisplay** ppDisplay, CSurface* pSurface, 
						HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	//if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)))
	//	return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}



//-----------------------------------------------------------------------------
// Name: DrawGameLogo(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Slot Machine Game Logo on the display area.
//-----------------------------------------------------------------------------
HRESULT DrawGameLogo(CDisplay** ppDisplay, CSurface* pSurface, 
					 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	//if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 156, 79)))
	//	return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

HRESULT DrawPayScreen(CDisplay** ppDisplay, CSurface* pSurface,
					   HBITMAP hBMP, DWORD xPos, DWORD yPos)
/*
** DrawPayScreen
** Draws the pay table screen, specified in hBMP
*/
{
	HRESULT hr = NULL;

	if (FAILED(hr = pSurface->DrawBitmap(hBMP,0,0,604,405)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}

HRESULT DrawHelpBG(CDisplay** ppDisplay, CSurface* pSurface,
					   HBITMAP hBMP, DWORD xPos, DWORD yPos)
/*
** DrawHelpBG
** Draws the help screen background
*/
{
	HRESULT hr = NULL;

	if (FAILED(hr = pSurface->DrawBitmap(hBMP,0,0,630,436)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}

HRESULT DrawHelpScreen(CDisplay** ppDisplay, CSurface* pSurface,
					   HBITMAP hBMP, DWORD xPos, DWORD yPos)
/*
** DrawHelpScreen()
** Will draw the specified help screen to the background surface
*/
{
	HRESULT hr = NULL;

	if (FAILED(hr = pSurface->DrawBitmapPart(hBMP,15,15,0,0,602,412)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: DrawBetMeter(CDisplay**, CSurface*, HBITMAP, HBITMAP, HBITMAP, long, DWORD, DWORD)
// Desc: Method used to show the Bet Meter and its current value.
//---------------------------------------------------------------------------
HRESULT DrawBetMeter(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, HBITMAP hNbr,
					 HBITMAP hPunc, long lBet, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	char buffer[10];
	char work[10];
	int d,len,offset,nbr;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 116, 28)))
		return hr;

    memset(&work,0,sizeof(work)); 
	ltoa(lBet, buffer, 10);  
	len = strlen(buffer);

	switch(len)
	{
		case 0:
    		work[3]='0'; work[2]='0'; work[1]='.'; work[0]='0'; len=4;
			break;
		case 1:
			work[3]=buffer[0]; work[2]='0'; work[1]='.'; work[0]='0'; len=4;
			break;
		case 2:
    		work[3]=buffer[1]; work[2]=buffer[0]; work[1]='.'; work[0]='0'; len=4;
			break;
		case 3:
    		work[3]=buffer[2]; work[2]=buffer[1]; work[1]='.'; work[0]=buffer[0]; len=4;
			break;
		case 4:
    		work[4]=buffer[3]; work[3]=buffer[2]; work[2]='.'; work[1]=buffer[1]; 
			work[0] = buffer[0];len=5;
			break;
		case 5:
    		work[5]=buffer[4]; work[4]=buffer[3]; work[3]='.'; 
			work[2]=buffer[2]; work[1]=buffer[1]; work[0]=buffer[0];len=6;
			break;
		case 6:
    		work[7]=buffer[5]; work[6]=buffer[4]; work[5]='.'; work[4]=buffer[3];
			work[3]=buffer[2]; work[2]=buffer[1]; work[1]=','; work[0]=buffer[0];len=8;
			break;
		case 7:
    		work[8]=buffer[6]; work[7]=buffer[5]; work[6]='.'; work[5]=buffer[4];
			work[4]=buffer[3]; work[3]=buffer[2]; work[2]=','; work[1]=buffer[1];
			work[0]=buffer[0]; len=9;
			break;
		case 8:
    		work[9]=buffer[7]; work[8]=buffer[6]; work[7]='.'; work[6]=buffer[5];
			work[5]=buffer[4]; work[4]=buffer[3]; work[3]=','; work[2]=buffer[2];
			work[1]=buffer[1]; work[0]=buffer[0]; len=10;
			break;
		case 9:
    		work[11]=buffer[8]; work[10]=buffer[7]; work[9]='.'; work[8]=buffer[6];
			work[7]=buffer[5]; work[6]=buffer[4]; work[5]=','; work[4]=buffer[3];
			work[3]=buffer[2]; work[2]=buffer[1]; work[1]=','; work[0]=buffer[0]; len=12;
			break;
	} 
						
	offset=99;
    for(d=len-1;d>=0;d--) 
	{
		nbr=work[d];
        if(nbr>='0' && nbr<='9') 
		{
			nbr-='0';
			if( FAILED (hr = pSurface->DrawBitmapPart(hNbr, offset, 2, 0, (nbr*25), 13, 24)))
				return hr;
        }
        else 
		{
			offset+=6;
        	if(nbr=='.')
            	nbr=0;
            else
				nbr=25;

			if( FAILED (hr = pSurface->DrawBitmapPart(hPunc, offset, 2, 0, nbr, 7, 24)))
				return hr;
        }
		offset-=13;
    }

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);
	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawWonMeter(CDisplay**, CSurface*, HBITMAP, HBITMAP, HBITMAP, long, DWORD, DWORD)
// Desc: Method used to show the Won Meter and its current value.
//---------------------------------------------------------------------------
HRESULT DrawWonMeter(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, HBITMAP hNbr,
					 HBITMAP hPunc, long lWon, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	char buffer[10];
	char work[10];
	int d,len,offset,nbr;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 136, 28)))
		return hr;

    memset(&work,0,sizeof(work)); 
	ltoa(lWon, buffer, 10);  
	len = strlen(buffer);

	switch(len)
	{
		case 0:
    		work[3]='0'; work[2]='0'; work[1]='.'; work[0]='0'; len=4;
			break;
		case 1:
			work[3]=buffer[0]; work[2]='0'; work[1]='.'; work[0]='0'; len=4;
			break;
		case 2:
    		work[3]=buffer[1]; work[2]=buffer[0]; work[1]='.'; work[0]='0'; len=4;
			break;
		case 3:
    		work[3]=buffer[2]; work[2]=buffer[1]; work[1]='.'; work[0]=buffer[0]; len=4;
			break;
		case 4:
    		work[4]=buffer[3]; work[3]=buffer[2]; work[2]='.'; work[1]=buffer[1]; 
			work[0] = buffer[0];len=5;
			break;
		case 5:
    		work[5]=buffer[4]; work[4]=buffer[3]; work[3]='.'; 
			work[2]=buffer[2]; work[1]=buffer[1]; work[0]=buffer[0];len=6;
			break;
		case 6:
    		work[7]=buffer[5]; work[6]=buffer[4]; work[5]='.'; work[4]=buffer[3];
			work[3]=buffer[2]; work[2]=buffer[1]; work[1]=','; work[0]=buffer[0];len=8;
			break;
		case 7:
    		work[8]=buffer[6]; work[7]=buffer[5]; work[6]='.'; work[5]=buffer[4];
			work[4]=buffer[3]; work[3]=buffer[2]; work[2]=','; work[1]=buffer[1];
			work[0]=buffer[0]; len=9;
			break;
		case 8:
    		work[9]=buffer[7]; work[8]=buffer[6]; work[7]='.'; work[6]=buffer[5];
			work[5]=buffer[4]; work[4]=buffer[3]; work[3]=','; work[2]=buffer[2];
			work[1]=buffer[1]; work[0]=buffer[0]; len=10;
			break;
		case 9:
    		work[11]=buffer[8]; work[10]=buffer[7]; work[9]='.'; work[8]=buffer[6];
			work[7]=buffer[5]; work[6]=buffer[4]; work[5]=','; work[4]=buffer[3];
			work[3]=buffer[2]; work[2]=buffer[1]; work[1]=','; work[0]=buffer[0]; len=12;
			break;
	} 
						
	offset=119;
    for(d=len-1;d>=0;d--) 
	{
		nbr=work[d];
        if(nbr>='0' && nbr<='9') 
		{
			nbr-='0';
			if( FAILED (hr = pSurface->DrawBitmapPart(hNbr, offset, 2, 0, (nbr*25), 13, 24)))
				return hr;
        }
        else 
		{
			offset+=6;
        	if(nbr=='.')
            	nbr=0;
            else
				nbr=25;

			if( FAILED (hr = pSurface->DrawBitmapPart(hPunc, offset, 2, 0, nbr, 7, 24)))
				return hr;
        }
		offset-=13;
    }

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);
	return S_OK;
}



//-----------------------------------------------------------------------------
// Name: DrawCreditMeter(CDisplay**, CSurface*, HBITMAP, HBITMAP, HBITMAP, long, DWORD, DWORD)
// Desc: Method used to show the Bet Meter and its current value.
//---------------------------------------------------------------------------
HRESULT DrawCreditMeter(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, HBITMAP hNbr,
						HBITMAP hPunc, long lCredits, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	char buffer[10];
	char work[10];
	int d,len,offset,nbr;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 152, 28)))
		return hr;

    memset(&work,0,sizeof(work)); 
	ltoa(lCredits, buffer, 10);
	len = strlen(buffer);

	switch(len)
	{
		case 0:
    		work[3]='0'; work[2]='0'; work[1]='.'; work[0]='0'; len=4;
			break;
		case 1:
			work[3]=buffer[0]; work[2]='0'; work[1]='.'; work[0]='0'; len=4;
			break;
		case 2:
    		work[3]=buffer[1]; work[2]=buffer[0]; work[1]='.'; work[0]='0'; len=4;
			break;
		case 3:
    		work[3]=buffer[2]; work[2]=buffer[1]; work[1]='.'; work[0]=buffer[0]; len=4;
			break;
		case 4:
    		work[4]=buffer[3]; work[3]=buffer[2]; work[2]='.'; work[1]=buffer[1]; 
			work[0] = buffer[0];len=5;
			break;
		case 5:
    		work[5]=buffer[4]; work[4]=buffer[3]; work[3]='.'; 
			work[2]=buffer[2]; work[1]=buffer[1]; work[0]=buffer[0];len=6;
			break;
		case 6:
    		work[7]=buffer[5]; work[6]=buffer[4]; work[5]='.'; work[4]=buffer[3];
			work[3]=buffer[2]; work[2]=buffer[1]; work[1]=','; work[0]=buffer[0];len=8;
			break;
		case 7:
    		work[8]=buffer[6]; work[7]=buffer[5]; work[6]='.'; work[5]=buffer[4];
			work[4]=buffer[3]; work[3]=buffer[2]; work[2]=','; work[1]=buffer[1];
			work[0]=buffer[0]; len=9;
			break;
		case 8:
    		work[9]=buffer[7]; work[8]=buffer[6]; work[7]='.'; work[6]=buffer[5];
			work[5]=buffer[4]; work[4]=buffer[3]; work[3]=','; work[2]=buffer[2];
			work[1]=buffer[1]; work[0]=buffer[0]; len=10;
			break;
		case 9:
    		work[11]=buffer[8]; work[10]=buffer[7]; work[9]='.'; work[8]=buffer[6];
			work[7]=buffer[5]; work[6]=buffer[4]; work[5]=','; work[4]=buffer[3];
			work[3]=buffer[2]; work[2]=buffer[1]; work[1]=','; work[0]=buffer[0]; len=12;
			break;
	} 

	offset=135;
    for(d=len-1;d>=0;d--) 
	{
		nbr=work[d];
        if(nbr>='0' && nbr<='9') 
		{
			nbr-='0';
			if( FAILED (hr = pSurface->DrawBitmapPart(hNbr, offset, 2, 0, (nbr*25), 13, 24)))
				return hr;
        }
        else 
		{
			offset+=6;
        	if(nbr=='.')
            	nbr=0;
            else
				nbr=25;

			if( FAILED (hr = pSurface->DrawBitmapPart(hPunc, offset, 2, 0, nbr, 7, 24)))
				return hr;
        }
		offset-=13;
    }

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);
	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawGameStat(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD, DWORD)
// Desc: Method used to show the gamestat message above the button box.
//---------------------------------------------------------------------------
HRESULT DrawGameStat(CDisplay** ppDisplay, CSurface* pSurface, 
					 HBITMAP hBMP, DWORD MsgNum, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	int yOffSet = 0;

	if(MsgNum == 2)
		yOffSet = 22;
	else if(MsgNum == 3)
		yOffSet = 44;
	else
		yOffSet = 0;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, yOffSet, 156, 22)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}



//-----------------------------------------------------------------------------
// Name: DrawTouchOne(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD, DWORD)
// Desc: Method used to show the touch one message in the button box.
//---------------------------------------------------------------------------
HRESULT DrawTouchOne(CDisplay** ppDisplay, CSurface* pSurface, 
					 HBITMAP hBMP, DWORD MsgNum, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	int yOffSet = 0;

	if(MsgNum == 2)
		yOffSet = 19;
	else if(MsgNum == 3)
		yOffSet = 38;
	else
		yOffSet = 0;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, yOffSet, 143, 19)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: DrawTheRSideMessage(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD, DWORD)
// Desc: Method used to show the Right Side Message Surface in its proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawTouchTktMessage(CDisplay** ppDisplay, CSurface* pSurface, 
							HBITMAP hBMP, DWORD MsgNum, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	int yOffSet = 0;
	
	if(MsgNum == 2)
		yOffSet = 57;
	else if(MsgNum == 3)
		yOffSet = 114;
	else
		yOffSet = 0;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, yOffSet, 145, 57)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}


//-----------------------------------------------------------------------------
// Name: DrawFrame1(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Right Side Message Surface in its proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawFrame1(CDisplay** ppDisplay, CSurface* pSurface, 
								 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	//if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 162, 65)))
	//	return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}




//-----------------------------------------------------------------------------
// Name: DrawFrame2(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Right Side Message Surface in its proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawFrame2(CDisplay** ppDisplay, CSurface* pSurface, 
								 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 162, 141)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawFrame3(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Right Side Message Surface in its proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawFrame3(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
				   DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 164, 324)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawFrame4(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Right Side Message Surface in its proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawFrame4(CDisplay** ppDisplay, CSurface* pSurface, 
								 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 164, 424)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawFrame5(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Right Side Message Surface in its proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawFrame5(CDisplay** ppDisplay, CSurface* pSurface, 
								 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 204, 406)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawORMsg(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Right Side or Message Surface in its proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawORMsg(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 29, 20)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawDefaultSmallTicketHeader()
// Desc: Method used to show the initialized Small Ticket Surface in its 
//       proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawDefaultSmallTicketHeader(CDisplay** ppDisplay, CSurface* pSurface, 
									 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	
	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 200, 18)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}


//-----------------------------------------------------------------------------
// Name: DrawDefaultSmallTicketBase()
// Desc: Method used to show the initialized Small Ticket Surface in its 
//       proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawDefaultSmallTicketBase(CDisplay** ppDisplay, CSurface* pSurface, 
									 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	
	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 204, 186)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}

HRESULT DrawSmallWayTicket(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt,
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlGrpLtr, DWORD xPos, DWORD yPos)
/*
** DrawSmallWayTicket()
** This function draws the small group letters onto small way tickets
*/
{
	HRESULT hr = NULL;
	int g, s, nbr, letter = 0, x, y;
	bool valid;
	char buf[256];

	//pSurface->Clear(SCREEN_COLORKEY);
	if( FAILED (hr = pSurface->DrawBitmap(hBMPSTBase, 0, 0, 204, 186)))
		return hr;

	for (g = 0; g < pGS->m_pGS.tkt[tkt].grpcount; g++)
	{
		valid = false;

		for (s = 0; s < 20; s++)
		{
			nbr = pGS->m_pGS.tkt[tkt].groups[g][s];

			if (nbr)
			{
				valid = true;
				
				if (CalcXY(nbr,&x,&y))
				{
					pSurface->DrawBitmapPart(hBMPSmlGrpLtr,x,y,0,letter * 11,10,11);
				}
				else
					return NULL;
			}
			else
				break;
		}

		if (valid)
			letter++;
	}


	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}

HRESULT DrawSmallSpotTicket(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt,
									 HBITMAP hBMPSTBase, HBITMAP hSpotBMP[81], DWORD xPos, DWORD yPos)
/*
** DrawSmallSpotTicket()
** Draws a small "spot ticket"(straight & quick pick)
*/
{
	HRESULT hr = NULL;
	int s, nbr, x, y;

	//pSurface->Clear(SCREEN_COLORKEY);
	if( FAILED (hr = pSurface->DrawBitmap(hBMPSTBase, 0, 0, 204, 186)))
		return hr;

	for (s = 0; s < 20; s++)
	{
		nbr = pGS->m_pGS.tkt[tkt].groups[0][s];

		if (nbr)
		{
			if (CalcXY(nbr,&x,&y))
			/* Get X/Y coordinates & draw to small ticket surface */
				pSurface->DrawBitmapPart(hSpotBMP[nbr],x,y,0,36,17,17);
		}
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

HRESULT DrawSmallSpecialTicket(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt,
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlSpecial, DWORD xPos, DWORD yPos)
/*
** DrawSmallSpecialTicket()
** Draws a small special ticket
*/
{
	HRESULT hr = NULL;
	int index, letter = 0, x, y;

	//pSurface->Clear(SCREEN_COLORKEY);
	if( FAILED (hr = pSurface->DrawBitmap(hBMPSTBase, 0, 0, 204, 186)))
		return hr;
	
	switch (pGS->m_pGS.tkt[tkt].rate)
	{
		case 0:
			return NULL;
    	case 1:			// top/bottom
			for (index = 0; index < 40; index++)
			{
				if (CalcXY(TopNbrs[index],&x,&y))
				/* Get X/Y for top numbers */
					pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,18 * 7,17,17);

				if (CalcXY(BotNbrs[index],&x,&y))
				/* ...and the bottom ones */
					pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,18 * 5,17,17);
			}
        	break;
    	case 2:			// left/right
			for (index = 0; index < 40; index++)
			{
				if (CalcXY(LeftNbrs[index],&x,&y))
				/* Get X/Y for left numbers */
					pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,18 * 3,17,17);

				if (CalcXY(RightNbrs[index],&x,&y))
				/* also the right numbers */
					pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,18,17,17);
			}
        	break;
        case 3 :		// edge
        	for (index = 0; index < 32; index++)
				if (CalcXY(EdgeNbrs[index],&x,&y))
				/* Now get X/Y coordinates for edge numbers */
					pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,18 * 11,17,17);
        	break;
    	case 4:			// odd/even
			for (index = 0; index < 40; index++)
			{
				if (CalcXY(OddNbrs[index],&x,&y))
				/* First do odd numbers */
					pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,18 * 9,17,17);

				if (CalcXY(EvenNbrs[index],&x,&y))
				/* Then, even numbers */
					pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,18 * 11,17,17);
			}
        	break;
	}
	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

HRESULT DrawSmallWayTicketC(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt, int cnumber, int DrawNbrs[80], HBITMAP SmallNbr[81],
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlGrpLtr, DWORD xPos, DWORD yPos)
/*
** DrawSmallWayTicketC()
** Draws a small way ticket with catches
*/
{
	int i1, c = DrawNbrs[0], x, y, letr;

	/* First draw the ticket to the surface */
	DrawSmallWayTicket(ppDisplay,pSurface,pGS,tkt,hBMPSTBase,hBMPSmlGrpLtr,xPos,yPos);

	for (i1 = 0; i1 <= cnumber; i1++)
	/* Go through catches and draw them on the ticket */
	{
		if (CalcXY(DrawNbrs[i1],&x,&y))
		{
			letr = CalcWinSpot(pGS,tkt,DrawNbrs[i1]);

			if (letr)
			/* Spot is valid */
			{
				if (i1 == cnumber)
					pGS->m_pGS.tkt[tkt].caught[0]++;
				pSurface->DrawBitmapPart(SmallNbr[DrawNbrs[i1]],x,y,0,0,17,17);
			}
			else
				pSurface->DrawBitmapPart(SmallNbr[DrawNbrs[i1]],x,y,0,18,17,17);

			if (pGS->m_pGS.tkt[tkt].grpcount > 1 && letr)
			/* Draw way letter on top */
				pSurface->DrawBitmapPart(hBMPSmlGrpLtr,x,y,0,(letr - 1) * 11,11,11);
		}
	}

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);

	return S_OK;
}

HRESULT DrawSmallSpecialTicketC(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt, int cnumber, int DrawNbrs[80], HBITMAP SmallNbr[81],
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlSpecial, DWORD xPos, DWORD yPos)
/*
** DrawSmallSpecialTicketC()
** Draws the a small specials ticket with catches
*/
{
	int i1, c = DrawNbrs[0], x, y, letr, ytop;

	/* First draw the ticket to the surface */
	DrawSmallSpecialTicket(ppDisplay,pSurface,pGS,tkt,hBMPSTBase,hBMPSmlSpecial,xPos,yPos);

	for (i1 = 0; i1 <= cnumber; i1++)
	/* Go through catches and draw them on the ticket */
	{
		if (CalcXY(DrawNbrs[i1],&x,&y))
		{
			letr = CalcWinSpot(pGS,tkt,DrawNbrs[i1]);

			switch (letr)
			{
				case 'T':
					ytop = 6 * 18;
				break;
				case 'B':
					ytop = 4 * 18;
				break;
				case 'L':
					ytop = 2 * 18;
				break;
				case 'R':
					ytop = 0;
				break;
				case 'E':
					ytop = 10 * 18;
				break;
				case 'O':
					ytop = 8 * 18;
				break;
				default:
					letr = 0;
				break;
			}

			if (letr)
			{
				if (i1 == cnumber && (letr == 'T' || letr == 'L' || letr == 'E'))
					pGS->m_pGS.tkt[tkt].caught[0]++;
				else
					if (i1 == cnumber)
						pGS->m_pGS.tkt[tkt].caught[1]++;
				pSurface->DrawBitmapPart(hBMPSmlSpecial,x,y,0,ytop,17,17);
			}
			else
				pSurface->DrawBitmapPart(SmallNbr[DrawNbrs[i1]],x,y,0,18,17,17);

		}
	}

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);

	return S_OK;
}

HRESULT DrawSmallSpotTicketC(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt, int cnumber, int DrawNbrs[80], HBITMAP SmallNbr[81],
									 HBITMAP hBMPSTBase, DWORD xPos, DWORD yPos)
/*
** DrawSmallSpotTicketC()
** Draws a spot ticket, along with the catches
*/
{
	int i1, c = DrawNbrs[0], x, y, letr;

	/* First draw the ticket to the surface */
	DrawSmallSpotTicket(ppDisplay,pSurface,pGS,tkt,hBMPSTBase,&SmallNbr[0],xPos,yPos);

	for (i1 = 0; i1 <= cnumber; i1++)
	/* Go through catches and draw them on the ticket */
	{
		if (CalcXY(DrawNbrs[i1],&x,&y))
		{
			letr = CalcWinSpot(pGS,tkt,DrawNbrs[i1]);

			if (letr)
			/* Spot is valid */
			{
				pSurface->DrawBitmapPart(SmallNbr[DrawNbrs[i1]],x,y,0,0,17,17);
				if (i1 == cnumber)				
					pGS->m_pGS.tkt[tkt].caught[0]++;
			}
			else
				pSurface->DrawBitmapPart(SmallNbr[DrawNbrs[i1]],x,y,0,18,17,17);
		}
	}

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);

	return S_OK;
}
HRESULT DrawSmallTicketHeader(CDisplay** ppDisplay, CSurface* pSurface,
									 HBITMAP hBMPBlankHdr, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, char* text, DWORD xPos, DWORD yPos)
/*
** DrawSmallTicketHeader()
** This function draws the small ticket header
*/
{
	HRESULT hr = NULL;
	HBITMAP hBMP = hBMPFont;
	BITMAP FontInfo;
	int let, pos = 0, xpos = 10;

	/* First draw blank header */
	if( FAILED (hr = pSurface->DrawBitmap(hBMPBlankHdr, 0, 0, 200, 18)))
		return hr;

	GetObject(hBMP,sizeof(FontInfo),&FontInfo);

	while (text[pos] != '\0')
	/* Fill in header surface with appropriate text */
	{
		let = text[pos];

		if ((let >= 'A' && let <= 'Z') || let == ' ')
		{
			if (let >= 'A' && let <= 'Z')
				let -= 'A';
			else
				let = 26;

			hBMP = hBMPFont;
		}
		else if (let >= '0' && let <= '9')
		{
			let -= '0';
			hBMP = hBMPNbrs;
		}
		else if (let == '.' || let == ',')
		{
			if (let == '.')
				let = 1;
			else
				let = 2;
			
			hBMP = hBMPPunc;
		}

		if (hBMP != hBMPPunc)
			pSurface->DrawBitmapPart(hBMP,xpos,3,let * 7,0,6,FontInfo.bmHeight);
		else
			pSurface->DrawBitmapPart(hBMP,xpos,3,let * 3,0,2,FontInfo.bmHeight);

		pos++;
		xpos+= 7;
	}
	

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);

	return S_OK;
}

HRESULT DrawBigDrawBase(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int index, int nbrs[21],
						  HBITMAP hBMP, HBITMAP hSpotBMP[81], DWORD xPos, DWORD yPos)
/*
** DrawBigDrawBase()
** Draws the big ticket draw with the corresponding X's
*/
{
	HRESULT hr = NULL;
	HBITMAP hSPOT = NULL;
	int count, x, y;

	for (count = 0; count <= index; count++)
	{
		if(CalcBigXY(nbrs[index], &x, &y))
		{
			hSPOT = (hSpotBMP[nbrs[index]]);
			if( FAILED (hr = pSurface->DrawBitmapPart(hSPOT, x, y, 0, 80, 40, 40)))
				return hr;
		}
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}
//-----------------------------------------------------------------------------
// Name: DrawBigTicketBase()
// Desc: Class method used to show the initialized BigTicket Surface in its 
//       proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawBigTicketBase(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, 
						  HBITMAP hBMP, HBITMAP hSpotBMP[81], DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	HBITMAP hSPOT = NULL;
	int ix, iy, CT, n;
	int x,y;

	
	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 442, 402)))
		return hr;

	CT = pGS->GetActiveTicket();CT--;

	switch(pGS->m_pGS.tkt[CT].type)
	{
		case tQUICKPICK:
		case tSTRAIGHT:
			for(ix=0;ix<=20;ix++)
			{
				if(CalcBigXY(pGS->m_pGS.tkt[CT].groups[0][ix], &x, &y))
				{
					hSPOT = (hSpotBMP[pGS->m_pGS.tkt[CT].groups[0][ix]]);
					if( FAILED (hr = pSurface->DrawBitmapPart(hSPOT, x, y, 0, 80, 40, 40)))
						return hr;
				}
			}
			break;

		case tWAYTKT:
			for(ix=0;ix<=20;ix++)
			{
				for(iy=0;iy<=20;iy++)
				{
					if(CalcBigXY(pGS->m_pGS.tkt[CT].groups[ix][iy], &x, &y))
					{
						hSPOT = (hSpotBMP[pGS->m_pGS.tkt[CT].groups[ix][iy]]);
						if( FAILED (hr = pSurface->DrawBitmapPart(hSPOT, x, y, 0, 80, 40, 40)))
							return hr;
					}
				}
			}
			break;

		case tTOPBOT:
		/* Draw top-to-bottom */

			hSPOT = hSpotBMP[0];

			for (n=0 ; n < 40 ; n++)
			{
				if (CalcBigXY(TopNbrs[n],&x,&y))
				{
					if ( FAILED (hr = pSurface->DrawBitmapPart(hSPOT,x,y,1,280,40,40)))
						return hr;
				}
			}

			for (n = 0; n < 40; n++)
			{
				if (CalcBigXY(BotNbrs[n], &x, &y))
				{
					if ( FAILED (hr = pSurface->DrawBitmapPart(hSPOT,x,y,1,200,40,40)))
						return hr;
				}
			}
			break;

		case tLEFTRT:
		/* Draw left-to-right */

			hSPOT = hSpotBMP[0];

			for (n=0 ; n < 40 ; n++)
			{
				if (CalcBigXY(LeftNbrs[n],&x,&y))
				{
					if ( FAILED (hr = pSurface->DrawBitmapPart(hSPOT,x,y,1,120,40,40)))
						return hr;
				}
			}

			for (n = 0; n < 40; n++)
			{
				if (CalcBigXY(RightNbrs[n], &x, &y))
				{
					if ( FAILED (hr = pSurface->DrawBitmapPart(hSPOT,x,y,1,40,40,40)))
						return hr;
				}
			}

			break;

		case tEDGE:
		/* Draw Edges */
			hSPOT = hSpotBMP[0];
			for (n = 0; n < 32; n++)
			{
				if (CalcBigXY(EdgeNbrs[n], &x, &y))
				{
					if ( FAILED (hr = pSurface->DrawBitmapPart(hSPOT,x,y,1,440,40,40)))
						return hr;
				}
			}

			break;

		case tODDEVEN:
		/* Draw Odd/Even */
			hSPOT = hSpotBMP[0];

			for (n=0 ; n < 40 ; n++)
			{
				if (CalcBigXY(OddNbrs[n],&x,&y))
				{
					if ( FAILED (hr = pSurface->DrawBitmapPart(hSPOT,x,y,1,360,40,40)))
						return hr;
				}
			}

			for (n = 0; n < 40; n++)
			{
				if (CalcBigXY(EvenNbrs[n], &x, &y))
				{
					if ( FAILED (hr = pSurface->DrawBitmapPart(hSPOT,x,y,1,440,40,40)))
						return hr;
				}
			}
			break;

		case t190UD:

			break;

		case t190BOX:

			break;

		case tHZROW:

			break;

		case tVTROW:

			break;
	}





	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}




//-----------------------------------------------------------------------------
// Name: DrawBigTicketBase()
// Desc: Class method used to show the initialized BigTicket Surface in its 
//       proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawBigTicketHeader(CDisplay** ppDisplay, CSurface* pSurface, 
									 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	
	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 435, 45)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}


//-----------------------------------------------------------------------------
// Name: DrawMessageCenter(CDisplay**, CSurface*, HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Message Center on the Main Screen Drawing Surface.
//---------------------------------------------------------------------------
HRESULT DrawMessageCenter(CDisplay** ppDisplay, CSurface* pSurface, 
					 HBITMAP hBMP, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 418, 25)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: DrawMsgCntrText(CDisplay**, CSurface*, HFONT, TCHAR*, COLORREF, COLORREF, DWORD, DWORD)
// Desc: Method used to show the Text inside the Message Center Drawing Surface.
//---------------------------------------------------------------------------
HRESULT DrawMsgCntrText(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, DWORD yPos )
{
	HRESULT hr = NULL;
	HBITMAP hBMP = hBMPFont;
	BITMAP FontInfo, PuncInfo;
	int count = 0, letter = 0, x = 5, y = 3;

	/*
    HDC     hDC;
    SIZE    sizeText;

    hDC = GetDC( NULL );

    if( hFont )
        SelectObject( hDC, hFont );

    GetTextExtentPoint32( hDC, strText, _tcslen(strText), &sizeText );
    ReleaseDC( NULL, hDC );

    if( FAILED( hr = pSurface->DrawText( hFont, strText, 0, 0, crBG, crFG ) ) )
        return hr;
	*/

	/*
	HRESULT hr = NULL;
	HBITMAP hBMP = hBMPNbrs;
	BITMAP FontInfo;
	int let, pos = 0, xpos = 29;

	GetObject(hBMP,sizeof(FontInfo),&FontInfo);

	while (text[pos] != '\0')
	{
		let = text[pos];

		if (let >= 'A' && let <= 'Z')
		{
			let -= 'A';
			hBMP = hBMPFont;
		}
		else if (let >= '0' && let <= '9')
		{
			let -= '0';
			hBMP = hBMPNbrs;
		}

		pSurface->DrawBitmapPart(hBMP,xpos,9,let * 14,0,13,FontInfo.bmHeight);

		pos++;
		xpos+= 14;
	}
	

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);

	return S_OK;
}
*/
	GetObject(hBMP,sizeof(FontInfo),&FontInfo);
	GetObject(hBMP,sizeof(PuncInfo),&PuncInfo);

	for (count = 0; strText[count] != 0; count++)
	{
		letter = strText[count];

		if (letter >= 'A' && letter <= 'Z')
		{
			letter -= 'A';
			pSurface->DrawBitmapPart(hBMPFont,x,y,letter * 8,0,8,FontInfo.bmHeight);
		}
		else if (letter >= '0' && letter <= '9')
		{
			letter -= '0';
			pSurface->DrawBitmapPart(hBMPNbrs,x,y,letter * 8,0,8,FontInfo.bmHeight);
		}
		else if (letter == '.' || letter == ',' || letter == ' ')
		{
			if (letter == '.')
				letter = 1;
			else if (letter == ',')
				letter = 2;
			else
				letter = 0;

			pSurface->DrawBitmapPart(hBMPPunc,x,y,letter * 3,0,2,PuncInfo.bmHeight);
		}

		x += 8;

	}



	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: DrawMsgCntrTextScroll(CDisplay**, CSurface*, HFONT, TCHAR*, COLORREF, COLORREF, DWORD, DWORD)
// Desc: Method used to show the Text inside the Message Center Drawing Surface.
//---------------------------------------------------------------------------
HRESULT DrawMsgCntrTextScroll(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, int xSubPos, DWORD yPos )
{
	HRESULT hr = NULL;
	HBITMAP hBMP = hBMPFont;
	BITMAP FontInfo, PuncInfo;
	int count = 0, letter = 0, x = xSubPos + 2, y = 3;

	GetObject(hBMP,sizeof(FontInfo),&FontInfo);
	GetObject(hBMP,sizeof(PuncInfo),&PuncInfo);

	for (count = 0; strText[count] != 0; count++)
	{

		if (x > 400)
			break;

		letter = strText[count];

		if (letter >= 'A' && letter <= 'Z')
		{
			letter -= 'A';
			pSurface->DrawBitmapPart(hBMPFont,x,y,letter * 8,0,8,FontInfo.bmHeight);
			x += 8;
		}
		else if (letter >= '0' && letter <= '9')
		{
			letter -= '0';
			pSurface->DrawBitmapPart(hBMPNbrs,x,y,letter * 8,0,8,FontInfo.bmHeight);
			x += 8;
		}
		else if (letter == '.' || letter == ',' || letter == ' ' || letter == '\"')
		{
			if (letter == '.')
				letter = 1;
			else if (letter == ',')
				letter = 2;
			else if (letter == '\"')
				letter = 3;
			else
				letter = 0;

			pSurface->DrawBitmapPart(hBMPPunc,x,y,letter * 3,0,3,PuncInfo.bmHeight);
			
			if (letter == 0)
				x += 8;
			else
				x += 4;
		}
	}
	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: DrawMsgCntrTextScrollL()
// Desc: Method used to scroll the text offset on the left
//---------------------------------------------------------------------------
HRESULT DrawMsgCntrTextScrollL(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, int xSubPos, DWORD yPos )
{
	HRESULT hr = NULL;
	HBITMAP hBMP = hBMPFont;
	BITMAP FontInfo, PuncInfo;
	int index = 0, count = 0, letter = 0, x = 2, y = 3, offset = 0;
	char buf[256];

	GetObject(hBMP,sizeof(FontInfo),&FontInfo);
	GetObject(hBMP,sizeof(PuncInfo),&PuncInfo);

	for (count = 0; strText[count] != 0; count++)
	/* Loop through string and figure out which pieces to add */
	{
		letter = strText[count];

        if (letter == '\"' || letter == ',' || letter == '.')
			index += 4;
		else
			index += 8;

		if (x > 408)
			break;

		if (index >= xSubPos)
		/* Enter drawing phase only if position is correct for current count */
		{
			if (letter >= 'A' && letter <= 'Z')
			{
				letter -= 'A';

				if (x != 2)
				{
					pSurface->DrawBitmapPart(hBMPFont,x,y,letter * 8,0,8,FontInfo.bmHeight);
					x += 8;
				}
				else
				{
					offset = index - xSubPos;

					if (offset != 0)
						pSurface->DrawBitmapPart(hBMPFont,x,y,(letter * 8) + (8 - offset),0,offset,FontInfo.bmHeight);

					x += offset;
				}
			}
			else if (letter >= '0' && letter <= '9')
			{
				letter -= '0';

				if (x != 2)
				{
					pSurface->DrawBitmapPart(hBMPNbrs,x,y,letter * 8,0,8,FontInfo.bmHeight);
					x += 8;
				}
				else
				{
					offset = index - xSubPos;
					
					if (offset != 0)
						pSurface->DrawBitmapPart(hBMPNbrs,x,y,(letter * 8) + (8 - offset),0,offset,FontInfo.bmHeight);

					x += offset;
				}
			}
			else if (letter == '.' || letter == ',' || letter == ' ' || letter == '\"')
			{
				if (letter == '.')
					letter = 1;
				else if (letter == ',')
					letter = 2;
				else if (letter == '\"')
					letter = 3;
				else
					letter = 0;

				if (x != 2)
				{
					pSurface->DrawBitmapPart(hBMPPunc,x,y,letter * 3,0,3,FontInfo.bmHeight);

					if (letter == 0)
						x += 8;
					else
						x += 4;
				}
				else
				{
					offset = index - xSubPos;

					if (offset != 0)
						pSurface->DrawBitmapPart(hBMPPunc,x,y,(letter * 3) + (3 - offset),0,offset,FontInfo.bmHeight);

					x += offset;
				}
			}
		}
	}
	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: DrawHiLiteEKButton()
// Desc: Method used to show the passed button on a button surface in its 
//       proper x/y orientation.
//-----------------------------------------------------------------------------
HRESULT DrawHiLiteEKButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
					 DWORD dwBtnState, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	
	switch(dwBtnState)
	{
		case SHOW_NORMAL:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 42, 73, 42)))
				return hr;
			break;

		case SHOW_HILITE:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 73, 42)))
				return hr;
			break;
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	// Updating the primary buffer with a blt
	LPDIRECTDRAWSURFACE7 pddsFrontBuffer = (*ppDisplay)->GetFrontBuffer();
	LPDIRECTDRAWSURFACE7 pddsBackBuffer = (*ppDisplay)->GetBackBuffer();

	if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
		return hr;


	return S_OK;

}




//-----------------------------------------------------------------------------
// Name: DrawEKButton()
// Desc: Method used to show the passed button on a button surface in its 
//       proper x/y orientation. Hilites are handled elsewhere 
//-----------------------------------------------------------------------------
HRESULT DrawEKButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
					 DWORD dwBtnState, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	
	switch(dwBtnState)
	{
		case SHOW_NORMAL:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 42, 73, 42)))
				return hr;
			break;

		case SHOW_HILITE:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 73, 42)))
				return hr;
			break;
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}




//-----------------------------------------------------------------------------
// Name: DrawCashOutButton()
// Desc: Method used to show the passed button on a button surface in its 
//       proper x/y orientation. Hilites are handled elsewhere 
//-----------------------------------------------------------------------------
HRESULT DrawCashOutButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
					 DWORD dwBtnState, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	
	switch(dwBtnState)
	{
		case SHOW_NORMAL:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 42, 51, 42)))
				return hr;
			break;

		case SHOW_HILITE:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 51, 42)))
				return hr;
			break;
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}

//-----------------------------------------------------------------------------
// Name: DrawHiLiteCashOutButton()
// Desc: Method used to show the cash out button on a button surface in its 
//       proper x/y orientation. Hilites are handled elsewhere 
//-----------------------------------------------------------------------------
HRESULT DrawHiLiteCashOutButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
					 DWORD dwBtnState, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;
	
	switch(dwBtnState)
	{
		case SHOW_NORMAL:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 42, 51, 42)))
				return hr;
			break;

		case SHOW_HILITE:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 51, 42)))
				return hr;
			break;
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	// Updating the primary buffer with a blt
	LPDIRECTDRAWSURFACE7 pddsFrontBuffer = (*ppDisplay)->GetFrontBuffer();
	LPDIRECTDRAWSURFACE7 pddsBackBuffer = (*ppDisplay)->GetBackBuffer();

	if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
		return hr;


	return S_OK;

}

extern HRESULT DrawClearButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
								 DWORD dwBtnState, DWORD xPos, DWORD yPos)
/*
** DrawClearButton()
** Draws the big CLEAR button in the specified location
*/
{
	HRESULT hr = NULL;
	
	switch(dwBtnState)
	{
		case SHOW_NORMAL:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 42, 164, 42)))
				return hr;
			break;

		case SHOW_HILITE:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 164, 42)))
				return hr;
			break;
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}
extern HRESULT DrawHiLiteClearButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
								DWORD dwBtnState, DWORD xPos, DWORD yPos)
/*
** DrawHiLiteClearButton()
** Draws the big CLEAR button highlighed in the specified location
*/
{
	HRESULT hr = NULL;
	
	switch(dwBtnState)
	{
		case SHOW_NORMAL:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 42, 164, 42)))
				return hr;
			break;

		case SHOW_HILITE:
			if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 164, 42)))
				return hr;
			break;
	}

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	// Updating the primary buffer with a blt
	LPDIRECTDRAWSURFACE7 pddsFrontBuffer = (*ppDisplay)->GetFrontBuffer();
	LPDIRECTDRAWSURFACE7 pddsBackBuffer = (*ppDisplay)->GetBackBuffer();

	if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
		return hr;

	return S_OK;

}

//-----------------------------------------------------------------------------
// Name: DrawTouchOneMsg()
// Desc: Method used to show the Touch One Message above the buttons in   
//       proper x/y orientation. 
//-----------------------------------------------------------------------------
HRESULT DrawTouchOneMsg(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
					 DWORD dwMsgNum, DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, (dwMsgNum * 19), 143, 19)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}



//-----------------------------------------------------------------------------
// Name: DrawChangeBet(CDisplay**, CSurface* HBITMAP, DWORD, DWORD)
// Desc: Method used to show the Change Bet Message above the amount buttons in   
//       proper x/y orientation. 
//-----------------------------------------------------------------------------
HRESULT DrawChangeBet(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
					  DWORD xPos, DWORD yPos)
{
	HRESULT hr = NULL;

	if( FAILED (hr = pSurface->DrawBitmap(hBMP, 0, 0, 96, 19)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;

}

HRESULT DrawTicketText(CDisplay** ppDisplay, CSurface* pSurface, 
					   HBITMAP hBMPFont, HBITMAP hBMPNbrs, char* text, DWORD xPos, DWORD yPos)
/* DrawTicketText()
** Draws specified text using the large ticket font .bmp file
*/
{
	HRESULT hr = NULL;
	HBITMAP hBMP = hBMPNbrs;
	BITMAP FontInfo;
	int let, pos = 0, xpos = 29;

	GetObject(hBMP,sizeof(FontInfo),&FontInfo);

	while (text[pos] != '\0')
	{
		let = text[pos];

		if (let >= 'A' && let <= 'Z')
		{
			let -= 'A';
			hBMP = hBMPFont;
		}
		else if (let >= '0' && let <= '9')
		{
			let -= '0';
			hBMP = hBMPNbrs;
		}

		pSurface->DrawBitmapPart(hBMP,xpos,9,let * 14,0,13,FontInfo.bmHeight);

		pos++;
		xpos+= 14;
	}
	

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);

	return S_OK;
}

HRESULT DrawPOWHeader(CDisplay** ppDisplay, CSurface* pSurface,
					  HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, char* wayline, DWORD xPos, DWORD yPos)
/*
** DrawPOWHeader()
** Function draws the specified text on the POW header surface
*/
{
	BITMAP bmInfo;
	bool putway=true;
    int letr;
	int m=0,x,y;

	GetObject(hBMPFont,sizeof(bmInfo),&bmInfo);

    x=xPos+8;
    y=yPos+5;
    while(putway) {
		if(wayline[m]) {
        	letr=wayline[m];
            if(letr>='A' && letr<='Z' || letr==' ') {
	            if(letr>='A' && letr<='Z')
		        	letr-='A';
                else letr=26;			// last position = ' '
				pSurface->DrawBitmapPart(hBMPFont,x,y,letr * 7,0,6,bmInfo.bmHeight);
            }
            else if(letr>='0' && letr<='9') {
	        	letr-='0';
				pSurface->DrawBitmapPart(hBMPNbrs,x,y,letr * 7,0,6,bmInfo.bmHeight);
            }
            else if(letr=='.') {
	        	letr=0;
				pSurface->DrawBitmapPart(hBMPPunc,x,y,letr * 7,0,6,bmInfo.bmHeight);
            }
            m++;
            x+=7;
        }
        else putway=false;
    }

	return S_OK;
}
HRESULT DrawBigBetText(CDisplay** ppDisplay, CSurface* pSurface,
							  HBITMAP hBMPOval, HBITMAP hBMPPunc, HBITMAP hBMPNbrs, char value[])
/* 
** DrawBigBetText()
** This function draws the bet amount(in yellow) inside of the oval
*/
{

	HRESULT hr = NULL;
	BITMAP bmNbrs, bmPunc;
	char work[10];
	int d,w,len,offset,nbr, xpos = 283;

	/* First, we'll redraw the oval itself */
	DrawBigOval(ppDisplay,pSurface,hBMPOval);

	GetObject(hBMPPunc,sizeof(bmPunc),&bmPunc);
	GetObject(hBMPNbrs,sizeof(bmNbrs),&bmNbrs);

    memset(&work,0,sizeof(work));
    len=strlen(value);
    if(len==0) {
    	work[2]='0';
        work[1]='0';
        work[0]='.';
        len=3;
    }
    else if(len==1) {
    	work[2]=value[0];
        work[1]='0';
        work[0]='.';
        len=3;
    }
    else if(len==2) {
    	work[2]=value[1];
        work[1]=value[0];
        work[0]='.';
        len=3;
    }
    else {
    	for(d=len,w=len;d>0;d--) {
			if(d==len-2) {
            	work[w--]='.';
                work[w--]=value[d-1];
            }
            else work[w--]=value[d-1];
        }
        len+=1;
    }
    offset=120;
    for(d=len-1;d>=0;d--) {
		nbr=work[d];
        if(nbr>='0' && nbr<='9') {
			nbr-='0';
			pSurface->DrawBitmapPart(hBMPNbrs, xpos + offset, 9, 0, (nbr * 30) + 1, bmNbrs.bmWidth, 28);
	        offset-=16;
        }
        else {
        	if(nbr=='.')
            	nbr=0;
            else nbr=1;
			pSurface->DrawBitmapPart(hBMPPunc, xpos + offset + 8, 9, 0, (nbr * 30) + 1, bmPunc.bmWidth, 28);
	        offset-=8;
        }
    }

	(*ppDisplay)->Blt(11,25,pSurface,NULL);

	return S_OK;
}

HRESULT DrawSmallBetText(CDisplay** ppDisplay, CSurface* pSurface, int tkt,
							HBITMAP hBMPOval, HBITMAP hBMPPunc, HBITMAP hBMPNbrs, char value[], DWORD xPos, DWORD yPos)
/*
** DrawSmallBetText()
** Draws the small ticket bet amount + oval inside the header
*/
{
	HRESULT hr = NULL;
	BITMAP bmNbrs, bmPunc;
	char work[10];
	int d,w,len,offset,nbr, xpos = 1;

	/* Fill surface with oval */
	if( FAILED (hr = pSurface->DrawBitmap(hBMPOval, 0, 0, 58, 16)))
		return hr;

	GetObject(hBMPPunc,sizeof(bmPunc),&bmPunc);
	GetObject(hBMPNbrs,sizeof(bmNbrs),&bmNbrs);

    memset(&work,0,sizeof(work));
    len=strlen(value);
    if(len==0) {
    	work[2]='0';
        work[1]='0';
        work[0]='.';
        len=3;
    }
    else if(len==1) {
    	work[2]=value[0];
        work[1]='0';
        work[0]='.';
        len=3;
    }
    else if(len==2) {
    	work[2]=value[1];
        work[1]=value[0];
        work[0]='.';
        len=3;
    }
    else {
    	for(d=len,w=len;d>0;d--) {
			if(d==len-2) {
            	work[w--]='.';
                work[w--]=value[d-1];
            }
            else work[w--]=value[d-1];
        }
        len+=1;
    }
    offset=45;
    for(d=len-1;d>=0;d--) {
		nbr=work[d];
        if(nbr>='0' && nbr<='9') {
			nbr-='0';
			pSurface->DrawBitmapPart(hBMPNbrs, xpos + offset, 1, 0, nbr * 14, bmNbrs.bmWidth, 13);
	        offset-=6;
        }
        else {
        	if(nbr=='.')
            	nbr=0;
            else nbr=1;
			pSurface->DrawBitmapPart(hBMPPunc, xpos + offset + 2, 1, 0, nbr * 14, bmPunc.bmWidth, 13);
	        offset-=6;
        }
    }

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);

	return S_OK;
}

HRESULT DrawBigOval(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP)
/*
** DrawBigOval()
** Function to draw the big red oval in the ticket header
*/
{
	BITMAP OvalInfo;

	GetObject(hBMP,sizeof(OvalInfo),&OvalInfo);

	pSurface->DrawBitmapPart(hBMP,309,4,0,0,OvalInfo.bmWidth,OvalInfo.bmHeight);

	(*ppDisplay)->Blt(11,25,pSurface,NULL);

	return S_OK;
}

HRESULT DrawTktTypes(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP Images[])
/*
** DrawTktTypes()
** Helper function to draw the special ticket types
*/
{
	BITMAP bm;
	int i;
    int x=550;
    int ypos[4] = { 37,92,147,202 };

	for(i=0;i<4;i++) {
		GetObject(Images[i],sizeof(bm),&bm);
		pSurface->DrawBitmap(Images[i],0,0,bm.bmWidth,bm.bmHeight);
		(*ppDisplay)->Blt(x,ypos[i],pSurface,NULL);
    }

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: CalcBigXY(int spot, int *xpos, int *ypos)
// Desc: Helper function used to calculate the x/y coordinates of a Big Ticket   
//       spot for marking the ticket in its proper x/y orientation. 
//---------------------------------------------------------------------------
bool CalcBigXY(int spot,int *xpos,int *ypos)
{
    int horizbase=8,horizoff=43;
    int vertbase=50,vertoff=43;

    if(!spot)
       	return(false);
   	else if(spot<=10) {
       	*xpos=horizbase+(horizoff*(spot-1));
        *ypos=vertbase;
    }
    else if(spot<=20) {
       	*xpos=horizbase+(horizoff*(spot-11));
        *ypos=vertbase+(vertoff*1);
    }
    else if(spot<=30) {
       	*xpos=horizbase+(horizoff*(spot-21));
        *ypos=vertbase+(vertoff*2);
    }
    else if(spot<=40) {
       	*xpos=horizbase+(horizoff*(spot-31));
        *ypos=vertbase+(vertoff*3);
    }
    else if(spot<=50) {
       	*xpos=horizbase+(horizoff*(spot-41));
        *ypos=vertbase+(vertoff*4);
    }
    else if(spot<=60) {
       	*xpos=horizbase+(horizoff*(spot-51));
        *ypos=vertbase+(vertoff*5);
    }
    else if(spot<=70) {
       	*xpos=horizbase+(horizoff*(spot-61));
        *ypos=vertbase+(vertoff*6);
    }
    else if(spot<=80) {
       	*xpos=horizbase+(horizoff*(spot-71));
        *ypos=vertbase+(vertoff*7);
    }
    else return(false);
    if(spot>=41) 		// crossed double line twix upper/lower half of tkt
    	*ypos+=3;
    return(true);
}

bool CalcXY(int spot,int *xpos,int *ypos)
/*
** CalcXY()
** Helper function used to mark placement of ticket spot offsets
** NOTE: Function returns X/Y coordinates to be used on the small tkt surface
*/
{
    int horizbase=3,horizoff=20;
    int vertbase=23,vertoff=20;

    if(!spot)
       	return(false);
   	else if(spot<=10) {
       	*xpos=horizbase+(horizoff*(spot-1));
        *ypos=vertbase;
    }
    else if(spot<=20) {
       	*xpos=horizbase+(horizoff*(spot-11));
        *ypos=vertbase+(vertoff*1);
    }
    else if(spot<=30) {
       	*xpos=horizbase+(horizoff*(spot-21));
        *ypos=vertbase+(vertoff*2);
    }
    else if(spot<=40) {
       	*xpos=horizbase+(horizoff*(spot-31));
        *ypos=vertbase+(vertoff*3);
    }
    else if(spot<=50) {
       	*xpos=horizbase+(horizoff*(spot-41));
        *ypos=vertbase+(vertoff*4);
    }
    else if(spot<=60) {
       	*xpos=horizbase+(horizoff*(spot-51));
        *ypos=vertbase+(vertoff*5);
    }
    else if(spot<=70) {
       	*xpos=horizbase+(horizoff*(spot-61));
        *ypos=vertbase+(vertoff*6);
    }
    else if(spot<=80) {
       	*xpos=horizbase+(horizoff*(spot-71));
        *ypos=vertbase+(vertoff*7);
    }
    else return(false);
    if(spot>=41) 		// crossed double line twix upper/lower half of tkt
    	*ypos+=1;
    return(true);
}

HRESULT DrawWayLtrs(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, HBITMAP hBMPLTBase, HBITMAP hBMPWayLtrs)
/*
** DrawWayLtrs()
** Draws the corresponding way letter boxes on the large ticket
*/
{
	HRESULT hr;
	int x, y, letr = -1, g, spot, s;
	char buf[256];

	int AT = pGS->GetActiveTicket(); AT--;

	if( FAILED (hr = pSurface->DrawBitmap(hBMPLTBase, 0, 0, 442, 402)))
		return hr;

	//if (pGS->m_pGS.tkt[AT].groups[0][0] != 0)
	//{
	//	sprintf(buf,"ticket: %d, grpcount: %d",AT,pGS->m_pGS.tkt[AT].grpcount);
	//	MessageBox(pGS->GetHWnd(),buf,"Hi",MB_OK);
	//}

	for ( g = 0; g < pGS->m_pGS.tkt[AT].grpcount;g++) {
		if(pGS->m_pGS.tkt[AT].groups[g][0])	// is there a spot here ?
	            letr++;						// yes, next group letter
		for(s=0;s<20;s++) {
			spot=pGS->m_pGS.tkt[AT].groups[g][s];
            if(spot) {
				if(CalcBigXY(spot,&x,&y)) {		// get XY coordinate
					pSurface->DrawBitmapPart(hBMPWayLtrs,x,y,0,letr * 22,21,22);
                }
                else break;
			}
            else break;
        }
	}

	(*ppDisplay)->Blt(8, 21, pSurface, NULL);

	return S_OK;
}

HRESULT DrawWayBoxBlanks(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info, unsigned int blankcombos[21], HBITMAP hBMPBtn)
/*
** DrawWayBoxBlanks()
** This function will draw the blanks on the passed array, based on the index values
*/
{
	HRESULT hr = NULL;
	int j;
	int xway[]= { 460,540,460,540,460,540,460,540,460,540 };
    int yway[]= { 39,39,85,85,131,131,177,177,223,223 };

	int CT = pGS->GetActiveTicket(); CT--;

	for (j = 0; j < 10; j++)
	{
		if (pGS->m_pGS.tkt[CT].ways[j])
		{
			if (info->combo[pGS->m_pGS.tkt[CT].ways[j]] != blankcombos[pGS->m_pGS.tkt[CT].ways[j]])
			/* Number has been affected, blank it out for now */
			{
				pSurface->DrawBitmapPart(hBMPBtn,0,0,5,5,41,13);

				(*ppDisplay)->Blt(xway[j] + 11,yway[j] - 1,pSurface,NULL);
			}
		}
	}

	return S_OK;
}
HRESULT DrawWayBox(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info, HBITMAP hBMPWayNbrs, HBITMAP hBMPBtn)
/*
** DrawWayBox()
** This function is used to draw the numbers inside of the way buttons
*/
{
	HRESULT hr = NULL;
	BITMAP NbrInfo;
	int j, testnum = 1;
	int xway[]= { 460,540,460,540,460,540,460,540,460,540 };
    int yway[]= { 39,39,85,85,131,131,177,177,223,223 };

	int CT = pGS->GetActiveTicket(); CT--;

	GetObject(hBMPWayNbrs,sizeof(NbrInfo),&NbrInfo);

	for (j = 0; j < 10; j++)
	{
		if (pGS->m_pGS.tkt[CT].ways[j])
		{
			if (info->combo[pGS->m_pGS.tkt[CT].ways[j]])
			{
				/* Fill fresh surface */
				pSurface->DrawBitmapPart(hBMPBtn,0,0,5,5,41,13);

				/* Individually draw the letters on the surface */
				DrawWayBox2(ppDisplay,pSurface,pGS,info,hBMPWayNbrs,hBMPBtn,pGS->m_pGS.tkt[CT].ways[j],info->combo[pGS->m_pGS.tkt[CT].ways[j]]);
				(*ppDisplay)->Blt(xway[j] + 11,yway[j] - 1,pSurface,NULL);
			}
		}
	}

	return S_OK;
}

int DrawWayBox2(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info, HBITMAP hBMPWayNbrs, HBITMAP hBMPBtn, int w, int c)
{
	BITMAP NbrInfo;
	bool putway=true;
    char waybox[30];
	int m=0,x = 1,nbr;

	memset(waybox,0,30);
	GetObject(hBMPWayNbrs,sizeof(NbrInfo),&NbrInfo);
    sprintf(waybox,"%d",c);

    while(putway) {
		if(waybox[m]) {
        	nbr=waybox[m];
            if(nbr>='0' && nbr<='9') {
            	nbr-='0';
				pSurface->DrawBitmapPart(hBMPWayNbrs,x,0,0,NbrInfo.bmHeight - (nbr * 14) - 28,NbrInfo.bmWidth,13);
				x+=12;
            }
			m++;
        }
        else putway=false;
    }

	return 0;
}

HRESULT DrawBlowerPortion(CDisplay** ppDisplay, CSurface* pSurface, int height,
						  HBITMAP hBMPBackground, HBITMAP hBMPBlower, DWORD xPos, DWORD yPos)
/*
** DrawBlowerPortion()
** This function will draw a portion of the blower, by specified height
*/
{
	HRESULT hr = NULL;

	/* Fill the surface with the background behind it */
	if( FAILED (hr = pSurface->DrawBitmapPart(hBMPBackground, 0, 0, xPos, yPos, 155, 400)))
		return hr;

	/* Draw blower on surface up to specified height */
	if( FAILED (hr = pSurface->DrawBitmapPart(hBMPBlower, 0, 0, 0, 70, 152, height)))
		return hr;

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

HRESULT DrawFullBlower(CDisplay** ppDisplay, CSurface* pSurface, int DrawNbrs[80],
							HBITMAP hBMPBlower, HBITMAP hBMPBalls, DWORD xPos, DWORD yPos)
/*
** DrawFullBlower()
** This function draws the blower with all 20 balls in it
*/
{
	HRESULT hr = NULL;
	int count;
	int x[] = { 32, 85 };						/* X of 2 tubes */
	int yi = 0, y[] = {
			335,
			300,
			265,
			230,
			195,
			160,
			125,
			90,
			55,
			20};
			/* Y positions */

	if ( FAILED (hr = pSurface->DrawBitmapPart(hBMPBlower, 0, 0, 0, 70, 152, 398) ) )
		return hr;

	for (count = 0; count < 20; count++)
	/* One at a time, we blt the keno balls to the surface */
	{
		if (count < 10)
			pSurface->DrawBitmapPart(hBMPBalls,x[0],y[count], 0, (DrawNbrs[count] - 1) * 35,35,35);
		else
			pSurface->DrawBitmapPart(hBMPBalls,x[1],y[count - 10], 0, (DrawNbrs[count] - 1) * 35,35,35);
	}
	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	return S_OK;
}

HRESULT DrawBallDrop(CDisplay** ppDisplay, CSurface* pSurface, int index, int DrawNbrs[80],
							HBITMAP hBMPBlower, HBITMAP hBMPBalls, DWORD xPos, DWORD yPos)
/*
** DrawBallDrop()
** Shows the specified ball dropping inside the tube
*/
{
	HRESULT hr = NULL;
	int start, count, advance = OPT_BALLDROPADVANCE, height, base;
	int xi, x[] = { 32, 85 };						/* X of 2 tubes */
	int yi = 0, y[] = {
			335,
			300,
			265,
			230,
			195,
			160,
			125,
			90,
			55,
			20};
			/* Y positions */

	LPDIRECTDRAWSURFACE7 pddsFrontBuffer, pddsBackBuffer;

	if ( FAILED (hr = pSurface->DrawBitmapPart(hBMPBlower, 0, 0, 0, 70, 152, 398) ) )
		return hr;

	/* Animate ball drop */

	for (count = 0; count < index; count++)
	/* First lets blt the previous balls to the surface */
	{
		if (count < 10)
			pSurface->DrawBitmapPart(hBMPBalls,x[0],y[count], 0, (DrawNbrs[count] - 1) * 35,35,35);
		else
			pSurface->DrawBitmapPart(hBMPBalls,x[1],y[count - 10], 0, (DrawNbrs[count] - 1) * 35,35,35);
	}

	/* Phase 2: Draw animation of new ball falling */

	if (index < 10)
	/* Draw ball in first tube */
	{
		xi = 0;
		yi = index;
	}
	else
	/* Second tube */
	{
		xi = 1;
		yi = index - 10;
	}

	pddsFrontBuffer = (*ppDisplay)->GetFrontBuffer();
	pddsBackBuffer = (*ppDisplay)->GetBackBuffer();

	start = y[9] - 5;

	for (count = 0; count < y[yi]; count += advance)
	/* Move ball down (advance) pixels, then fill in empty space with blower */
	{
		if (count < start)
		{
			base = start - count;
			height = 35 - base;
			pSurface->DrawBitmapPart(hBMPBalls,x[xi],start, 0, ((DrawNbrs[index] - 1) * 35) + base,35,height);
		}
		else
		{
			height = 35;
			base = 0;
			pSurface->DrawBitmapPart(hBMPBalls,x[xi],count, 0, ((DrawNbrs[index] - 1) * 35) + base,35,height);
			pSurface->DrawBitmapPart(hBMPBlower,x[xi],(count - advance), x[xi],(count - advance) + 70,35,advance);
		}

		(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

		if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
			return hr;
	}

	/* Draw new ball */
	pSurface->DrawBitmapPart(hBMPBalls,x[xi],y[yi], 0, (DrawNbrs[index] - 1) * 35,35,35);
	pSurface->DrawBitmapPart(hBMPBlower,x[xi],y[yi] - advance, x[xi],(y[yi] - advance) + 70,35,advance);

	(*ppDisplay)->Blt(xPos, yPos, pSurface, NULL);

	if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
		return hr;

	return S_OK;
}

int CalcWinSpot(CGameState* pGS, int t,int spot)
{
	int g,s,grpletr=1;

    if(pGS->m_pGS.tkt[t].rate==0) {
	    for(g=0;g<pGS->m_pGS.tkt[t].grpcount;g++,grpletr++) {
	    	for(s=0;s<20;s++) {
	     		if(spot==pGS->m_pGS.tkt[t].groups[g][s]) {
	            	tktcatch[t]+=1;
	            	return(grpletr);
	            }
	        }
	    }
    }
    else if(pGS->m_pGS.tkt[t].rate==1) {    // top/bottom
    	for(g=0;g<40;g++) {
        	if(spot==TopNbrs[g]) {
	           	tktcatch[t]+=1;
	           	return('T');
            }
        }
    	for(g=0;g<40;g++) {
        	if(spot==BotNbrs[g]) {
	           	tktcatch[t+4]+=1;
	           	return('B');
            }
        }
        return(false);
    }
    else if(pGS->m_pGS.tkt[t].rate==2) {	// left/right
    	for(g=0;g<40;g++) {
        	if(spot==LeftNbrs[g]) {
	           	tktcatch[t]+=1;
	           	return('L');
            }
        }
    	for(g=0;g<40;g++) {
        	if(spot==RightNbrs[g]) {
	           	tktcatch[t+4]+=1;
	           	return('R');
            }
        }
        return(false);
    }
    else if(pGS->m_pGS.tkt[t].rate==3) {	// edge
    	for(g=0;g<32;g++) {
        	if(spot==EdgeNbrs[g]) {
	           	tktcatch[t]+=1;
	           	return('E');
            }
        }
        return(false);
    }
    else if(pGS->m_pGS.tkt[t].rate==4) {	// odd/even
    	for(g=0;g<40;g++) {
        	if(spot==OddNbrs[g]) {
	           	tktcatch[t]+=1;
	           	return('O');
            }
        }
    	for(g=0;g<40;g++) {
        	if(spot==EvenNbrs[g]) {
	           	tktcatch[t+4]+=1;
	           	return('E');
            }
        }
        return(false);
    }
    return(false);
}
