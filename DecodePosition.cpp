//----------------------------------------------------------------------------------------------
//
// DecodePosition.cpp : Defines the application branching based upon the screen position of
//						of the mouse at the WM_LBUTTONUP Mouse Event.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------

#define STRICT
#include "Main.h"
#include "DecodePosition.h"

int POWtkt;

//-----------------------------------------------------------------------------
// Name: DecodePosition(int xPos, int yPos)
// Desc: Determine the current application mode and then based upon the state of
//       the game calculate the action that should precipitate based upon the
//		 current mouse x/y coordinate.
//-----------------------------------------------------------------------------
HRESULT DecodePosition(int xPos, int yPos, int nState)
{
    HRESULT hr;

	hr=CkWon(xPos, yPos);						// check to see if the won area was touched
    if(hr != 0)									// this is for testing phase only
		return(hr);
    //else if(CkVer(xPos, yPos))					// Need to add Hardware State Check for this
    //   	return(IDM_SHOW_DIALOG);				// event as soon as we get the stuff from McCleese.
	
	switch(nState)
	{
    	case sATTRACT:
            if(CkVer(xPos, yPos))				// TEST check version #
				hr=IDM_SHOW_DIALOG;
			else
				hr = IDM_MODE_IDLE;
			return(hr);
            break;

    	case sIDLE:
			hr=CkTkt(xPos, yPos);
        	if(hr != 0)							// tkt 1-4 selected
				return(hr);						
            else if(CkAddCredits(xPos, yPos))	// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED 
            	hr=IDF_KEY_F9;
			else
				hr=CkTktFunc(xPos, yPos);		// cashout, run game, add credits(TEST), exit(TEST)
            break;

        case sBIGTKTUP :						// big ticket visible, now what function ?
            if(CkAddCredits(xPos, yPos))		// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED
            	hr=IDF_KEY_F9;
            else
			{
	        	hr=GetBigSpot(xPos, yPos);		// spot 1-80 touched ?
				if(hr>=1 && hr<=80)
					return(hr);
				else
	        		hr=CkBigTktFunc(xPos, yPos);// quick pick,way tkt, specials, house, cancel
            }
        	break;

        case sSTRAIGHT :						// in straight ticket entry ?
            if(CkAddCredits(xPos, yPos))		// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED !!!!
            	return(IDF_KEY_F9);
            else 
			{
	        	hr=GetBigSpot(xPos, yPos);		// spot 1-80 touched ?
				if(hr>=1 && hr<=80)
					return(hr);
	        	hr=CkStraightStatus(xPos, yPos);// playit, cancel, change bet
				return(hr);
            }
        	break;

        case sQUICKPICK :						// in QUICK PICK
        case sQPENTRY :							// and qp selected
            if(CkAddCredits(xPos, yPos))		// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED 
            	hr=IDF_KEY_F9;
        	else
			{
				hr=CkQP(xPos,yPos);
				if(hr>0)
					return(hr);
				hr=CkStatus(xPos,yPos);			// playit, cancel, change bet
				return(hr);
			}
            break;
        
		case sWAYTKT :							// in WAY tickets
        case sWAYENTRY :
            if(CkAddCredits(xPos, yPos))		// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED 
            	hr=IDF_KEY_F9;
            else 
			{
	        	hr=GetBigSpot(xPos, yPos);		// spot 1-80 touched ?
				if(hr>=1 && hr<=80)
					return(hr);
	        	hr=CkWay(xPos, yPos);
				if(hr>0)
					return(hr);
	            hr=CkStatus(xPos, yPos);		// playit, cancel, change bet
				return(hr);
            }
            break;
        
		case sWAYPLAYIT :
            if(CkAddCredits(xPos, yPos))		// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED 
            	hr=IDF_KEY_F9;
            else 
			{
	        	hr=GetBigSpot(xPos, yPos);		// spot 1-80 touched ?
	            if(hr>=1 && hr<=80) 
	            	return(hr);					// more spots entered, not played
	        	else 
				{
					hr=CkWay(xPos, yPos);
					if (hr > 0)
						return hr;
					hr=CkStatus(xPos, yPos);	// playit, cancel, change bet
				}
            }
	        break;
        
		case sSPECIALS :						// in SPECIALS
        case sSPENTRY :
			hr=CkSP(xPos, yPos);
        	if(hr!=0)
            	return(hr);
            else if(CkAddCredits(xPos, yPos))	// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED
            	return(IDF_KEY_F9);
            else 
				hr=CkStatus(xPos, yPos);		// playit, cancel, change bet
            break;
        
		case sHOUSETKT :						// in HOUSE TICKETS
        case sHSENTRY :
            if(CkAddCredits(xPos, yPos))		// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED 
            	return(IDF_KEY_F9);
        	else 
			{
				hr=CkHouse(xPos, yPos);
				if (hr > 0)
					return hr;
				hr=CkStatus(xPos, yPos);		// playit, cancel, change bet
			}
			break;
        
		case sHZENTRY :							// in HORIZ row, waiting for 80# touch
        case sVTENTRY :							// in VERT row, waiting for 80# touch
            if(CkAddCredits(xPos, yPos))		// TEMP ADD $ 10.00 CREDITS IF CREDIT METER TOUCHED 
	           	return(IDF_KEY_F9);
            else 
			{
	        	hr=GetBigSpot(xPos, yPos);		// spot 1-80 touched ?

				if (hr >= 1 && hr <= 80)
					return hr;
				else
				{
					hr=CkHouse(xPos, yPos);			// changed to different tkt ?
					
					if (hr > 0)
						return hr;

					hr=CkStatus(xPos, yPos);		// playit, cancel, change bet
				}
            }
        	break;
        
		case sPAYTABLE1:						// in PAYTABLE screen
            if(xPos>=470 && xPos<=470+BW) 
			{									// game button
            	if(yPos>=440 && yPos<=440+BH)
                	hr=IDF_KEY_G;				// back to game
            }
            if(xPos>=550 && xPos<=550+BW) 
			{									// more button
            	if(yPos>=440 && yPos<=440+BH)
                	hr=IDF_KEY_M;				// more paytable
            }
			break;
        
		case sPAYTABLE2:						// in 2nd PAYTABLE screen
            if(xPos>=470 && xPos<=470+BW)		
			{									// game button
            	if(yPos>=440 && yPos<=440+BH)
                	hr=IDF_KEY_G;				// back to game
            }
            if(xPos>=550 && xPos<=550+BW) 
			{									// back button
            	if(yPos>=440 && yPos<=440+BH)
                	hr=IDF_KEY_B;				// back to 1st paytable
            }
            break;
        case sHELPSCRN:							// Help screen
			if (xPos >= 470 && xPos <= 470 + BW)
				if (yPos >= 440 && yPos <= 440 + BH)
					hr = IDF_KEY_G;
			break;
		case sDUMPBALLS:						// waiting to dump balls
        	hr=CkTkt(xPos, yPos);
            if(xPos>=464 && xPos<=618) 
			{
				if(yPos>=4 && yPos<=38)
		           	hr=IDF_KEY_C;				// big CLEAR button
            }
		    if(xPos>=470 && xPos<=470+BW) 
			{									// paytable button
    		   	if(yPos>=440 && yPos<=440+BH)
    		       	hr=IDF_KEY_Y;				// pa'y'able
    		}
        	break;
        
		case sPOW :								// showing a proof of win
            hr=CkPOWbtns(xPos, yPos);			// 'Touch' holds button (MORE/BACK)
            if(!hr)
			{
	        	hr=CkTkt(xPos, yPos);			// tkt 1-4 selected (clear PROOF OF WIN)
				if (hr)
					break;
			}
			if(xPos>=470 && xPos<=470+BW) 
			{									// paytable button
				if(yPos>=440 && yPos<=440+BH) 
	    			hr=IDF_KEY_Y;				// pa'y'able
    		}
	        if(xPos>=469 && xPos<=469 + BW) 
			{
				if(yPos>=4 && yPos<=38) 
			   		hr=IDF_KEY_R;				// Run game
            }
			if (xPos >= 465 + BW && xPos <= 465 + (BW * 2))
			{
				if (yPos >= 4 && yPos <= 38)
					hr = IDF_KEY_C;				// Clear button
			}
			if (OPT_USEBIGDRAW)
			{
				if (xPos>=20 && xPos<=438)
				{
					if (yPos>=232 && yPos<=257)
						hr=IDM_MODE_MSGTOUCH;				// TOUCH HERE message in big draw
				}
			}
            break;
	}
	return(hr);
}

//-----------------------------------------------------------------------------
// Name: CkTkt(int tx, int ty)
// Desc: Determine if the current mouse coordinates place the mouse within the 
//       drawing space of one of the 4 small tickets displayed during idle and
//		 attract mode.
//-----------------------------------------------------------------------------
long CkTkt(int tx, int ty)
{
   	if(tx>=24 && tx<=218) {				// ticket 1 or 3
       	if(ty>=42 && ty<=200)
           	return(IDF_KEY_F1);
        else if(ty>=264 && ty<=420)
           	return(IDF_KEY_F3);
    }
   	else if(tx>=240 && tx<=430) {		// ticket 2 or 4
       	if(ty>=42 && ty<=200)
           	return(IDF_KEY_F2);
        else if(ty>=264 && ty<=420)
          	return(IDF_KEY_F4);
    }
    return(0);
}
//-----------------------------------------------------------------------------
// Name: CkVer(int tx, int ty)
// Desc: Determine if the current mouse coordinates place the mouse within the 
//       drawing space of one of the star in the keno logo, and if so process.
//		 the first of the slot exit keys.
//-----------------------------------------------------------------------------
bool CkVer(int tx, int ty)		// TEST check version #
{
   	if(tx>=528 && tx<=554) {	// star above Elite 'K'ENO logo
       	if(ty>=12 && ty<=32)
           	return(true);
    }
    return(false);
}
//-----------------------------------------------------------------------------
// Name: CkAddCredits(int tx, int ty)
// Desc: Determine if the current mouse coordinates place the mouse within the 
//       drawing space of credits display, and if so process the second key of 
//		 the slot exit routine. (During test mode add credits)
//-----------------------------------------------------------------------------
bool CkAddCredits(int tx, int ty)	// temp click credits meter to add $ 10.00
{
    if(tx>=288 && tx<=435) {
       	if(ty>=450 && ty<=472)
           	return(true);		
    }
    return(false);
}
//-----------------------------------------------------------------------------
// Name: CkTktFunc(int tx, int ty)
// Desc: Determine if the current mouse coordinates place the mouse within the 
//       drawing space of one of the 4 small buttons displayed during idle and
//		 attract mode.
//-----------------------------------------------------------------------------
long CkTktFunc(int tx, int ty)
{
    if(tx>=508 && tx<=508+BW) {
       	if(ty>=368 && ty<=368+BH)
           	return(IDF_KEY_R);	// run game
        else if(ty>=296 && ty<=332) 	// cashout button
        	return(IDM_MODE_CASHOUT);
    }
    if(tx>=470 && tx<=470+BW) { 		// paytable button
       	if(ty>=440 && ty<=440+BH)
           	return(IDF_KEY_Y);	// pa'y'able
    }
    else if(tx>=550 && tx<=550+BW)		// use HELP button
	{	
       	if(ty>=440 && ty<=440+BH)
           	return(IDM_MODE_HELPSCREEN);// help button
    }
    return(0);
}
//-----------------------------------------------------------------------------
// Name: CkTkt(int tx, int ty)
// Desc: Determine if the current mouse coordinates place the mouse within the 
//       drawing space of one of the 5 small buttons displayed during sBIGTKTUP
//		 mode, and process the input.
//-----------------------------------------------------------------------------
long CkBigTktFunc(int tx, int ty)
{
   	if(tx>=468 && tx<=468+BW) {
       	if(ty>=245 && ty<=245+BH)
           	return(IDM_MODE_QUICKPICK);	// quick pick
       	else if(ty>=294 && ty<=294+BH)
           	return(IDM_MODE_SPECIALS);	// specials
    }
   	if(tx>=546 && tx<=546+BW) {
       	if(ty>=245 && ty<=245+BH)
           	return(IDM_MODE_WAYTICKET);	// way ticket
       	else if(ty>=294 && ty<=294+BH)
           	return(IDM_MODE_HOUSETICKET);// house ticket
	}
    if(tx>=508 && tx<=508+BW) {
       	if(ty>=380 && ty<=380+BH)
           	return(IDF_KEY_C);			 // cancel the ticket
    }
	return(0);
}
//-----------------------------------------------------------------------------
// Name: CkQP(int tx, int ty)
// Desc: Determine if the current mouse coordinates place the mouse within the 
//       drawing space of one of the 10 small buttons displayed during sQUICKPICK
//		 or sQPENTRY mode, and process the input.
//-----------------------------------------------------------------------------
long CkQP(int tx, int ty)
{
	if(tx>=470 && tx<=470+BW) 
	{		// 1st column of buttons
       	if(ty>=34 && ty<=34+BH)
	       	return(IDF_KEY_2);				// QP 2 spot
	    else if(ty>=80 && ty<=80+BH)
		   	return(IDF_KEY_4);
	    else if(ty>=126 && ty<=126+BH)
		   	return(IDF_KEY_6);
	    else if(ty>=172 && ty<=172+BH)
		   	return(IDF_KEY_8);
	    else if(ty>=218 && ty<=218+BH)
		   	return(IDF_KEY_0);
        else return(0);
    }
    else if(tx>=550 && tx<=550+BW) {
       	if(ty>=34 && ty<=34+BH)
           	return(IDF_KEY_3);
       	else if(ty>=80 && ty<=80+BH)
           	return(IDF_KEY_5);
       	else if(ty>=126 && ty<=126+BH)
           	return(IDF_KEY_7);
       	else if(ty>=172 && ty<=172+BH)
           	return(IDF_KEY_9);
       	else if(ty>=218 && ty<=218+BH)
           	return(IDF_KEY_1);
        else return(0);
    }
	return(0);
}
//-----------------------------------------------------------------------------
// Name: CkWay(int tx, int ty)
// Desc: Determine if the current mouse coordinates place the mouse within the 
//       drawing space of one of the 10 small buttons displayed during sWAYTKT
//		 and the sWAYENTRY modes, and process the input.
//-----------------------------------------------------------------------------
long CkWay(int tx, int ty)
{
	if(tx>=470 && tx<=470+BW) 
	{		// 1st column of buttons
       	if(ty>=36 && ty<=36+BH)
	       	return(IDF_KEY_A2);	
	    else if(ty>=82 && ty<=82+BH)
		   	return(IDF_KEY_A4);
	    else if(ty>=128 && ty<=128+BH)
		   	return(IDF_KEY_A6);
	    else if(ty>=174 && ty<=174+BH)
		   	return(IDF_KEY_A8);
	    else if(ty>=220 && ty<=220+BH)
		   	return(IDF_KEY_A0);
        else return(0);
    }
    else if(tx>=550 && tx<=550+BW) {
       	if(ty>=36 && ty<=36+BH)
           	return(IDF_KEY_A3);
       	else if(ty>=82 && ty<=82+BH)
           	return(IDF_KEY_A5);
       	else if(ty>=128 && ty<=128+BH)
           	return(IDF_KEY_A7);
       	else if(ty>=174 && ty<=174+BH)
           	return(IDF_KEY_A9);
       	else if(ty>=220 && ty<=220+BH)
           	return(IDF_KEY_A1);
        else return(0);
    }
	return(0);
}
//-----------------------------------------------------------------------------
// Name: CkStatus(int tx, int ty)
// Desc: Determine if the Play it or Cancel Key was clicked. If not, was one of 
//       the four bet amount keys clicked, and if so send a message to increase 
//		 or decrease the bet accordingly.
//-----------------------------------------------------------------------------
long CkStatus(int tx, int ty)
{
    if(tx>=470 && tx<=470+BW)
	{												// 1st column of buttons
    	if(ty>=268 && ty<=268+BH)
	       	return(IDF_KEY_P);						// play it
       	else if(ty>=334 && ty<=334+BH) 
			return(IDF_KEY_F5);
       	else if(ty>=380 && ty<=380+BH) 
			return(IDF_KEY_F7);
    }
	else if(tx>=550 && tx<=550+BW) 
	{												// 2nd column of buttons
       	if(ty>=268 && ty<=268+BH)
	       	return(IDF_KEY_C);	         			// cancel
        else if(ty>=334 && ty<=334+BH) 
			return(IDF_KEY_F6);
        else if(ty>=380 && ty<=380+BH) 
			return(IDF_KEY_F8);
		else if(ty>=440 && ty<=440+BH)
           	return(IDM_MODE_HELPSCREEN);			// help button
    }
	return(0);
}

//-----------------------------------------------------------------------------
// Name: CkWon(int tx, int ty)
// Desc: Determine if the Won meter was clicked. This will only have use during
//       the administrative mode as a part of the exit key strokes.
//-----------------------------------------------------------------------------
long CkWon(int tx, int ty)
{
   	if(tx>=147 && tx<=272) 
	{
       	if(ty>=449 && ty<=471)
        	return(IDM_MODE_ATTRACT);
    }
    return(0);        
}



//-----------------------------------------------------------------------------
// Name: CkStraightStatus(int tx, int ty)
// Desc: Exactly the same function as the CkStatus routine above, but for the 
//       positions used during sSTRAIGHT mode of play.
//-----------------------------------------------------------------------------
long CkStraightStatus(int tx, int ty)
{
    if(tx>=508 && tx<=508+BW) {
    	if(ty>=193 && ty<=193+BH)
	       	return(IDF_KEY_C);						// cancel
        else if(ty>=258 && ty<=258+BH)
        	return(IDF_KEY_P);						// play it
    }
    if(tx>=470 && tx<=470+BW) 
	{												// 1st column of buttons
       	if(ty>=334 && ty<=334+BH) 
			return(IDF_KEY_F5);
		else if(ty>=380 && ty<=380+BH) 
			return(IDF_KEY_F7);
    }
	else if(tx>=550 && tx<=550+BW) {// 2nd column of buttons
        if(ty>=334 && ty<=334+BH) 
			return(IDF_KEY_F6);
		else if(ty>=380 && ty<=380+BH)
			return(IDF_KEY_F8);
    }
	return(0);
}



//-----------------------------------------------------------------------------
// Name: CkSP(int tx, int ty)
// Desc: Check to see if one of the buttons was pressed that are displayed during  
//       sSPECIALS mode of play
//-----------------------------------------------------------------------------
long CkSP(int tx, int ty)
{
   	if(tx>=470 && tx<=470+BW) 
	{
       	if(ty>=43 && ty<=43+BH)
           	return(IDF_KEY_T);						// top/bottom
        else if(ty>=97 && ty<=97+BH)
           	return(IDF_KEY_L);						// left/right
        else if(ty>=151 && ty<=151+BH)
           	return(IDF_KEY_E);						// edge
        else if(ty>=205 && ty<=205+BH)
	       	return(IDF_KEY_O);						// odd/even
    }
	return(0);
}



//-----------------------------------------------------------------------------
// Name: CkHouse(int tx, int ty)
// Desc: Check to see if one of the buttons was pressed that are displayed during  
//       sHOUSETKT mode of play
//-----------------------------------------------------------------------------
long CkHouse(int tx, int ty)
{
   	if(tx>=470 && tx<=470+BW) 
	{
       	if(ty>=168 && ty<=168+BH)
           	return(IDF_KEY_U);						// 190 up/down
       	else if(ty>=214 && ty<=214+BH)
           	return(IDF_KEY_Z);						// horizontal row
    }
    else if(tx>=550 && tx<=550+BW) 
	{
       	if(ty>=168 && ty<=168+BH)
           	return(IDF_KEY_X);						// 190 boxes
       	else if(ty>=214 && ty<=214+BH)
           	return(IDF_KEY_V);						// vertical row
    }
	return(0);
}




bool CkMore(int tx, int ty)
{
	if(POWtkt==1 || POWtkt==3) {    	// right side tkt
		if(tx>=49 && tx<=49+BW) {
           	if(ty>=354 && ty<=354+BH)
            	return(true);
        }
    }
    else {								// left side tkt
		if(tx>=263 && tx<=263+BW) {
           	if(ty>=354 && ty<=354+BH)
            	return(true);
        }
    }
    return(false);
}
//---------------------------------------------------------------------------
bool CkBack(int tx, int ty)
{
	if(POWtkt==1 || POWtkt==3) {    	// right side tkt
		if(tx>=124 && tx<=124+BW) {
           	if(ty>=354 && ty<=354+BH)
            	return(true);
        }
    }
    else {								// left side tkt
		if(tx>=338 && tx<=338+BW) {
           	if(ty>=354 && ty<=354+BH)
            	return(true);
        }
    }
    return(false);
}
//-----------------------------------------------------------------------------
// Name: CkPOWbtns(int tx, int ty)
// Desc: Check to see if either the MORE or the BACK buttons was pressed that 
//       are visible during the Proof of Win Mode of play.
//-----------------------------------------------------------------------------
long CkPOWbtns(int tx, int ty)
{
    if(CkMore(tx, ty))
       	return(IDF_KEY_M);				// MORE
    else if(CkBack(tx, ty))
   	       return(IDF_KEY_B);			// BACK
	return(0);
}




//-----------------------------------------------------------------------------
// Name: GetBigSpot(int tx, int ty)
// Desc: Helper function used to decode the click if one of the ticket spots was  
//       clicked during any of the Big Ticket entry modes.
//-----------------------------------------------------------------------------
long GetBigSpot(int tx, int ty)
{
	int i;
    int col=-1,row=-1;
    int pick[10][8]={
    				{ 1,11,21,31,41,51,61,71 },
                    { 2,12,22,32,42,52,62,72 },
                    { 3,13,23,33,43,53,63,73 },
                    { 4,14,24,34,44,54,64,74 },
                    { 5,15,25,35,45,55,65,75 },
                    { 6,16,26,36,46,56,66,76 },
                    { 7,17,27,37,47,57,67,77 },
                    { 8,18,28,38,48,58,68,78 },
                    { 9,19,29,39,49,59,69,79 },
                    {10,20,30,40,50,60,70,80 } };
    int xbas=20,xwidth=32,xnxt=43;
    int ybas=75,yheight=32,ynxt=43;

   	for(i=0;i<10;i++) {
        if(tx>=xbas && tx<=xbas+xwidth) {	// column 1
        	col=i;
            break;
        }
        else xbas+=xnxt;
    }
    if(col!=-1) {
		for(i=0;i<8;i++) {
        	if(ty>=ybas && ty<=ybas+yheight) {
        		row=i;
           	    break;
           	}
           	else ybas+=ynxt;
       	}
    }
    if(col>=0 && row>=0)
       	return(pick[col][row]);
    return(0);
}


