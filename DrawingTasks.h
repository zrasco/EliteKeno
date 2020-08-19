//----------------------------------------------------------------------------------------------
//
// DrawingTasks.h : Global Defines for the DrawingTasks Properties and Methods of the Elite Keno 
// Slot Machine Application.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, & Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------
#ifndef DRAWINGTASKS_H
#define DRAWINGTASKS_H


#include "main.h"
#include "ddutil.h"
#include "GameState.h"

//---------------------------------------------------------------------------

extern int TopNbrs[];
extern int BotNbrs[];
extern int LeftNbrs[];
extern int RightNbrs[];
extern int EdgeNbrs[];
extern int OddNbrs[];
extern int EvenNbrs[];
extern int POWbtn;
extern int POWpage;

extern HRESULT DrawBackground(CDisplay** ppDisplay, CSurface* pSurface, 
							  HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawGameLogo(CDisplay** ppDisplay, CSurface* pSurface, 
							HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawBetMeter(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, HBITMAP hNbr,
							HBITMAP hPunc, long lBet, DWORD xPos, DWORD yPos);
extern HRESULT DrawWonMeter(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, HBITMAP hNbr,
							HBITMAP hPunc, long lWon, DWORD xPos, DWORD yPos);
extern HRESULT DrawCreditMeter(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, HBITMAP hNbr,
							   HBITMAP hPunc, long lCerdits, DWORD xPos, DWORD yPos);
extern HRESULT DrawGameStat(CDisplay** ppDisplay, CSurface* pSurface, 
							HBITMAP hBMP, DWORD MsgNum, DWORD xPos, DWORD yPos);
extern HRESULT DrawTouchOne(CDisplay** ppDisplay, CSurface* pSurface, 
							HBITMAP hBMP, DWORD MsgNum, DWORD xPos, DWORD yPos);
extern HRESULT DrawFrame1(CDisplay** ppDisplay, CSurface* pSurface, 
				 		  HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawFrame2(CDisplay** ppDisplay, CSurface* pSurface, 
						  HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawFrame3(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
						  DWORD xPos, DWORD yPos);
extern HRESULT DrawFrame4(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
						  DWORD xPos, DWORD yPos);
extern HRESULT DrawFrame5(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
						  DWORD xPos, DWORD yPos);
extern HRESULT DrawTouchTktMessage(CDisplay** ppDisplay, CSurface* pSurface, 
								   HBITMAP hBMP, DWORD MsgNum, DWORD xPos, DWORD yPos);
extern HRESULT DrawDefaultSmallTicketHeader(CDisplay** ppDisplay, CSurface* pSurface, 
											HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawDefaultSmallTicketBase(CDisplay** ppDisplay, CSurface* pSurface, 
										  HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawBigTicketBase(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, 
								 HBITMAP hBMP, HBITMAP hSpotBMP[81], DWORD xPos, DWORD yPos);
extern HRESULT DrawBigTicketHeader(CDisplay** ppDisplay, CSurface* pSurface, 
								   HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawORMsg(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
						 DWORD xPos, DWORD yPos);
extern HRESULT DrawMessageCenter(CDisplay** ppDisplay, CSurface* pSurface, 
								 HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawMsgCntrText(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, DWORD yPos );
extern HRESULT DrawMsgCntrTextScroll(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, int xSubPos, DWORD yPos);
extern HRESULT DrawMsgCntrTextScrollL(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, int xSubPos, DWORD yPos);
extern HRESULT DrawHiLiteEKButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
								 DWORD dwBtnState, DWORD xPos, DWORD yPos);
extern HRESULT DrawEKButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
							DWORD dwBtnState, DWORD xPos, DWORD yPos);
extern HRESULT DrawCashOutButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
								 DWORD dwBtnState, DWORD xPos, DWORD yPos);
extern HRESULT DrawHiLiteCashOutButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
								DWORD dwBtnState, DWORD xPos, DWORD yPos);
extern HRESULT DrawClearButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
								 DWORD dwBtnState, DWORD xPos, DWORD yPos);
extern HRESULT DrawHiLiteClearButton(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
								DWORD dwBtnState, DWORD xPos, DWORD yPos);
extern HRESULT DrawTouchOneMsg(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
							   DWORD dwMsgNum, DWORD xPos, DWORD yPos);
extern HRESULT DrawChangeBet(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
							 DWORD xPos, DWORD yPos);
/* Zebs externs */
extern HRESULT DrawBigDrawBase(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int index, int nbrs[21],
						  HBITMAP hBMP, HBITMAP hSpotBMP[81], DWORD xPos, DWORD yPos);
extern HRESULT DrawPayScreen(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP, 
							 DWORD xPos, DWORD yPos);
extern HRESULT DrawHelpBG(CDisplay** ppDisplay, CSurface* pSurface,
					   HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawHelpScreen(CDisplay** ppDisplay, CSurface* pSurface,
					   HBITMAP hBMP, DWORD xPos, DWORD yPos);
extern HRESULT DrawTicketText(CDisplay** ppDisplay, CSurface* pSurface,
							  HBITMAP hBMPFont, HBITMAP hBMPNbrs, char* text, DWORD xPos, DWORD yPos);
extern HRESULT DrawBigOval(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMP);
extern HRESULT DrawBigBetText(CDisplay** ppDisplay, CSurface* pSurface,
							  HBITMAP hBMPOval, HBITMAP hBMPPunc, HBITMAP hBMPNbrs, char value[]);
extern HRESULT DrawTktTypes(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP Images[]);
extern HRESULT DrawWayLtrs(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, HBITMAP hBMPLTBase, HBITMAP hBMPWayLtrs);
extern HRESULT DrawWayBox(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info, HBITMAP hBMPWayNbrs, HBITMAP hBMPBtn);
extern int DrawWayBox2(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info, HBITMAP hBMPWayNbrs, HBITMAP hBMPBtn, int w, int c);
extern HRESULT DrawWayBoxBlanks(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info, unsigned int blankcombos[21], HBITMAP hBMPBtn);
extern HRESULT DrawBlowerPortion(CDisplay** ppDisplay, CSurface* pSurface, int height,
						  HBITMAP hBMPBackground, HBITMAP hBMPBlower, DWORD xPos, DWORD yPos);
extern HRESULT DrawBallDrop(CDisplay** ppDisplay, CSurface* pSurface, int index, int DrawNbrs[80],
							HBITMAP hBMPBlower, HBITMAP hBMPBalls, DWORD xPos, DWORD yPos);
extern HRESULT DrawFullBlower(CDisplay** ppDisplay, CSurface* pSurface, int DrawNbrs[80],
							HBITMAP hBMPBlower, HBITMAP hBMPBalls, DWORD xPos, DWORD yPos);
extern HRESULT DrawPOWHeader(CDisplay** ppDisplay, CSurface* pSurface,
					  HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, char* wayline, DWORD xPos, DWORD yPos);


/* Small ticket drawing functions */
extern HRESULT DrawSmallWayTicket(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt,
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlGrpLtr, DWORD xPos, DWORD yPos);
extern HRESULT DrawSmallSpotTicket(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt,
									 HBITMAP hBMPSTBase, HBITMAP hSpotBMP[81], DWORD xPos, DWORD yPos);
extern HRESULT DrawSmallSpecialTicket(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt,
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlSpecial, DWORD xPos, DWORD yPos);
extern HRESULT DrawSmallWayTicketC(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt, int cnumber, int DrawNbrs[80], HBITMAP SmallNbr[81],
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlGrpLtr, DWORD xPos, DWORD yPos);
extern HRESULT DrawSmallSpotTicketC(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt, int cnumber, int DrawNbrs[80], HBITMAP SmallNbr[81],
									 HBITMAP hBMPSTBase, DWORD xPos, DWORD yPos);
extern HRESULT DrawSmallSpecialTicketC(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, int tkt, int cnumber, int DrawNbrs[80], HBITMAP SmallNbr[81],
									 HBITMAP hBMPSTBase, HBITMAP hBMPSmlSpecial, DWORD xPos, DWORD yPos);
extern HRESULT DrawSmallTicketHeader(CDisplay** ppDisplay, CSurface* pSurface,
									 HBITMAP hBMPBlankHdr, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, char* text, DWORD xPos, DWORD yPos);
extern HRESULT DrawSmallBetText(CDisplay** ppDisplay, CSurface* pSurface, int tkt,
							HBITMAP hBMPOval, HBITMAP hBMPPunc, HBITMAP hBMPNbrs, char value[], DWORD xPos, DWORD yPos);
extern bool CalcBigXY(int spot, int *xpos, int *ypos);
extern bool CalcXY(int spot,int *xpos,int *ypos);
extern int CalcWinSpot(CGameState* pGS, int t,int spot);

#endif // DRAWINGTASKS_H