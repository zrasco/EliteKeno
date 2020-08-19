//----------------------------------------------------------------------------------------------
//
// EliteKeno.cpp : Defines the entry point for the application.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------

#define STRICT
#include "EliteKeno.h"
#include <dshow.h>

#define high(x) ((x&(1<<31))?1:0)
#define TAP 0x1bL
#define WM_GRAPHNOTIFY  WM_APP + 1

BOOL brClick = FALSE;
BOOL bDraw120 = FALSE;

IGraphBuilder   *pGraph = NULL;
IMediaControl   *pMediaControl = NULL;
IVideoWindow    *pVidWin = NULL;
IMediaEventEx	*pEvent = NULL;
IMediaPosition	*pPos	= NULL;

//char *pszClear = "bmps\\buttons\\clear.bmp";
char *pszClear = "bmps\\buttons\\clear1.bmp";
char *pszBalls = "bmps\\balls\\ekballs.bmp";
char *pszBlower = "bmps\\playscrn\\blower.bmp";
//char *pszWayNbrs = "bmps\\playscrn\\waynbrs.bmp";
char *pszWayNbrs = "bmps\\playscrn\\waynbrs1.bmp";

char *EKBkgrnd = "bmps\\playscrn\\ekbase.bmp";
char *EKLogoPath = "bmps\\playscrn\\eklogo.bmp";
char *msgCenter = "bmps\\msgcntr\\message.bmp";
char *pszMsgFont = "bmps\\msgcntr\\msgtext\\msgaz.bmp";
//char *pszMsgFont = "bmps\\msgcntr\\msgtext\\msgaz1.bmp";
//char *pszMsgNbrs = "bmps\\msgcntr\\msgtext\\msgnbrs1.bmp";
char *pszMsgNbrs = "bmps\\msgcntr\\msgtext\\msgnbrs.bmp";
char *pszMsgPunc = "bmps\\msgcntr\\msgtext\\msgpunc.bmp";
//char *pszMsgPunc = "bmps\\msgcntr\\msgtext\\msgpunc1.bmp";
char *pszBigGrpLtr = "bmps\\largetkt\\groupltr.bmp";
char *pszSmlGrpLtr = "bmps\\smalltkt\\groupltr.bmp";
char *pszSmlHdrFont = "bmps\\smalltkt\\stfontaz.bmp";
char *pszSmlHdrNbrs = "bmps\\smalltkt\\stfontnb.bmp";
char *pszSmlHdrPunc = "bmps\\smalltkt\\stfontpc.bmp";
char *pszEKBtnPenny = "bmps\\buttons\\penny.bmp";

/* Help paths */
char* pszHelpBG = "bmps\\playscrn\\help\\helpbk.bmp";
char* pszHelpIdle = "bmps\\playscrn\\help\\helpidle.bmp";
char* pszHelpQP = "bmps\\playscrn\\help\\helpqp.bmp";
char* pszHelpSpecials = "bmps\\playscrn\\help\\helpspecial.bmp";
char* pszHelpWay = "bmps\\playscrn\\help\\helpway.bmp";
char* pszHelpHouse = "bmps\\playscrn\\help\\helphouse.bmp";

char *meterPath[] = {
	"bmps\\meters\\bet.bmp",
	"bmps\\meters\\won.bmp",
	"bmps\\meters\\credits.bmp"};
char *mtrNbrsPath = "bmps\\meters\\mtrnbrs.bmp";
char *mtrPuncPath = "bmps\\meters\\mtrpunc.bmp";

char *GameStatPath = "bmps\\playscrn\\gamestat.bmp";
char *OrLabelPath = "bmps\\playscrn\\or.bmp";
char *TouchTktPath = "bmps\\playscrn\\touchtkt.bmp";
char *TouchOnePath = "bmps\\playscrn\\touchone.bmp";
char *ChgBetPath = "bmps\\playscrn\\chgbet.bmp";

//-------------------------------------------------------------------------------------
// LARGE TICKET PARTS THAT MAKE UP THE TICKET
//-------------------------------------------------------------------------------------
char *LTBasePath = "bmps\\largetkt\\ltbase.bmp";
char *LTHeaderPath = "bmps\\largetkt\\ltrect.bmp";
char *LTSpecialMarkPath = "bmps\\largetkt\\largespt\\spclletr.bmp";
char *pszBigOval = "bmps\\largetkt\\ltoval.bmp";
char *pszBigHdrFont = "bmps\\largetkt\\ltfontaz.bmp";
char *pszBigHdrNbrs = "bmps\\largetkt\\ltfontnb.bmp";
char *pszBigBetPunc = "bmps\\largetkt\\ltpunc.bmp";
char *pszBigBetNbrs = "bmps\\largetkt\\ltnbrs.bmp";
//-------------------------------------------------------------------------------------
// SMALL TICKET PARTS THAT MAKE UP THE TICKET
//-------------------------------------------------------------------------------------
char *STBasePath = "bmps\\SmallTkt\\stbase.bmp";
char *stWinner = "bmps\\SmallTkt\\stwinner.bmp";
char *smheaders[] = {	"bmps\\SmallTkt\\Hdr1.bmp",
						"bmps\\SmallTkt\\Hdr2.bmp",
						"bmps\\SmallTkt\\Hdr3.bmp",
						"bmps\\SmallTkt\\Hdr4.bmp" };

char *pszSTBlankHdr= "bmps\\SmallTkt\\BlankHdr.bmp";

char *STSpecialMarkPath = "bmps\\smalltkt\\smallnbr\\stspecl.bmp";

char *pszSmlOval = "bmps\\smalltkt\\stoval.bmp";
char *pszSmlBetNbrs = "bmps\\smalltkt\\stnbrs.bmp";
char *pszSmlBetPunc = "bmps\\smalltkt\\stpunc.bmp";

char *btnArray[] = {	"bmps\\Buttons\\Cashout.bmp",
						"bmps\\Buttons\\Paytable.bmp",
						"bmps\\Buttons\\Help.bmp",
						"bmps\\Buttons\\Quickpik.bmp",
						"bmps\\Buttons\\Waytkt.bmp",
						"bmps\\Buttons\\Special.bmp",
						"bmps\\Buttons\\House.bmp",
						"bmps\\Buttons\\Cancel.bmp",
						"bmps\\Buttons\\Playit.bmp",
						"bmps\\Buttons\\Spots2.bmp",
						"bmps\\Buttons\\Spots3.bmp",
						"bmps\\Buttons\\Spots4.bmp",
						"bmps\\Buttons\\Spots5.bmp",
						"bmps\\Buttons\\Spots6.bmp",
						"bmps\\Buttons\\Spots7.bmp",
						"bmps\\Buttons\\Spots8.bmp",
						"bmps\\Buttons\\Spots9.bmp",
						"bmps\\Buttons\\Spots10.bmp",
						"bmps\\Buttons\\Spots20.bmp",
						"bmps\\Buttons\\nickel.bmp",
						"bmps\\Buttons\\quarter.bmp",
						"bmps\\Buttons\\Dollar1.bmp",
						"bmps\\Buttons\\Dollar5.bmp",
						"bmps\\Buttons\\Rungame.bmp",
						"bmps\\Buttons\\game.bmp",
						"bmps\\Buttons\\more.bmp",
						"bmps\\Buttons\\back.bmp",
						"bmps\\Buttons\\TopBot.bmp",
						"bmps\\Buttons\\LeftRt.bmp",
						"bmps\\Buttons\\Edge.bmp",
						"bmps\\Buttons\\OddEven.bmp",
						"bmps\\Buttons\\Ud190.bmp",
						"bmps\\Buttons\\Box190.bmp",
						"bmps\\Buttons\\HorizRow.bmp",
						"bmps\\Buttons\\VertRow.bmp",
						"bmps\\Buttons\\Way2.bmp",
						"bmps\\Buttons\\Way3.bmp",
						"bmps\\Buttons\\Way4.bmp",
						"bmps\\Buttons\\Way5.bmp",
						"bmps\\Buttons\\Way6.bmp",
						"bmps\\Buttons\\Way7.bmp",
						"bmps\\Buttons\\Way8.bmp",
						"bmps\\Buttons\\Way9.bmp",
						"bmps\\Buttons\\Way10.bmp",
						"bmps\\Buttons\\Way20.bmp",
						"bmps\\Buttons\\Groupit.bmp" };

char *image[] = {	"bmps\\Playscrn\\iTopBot.bmp",
					"bmps\\Playscrn\\iLeftRt.bmp",
					"bmps\\Playscrn\\iEdge.bmp",
					"bmps\\Playscrn\\iOddEven.bmp" };

char *rSideMsg = "bmps\\playscrn\\toucktkt.bmp";
char *rSideMsgFrame = "bmps\\playscrn\\window1.bmp";
char *Frame162x141Path = "bmps\\playscrn\\window2.bmp";
char *Frame164x324Path = "bmps\\playscrn\\window3.bmp";
char *Frame164x424Path = "bmps\\playscrn\\window4.bmp";
char *Frame204x424Path = "bmps\\playscrn\\window5.bmp";

/* Zebs added bmps */
//char *pszPayTable1 = "bmps\\Paytable\\Paytbl1.bmp";
//char *pszPayTable1 = "bmps\\Paytable\\Paytbl3.bmp";
char *pszPayTable1 = "bmps\\Paytable\\Paytbl4.bmp";
char *pszPayTable2 = "bmps\\Paytable\\Paytbl2.bmp";

char *messages[] = { "WELCOME TO ELITE KENO        ADD CREDITS TO PLAY",
					 "WELCOME TO ELITE KENO    TOUCH A TICKET TO BEGIN",
					 "                      GAME CLOSED                       ",
					 "TOUCH \"CLEAR\" TO CHANGE OR ADD A TICKET, OR PRESS \"RUN GAME\" TO DRAW NUMBERS.",
                     "                   NOT ENOUGH CREDITS                   ",
					 "TOUCH ONE OR MORE ROWS AND TOUCH \"PLAY IT\" TO ACTIVATE THE TICKET, OR TOUCH THE ROW AGAIN TO REMOVE IT.",
					 "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
                     "              NUMBER OF SPOTS IS NOT VALID              ",
                     "                  NO MORE SPOTS ALLOWED                 ",
                     "CHOOSE YOUR NUMBERS IN THE FIRST GROUP, AND THEN PRESS \"GROUP IT\".",
                     "TOUCH MORE NUMBERS FOR MORE GROUPS AND PRESS \"GROUP IT\", REMOVE GROUPS BY TOUCHING GROUPS FLASHING, OR PRESS \"PLAY IT\" TO ACTIVATE THE TICKET.",
                     "              YOU MUST INSERT MONEY TO PLAY             ",
					 "   A.G.T., INC. & KENO PRODUCTS GROUP   VERSION 1.2    ",
					 "CHOOSE FROM 2 TO 10 NUMBERS, A 20 SPOT SPECIAL, OR SELECT ANOTHER OPTION.",
					 "CHOOSE FROM 2 TO 10 NUMBERS, OR A 20 SPOT SPECIAL SHOWN ON YOUR RIGHT. THE COMPUTER WILL GENERATE YOUR NUMBERS.",
					 "PLEASE CHOOSE ONE OF THE SPECIAL TICKETS.",
					 "TOUCH ANY HOUSE TICKET TYPE, 190 WAY 8 OR ROWS.",
					 "AFTER YOU CHOOSE YOUR NUMBERS, PRESS NUMBER AGAIN TO DELETE, OR PRESS \"PLAY IT\" TO ACTIVATE YOUR TICKET, OR PRESS \"CANCEL\" TO MAKE ANOTHER CHOICE.",
					 "PRESS \"PLAY IT\" TO ACTIVATE YOUR TICKET, OR PRESS \"CANCEL\" TO CANCEL YOUR PLAY.",
					 "TOUCH \"PLAY IT\" TO ACTIVATE THE SPECIAL TICKET OR TOUCH \"CANCEL\" TO MAKE ANOTHER CHOICE.",
					 "CHANGE BET, PRESS \"PLAY IT\", OR CHOOSE ANOTHER HOUSE TICKET.",
					 "TOUCH ANOTHER BLANK TICKET, AN EXISTING TICKET TO CHANGE OR CANCEL, OR, \"RUN GAME\" TO DRAW NUMBERS.",
					 "TOUCH ANY TICKET TO CHANGE OR CANCEL, OR TOUCH \"RUN GAME\" TO DRAW NUMBERS.",
					 "         1         2         3         4         5      ",
					 "12345678901234567890123456789012345678901234567890123456"};

char *bigtkthdr[]= { "SELECT TICKET",
					 "QUICK PICK",
                     "SPECIALS",
                     "TOP AND BOTTOM",
                     "LEFT AND RIGHT",
                     "EDGE",
                     "ODD AND EVEN",
                     "HOUSE TICKET",
                     "190 WAY 8",
                     "HORIZONTAL",
                     "VERTICAL",
                     "WAY TICKET" };
int tktways[4] = { 0,0,0,0 };
int tktrate[4] = { 0,0,0,0 };
int tktcombo[4]= { 0,0,0,0 };
int tktcatch[8]= { 0,0,0,0,0,0,0,0 };	// last 4 used for secondary catch (top/bot,left/right)
char SpecWay[4][11];					// english special tickets

struct SPECIAL_TABLE_STRUCT	spcltbl[5];
struct RATE_TABLE_STRUCT tbl;
int POWlines=0;
int POWpages=0;
int POWpage=0;
int POWbtn=0;		// MORE or BACK or both visible
int POWTkt = -1;
int POWBigDraw = 0;
int newhit,newway,taddcnt,addcnt;
int SeqDraw[80];
int xPos;								// x coordinate of the mouse position
int yPos;								// y coordinate of the mouse position
static int nState = sIDLE;				// Set the default mode for the game
static int nHelpState = sIDLE;			// Used to determine help screen
static int nPayTableState = sIDLE;	// Used to determine pay table screen
static int AT = 0;						// Set active ticket to 0 for start up
struct GAME_STATE_STRUCT	st;
struct WAY_COMBO_STRUCT		wcs;
long dfltbetbtns[4] = { 5,25,100,500 };	// 4 button bets
static long dfltbet = 100;
static long lastbet = 0;
static unsigned long rnum[2];// single 64 bit number
unsigned long btick=0;
int	WaysToPlay[4][11];
unsigned int	AffectedCombos[21];
bool init103 = FALSE, Yahoo = FALSE;
long tvalue = 0, wtvalue = 0, wins = 0;
DWORD tick;
CSurface *STHdr[4];

/* Animation information */
CRITICAL_SECTION cs;
SCROLLING_CONTROL_STRUCT sinfo;

BOOL bFlag = FALSE;
BOOL bBlinkNbrs = FALSE;
BOOL bDelAffectedWays = TRUE;
DWORD dwBlinkNbrs = 0;
int nMsgScrollPos = 0;
DWORD dwMsgScrollDelay = 0;
DWORD nSpotsMax = 0;
DWORD dwInsertMoneyMsg = 0;
DWORD dwMoreCreditsMsg = 0;
DWORD dwInvalidSpotsMsg = 0;

RECT from;
RECT to;

HWND g_hWnd;

//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------

LRESULT CALLBACK MainWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK ExitDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

HRESULT WinInit( HINSTANCE hInst, int nCmdShow, HWND* phWnd, HACCEL* phAccel );
HRESULT InitDirectDraw( HWND hWnd );
VOID    FreeDirectDraw();
HRESULT ProcessNextFrame();
VOID    UpdateSprite( SPRITE_STRUCT* pSprite, FLOAT fTimeDelta );
HRESULT DisplayFrame();
HRESULT RestoreSurfaces();
BOOL    LoadAllGraphics();
HBITMAP GetBitmapFromFile(TCHAR* strBMP);
int		ActiveTickets();
HRESULT ProcessNumericTouch(long num, int nState);
BOOL	SelectButton(HBITMAP Button, int cXpos, int cYpos);
void	CalcQP(int qp);
int		get_ball(void);
void	RecalcGroups(int grps);
void	CalcWayTkt(void);
long	ComputeWayTkt(int tk,bool payit);
bool	LoadPayTables(void);
long	PayTable(int way,int rate,int caught,long bet);
int		GetGroupNum(int tkt);
int		CalcHoriz(int spot,int *grpletr);
int		CalcVert(int spot,int *grpletr);
void	CalcPlayWay(int way);
int		GetGroupItemNum(int tkt, int grp);
void	ProcExplodeTkt(int tkt);
bool	CalcDraw(void);
DWORD	cycle_r64(void);
DWORD	RND(void);
char*	CalcDecimal(char comma,char len,char dec_pos,long value);
long	CalcWinningTkts(void);
long	CalcWinTkt(int t,bool showit);
int		ComputeSpecial(int drawnbr,int type);
void	ReCalcBetMeter(void);
extern HRESULT DrawPOW(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info,
					  HBITMAP hBMPBlankPOW, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, int t, DWORD xPos, DWORD yPos);
extern void DrawCatch(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, 
					  HBITMAP hBMPBlankPOW, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, int t, DWORD xpos);
void		ProcBet(int b);
HRESULT DoScrollingWork(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, DWORD yPos );
unsigned int CalcPixLength(char* string);
BOOL WriteABuffer(HANDLE hComm, char * lpBuf, DWORD dwToWrite);
void PlayFileInit(void);
void AnimationThread(void*);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything and calls
//       UpdateFrame() when idle from the message pump.
//-----------------------------------------------------------------------------

int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow )
{
	int w, w2, way = 2;
    MSG	   msg;
    HWND   hWnd;
    HACCEL hAccel;
	unsigned short count = 0;
	unsigned long ticks = GetTickCount();
	char buf[256];

    ZeroMemory( &g_Sprite, sizeof(SPRITE_STRUCT) * NUM_SPRITES );
	ZeroMemory( &sinfo,sizeof(sinfo));
    srand( GetTickCount() );

	LoadPayTables();

    if( FAILED( WinInit( hInst, nCmdShow, &hWnd, &hAccel ) ) )
        return FALSE;

    if( FAILED( InitDirectDraw( hWnd ) ) )
    {
        MessageBox( hWnd, TEXT("DirectDraw init failed. ")
                    TEXT("The slot program will now exit. "), TEXT("Elite Keno Slot"), 
                    MB_ICONERROR | MB_OK );
        return FALSE;
    }

	gs->SetHWnd(hWnd);
	g_hWnd = hWnd;
	RND();

	CoInitialize(NULL);
	PlayFileInit();

	/* Set initial state to attract mode */
	PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDF_KEY_F10, 0), 0);

	//ShowCursor( false );
    g_dwLastTick = timeGetTime();

	for (w2 = 0; w2 < 4; w2++)
	{
		way = 2;

		for(w=0;w<9;w++)
			WaysToPlay[w2][w]=way++;
		WaysToPlay[w2][w]=20;
	}

	LoadPayTables();

    while( TRUE )
    {
        // Look for messages, if none are found then 
        // update the state and display it
        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( 0 == GetMessage(&msg, NULL, 0, 0 ) )
            {
                // WM_QUIT was posted, so exit
                return (int)msg.wParam;
            }

            // Translate and dispatch the message. If a dialog is showing, 
            // translate messages for it since they are modeless dialog.
            if( g_hWndDlg == NULL || !IsDialogMessage( g_hWndDlg, &msg ) )
            {
                if( 0 == TranslateAccelerator( hWnd, hAccel, &msg ) )
                {
                    TranslateMessage( &msg ); 
                    DispatchMessage( &msg );
                }
            }
        }
        else
        {
            if( g_bActive )
            {
                // Move the sprites, blt them to the back buffer, then 
                // flip or blt the back buffer to the primary buffer

                if( FAILED( ProcessNextFrame() ) )
                {
                    SAFE_DELETE( g_pDisplay );

                    MessageBox( hWnd, TEXT("Frame processing error, the subsequent frame failed. ")
                                TEXT("The Elite Keno Slot System will now restart. "), TEXT("Elite Keno Slot"), 
                                MB_ICONERROR | MB_OK );
            	    PostMessage( HWND_BROADCAST, WM_CLOSE, 0, 0 );
                    return FALSE;
                }
				else
				{
					if (GetTickCount() - 1000 > ticks)
					{
                        //sprintf(buf,"%d calls to ProcessNextFrame() in 1s.\r\n",count);
						//OutputDebugString(buf);
						count = 0; ticks = GetTickCount();
					}
					else
						count++;
				}
            }
            else
            {
                // Make sure we go to sleep if we have nothing else to do
                WaitMessage();

                // Ignore time spent inactive 
                g_dwLastTick = timeGetTime();
            }
        }
    }
}

//-----------------------------------------------------------------------------
// Name: WinInit()
// Desc: Init the window
//-----------------------------------------------------------------------------

HRESULT WinInit( HINSTANCE hInst, int nCmdShow, HWND* phWnd, HACCEL* phAccel )
{
    WNDCLASS wc;
    HWND     hWnd;
    HACCEL   hAccel;

	if( !LoadAllGraphics() )
		return E_FAIL;

    // Register the Window Class
    wc.lpszClassName = TEXT("EliteKenoSlot");
    wc.lpfnWndProc   = MainWndProc;
    wc.style         = CS_VREDRAW | CS_HREDRAW;
    wc.hInstance     = hInst;
    wc.hIcon         = LoadIcon( hInst, MAKEINTRESOURCE(IDI_MAIN) );
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;

    if( RegisterClass( &wc ) == 0 )
        return E_FAIL;

    // Load keyboard accelerators
    hAccel = LoadAccelerators( hInst, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

    // Create and show the main window
    hWnd = CreateWindowEx( 0, TEXT("EliteKenoSlot"), TEXT("Elite Keno Slot Machine"),
                           WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT,
  	                       CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL );
    if( hWnd == NULL )
    	return E_FAIL;

    ShowWindow( hWnd, nCmdShow );
    UpdateWindow( hWnd );

    *phWnd   = hWnd;
    *phAccel = hAccel;

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: InitDirectDraw()
// Desc: Create the DirectDraw object, and init the surfaces
//-----------------------------------------------------------------------------

HRESULT InitDirectDraw( HWND hWnd )
{
    HRESULT             hr;

    g_pDisplay = new CDisplay();
	gs = new CGameState();

	CalcWinningTkts();

	ComputeWayTkt(1,true);
	ComputeWayTkt(0,true);

	//if( FAILED( hr = g_pDisplay->CreateWindowedDisplay(hWnd, 800 , 600)))
		
	if( FAILED( hr = g_pDisplay->CreateFullScreenDisplay( hWnd, SCREEN_WIDTH, 
                                                          SCREEN_HEIGHT, SCREEN_BPP ) ) )
    {
        MessageBox( hWnd, TEXT("This display card does not support 640x480x16. "),
                    TEXT("Elite Keno Slot"), MB_ICONERROR | MB_OK );
        return hr;
    }
	
    // Check if the device supports DDCAPS2_CANRENDERWINDOWED.  
    // If it does, then it supports GDI writing directly to the primary surface
    // Otherwise, to do GDI displaying on these cards, you you must create a 
    // bitmap of the GDI window and BitBlt the bitmap to the backbuffer 
    // then flip as normal. However, this application does not do this at present. 
    DDCAPS ddcaps;
    ZeroMemory( &ddcaps, sizeof(ddcaps) );
    ddcaps.dwSize = sizeof(ddcaps);
    g_pDisplay->GetDirectDraw()->GetCaps( &ddcaps, NULL );
    if( (ddcaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED) == 0 )
    {
        MessageBox( hWnd, TEXT("This display card can not render GDI."),
                    TEXT("Elite Keno Slot"), MB_ICONERROR | MB_OK );
        return E_FAIL;
    }

    // Create a clipper so DirectDraw will not blt over the GDI dialog
    if( FAILED( hr = g_pDisplay->InitClipper() ) )
        return hr;

    // Create a surfaces, and draw or don't draw a bitmap resource on it.  
    if( FAILED( hr = g_pDisplay->CreateSurfaceFromBitmap( &g_pEKBaseSurface, EKBkgrnd, SCREEN_WIDTH, SCREEN_HEIGHT ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKLogoSurface, 156, 79 ) ) )
        return hr;
	else
		g_pEKLogoSurface->DrawBitmap(EKLogo,0,0,156,79);

    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKBTBaseSurface, 442, 402 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKBTHdrSurface, 435, 45 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKBTSpotSurface, 40, 40 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKSTBaseSurface, 204, 186 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKSTHdr1Surface, 200, 18 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKSTHdr2Surface, 200, 18 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKSTHdr3Surface, 200, 18 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKSTHdr4Surface, 200, 18 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKSTSpotSurface, 18, 18 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKGameStatSurface, 156, 22 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKOrLabelSurface, 29, 20 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKChgBetSurface, 96, 19 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKMsgCtrSurface, 418, 25 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurfaceFromText( &g_pTextSurface, NULL, messages[0], RGB(0,0,0), RGB(255, 255, 0) ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKFrame1Surface, 162, 65 ) ) )
        return hr;
	else
		g_pEKFrame1Surface->DrawBitmap(Frame162x65,0,0,162,65);

    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKFrame2Surface, 162, 141 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKFrame3Surface, 164, 324 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKFrame4Surface, 164, 424 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKFrame5Surface, 204, 424 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKRMsgSurface, 145, 57 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKBetMtrSurface, 116, 28 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKWonMtrSurface, 136, 28 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKCreditSurface, 152, 28 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKButtonSurface, 73, 42 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKCashOutSurface, 51, 42 ) ) )
        return hr;
    if( FAILED( hr = g_pDisplay->CreateSurface( &g_pEKTchOneSurface, 143, 19 ) ) )
        return hr;
	/* Create Zebs surfaces */
	if (FAILED(hr = g_pDisplay->CreateSurface(&g_pEKPayScreenSurface,604,405)))
		return hr;
	if (FAILED(hr = g_pDisplay->CreateSurface(&g_pEKTktTypeSurface,59,48)))
		return hr;
	if (FAILED(hr = g_pDisplay->CreateSurface(&g_pEKWayBoxSurface, 41, 13 ) ) )
		return hr;
	if (FAILED(hr = g_pDisplay->CreateSurface(&g_pEKHelpBGSurface, 630, 436 ) ) )
		return hr;
	if (FAILED(hr = g_pDisplay->CreateSurface(&g_pEKSTOvalSurface, 58, 16 ) ) )
		return hr;
	if (FAILED(hr = g_pDisplay->CreateSurface(&g_pEKBlowerSurface, 155, 400 ) ) )
		return hr;
	if (FAILED(hr = g_pDisplay->CreateSurface(&g_pEKBigClearSurface, 164, 42 ) ) )
		return hr;

	STHdr[0] = g_pEKSTHdr1Surface; STHdr[0]->DrawBitmap(TktHdrs[0],0,0,200,18);
	STHdr[1] = g_pEKSTHdr2Surface; STHdr[1]->DrawBitmap(TktHdrs[1],0,0,200,18);
	STHdr[2] = g_pEKSTHdr3Surface; STHdr[2]->DrawBitmap(TktHdrs[2],0,0,200,18);
	STHdr[3] = g_pEKSTHdr4Surface; STHdr[3]->DrawBitmap(TktHdrs[3],0,0,200,18);

	/* Enable Sprites */
	if( FAILED( hr = g_pDisplay->CreateSurfaceFromBitmap( &g_pDXLogoSurface, MAKEINTRESOURCE( IDB_DIRECTX ), 
                                                          SPRITE_DIAMETER, SPRITE_DIAMETER ) ) )
        return hr;

    // Set the color key for the DirectX logo sprite to black
    if( FAILED( hr = g_pDXLogoSurface->SetColorKey( 0 ) ) )
        return hr;

    // Init all the sprites.  All of these sprites look the same, 
    // using the g_pDXLogoSurface. 
    for( int iSprite = 0; iSprite < NUM_SPRITES; iSprite++ )
    {
        // Set the sprite's position and velocity
        g_Sprite[iSprite].fPosX = (float) (rand() % SCREEN_WIDTH);
        g_Sprite[iSprite].fPosY = (float) (rand() % SCREEN_HEIGHT); 

        g_Sprite[iSprite].fVelX = 500.0f * rand() / RAND_MAX - 250.0f;
        g_Sprite[iSprite].fVelY = 500.0f * rand() / RAND_MAX - 250.0f;
    }

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: FreeDirectDraw()
// Desc: Release all the DirectDraw objects
//-----------------------------------------------------------------------------
VOID FreeDirectDraw()
{
    SAFE_DELETE( g_pDXLogoSurface		);
	SAFE_DELETE( g_pEKBaseSurface		);
	SAFE_DELETE( g_pEKLogoSurface		);
	SAFE_DELETE( g_pEKBTBaseSurface		);
	SAFE_DELETE( g_pEKBTHdrSurface		);
	SAFE_DELETE( g_pEKBTSpotSurface		);
	SAFE_DELETE( g_pEKSTBaseSurface		);
	SAFE_DELETE( g_pEKSTHdr1Surface		);
	SAFE_DELETE( g_pEKSTHdr2Surface		);
	SAFE_DELETE( g_pEKSTHdr3Surface		);
	SAFE_DELETE( g_pEKSTHdr4Surface		);
	SAFE_DELETE( g_pEKSTSpotSurface		);
	SAFE_DELETE( g_pEKGameStatSurface	);
	SAFE_DELETE( g_pEKOrLabelSurface    );
	SAFE_DELETE( g_pEKMsgCtrSurface		);
    SAFE_DELETE( g_pTextSurface			);
	SAFE_DELETE( g_pEKFrame1Surface     );
	SAFE_DELETE( g_pEKFrame2Surface     );
	SAFE_DELETE( g_pEKFrame3Surface     );
	SAFE_DELETE( g_pEKFrame4Surface     );
	SAFE_DELETE( g_pEKFrame5Surface     );
	SAFE_DELETE( g_pEKRMsgSurface       );
	SAFE_DELETE( g_pEKBetMtrSurface		);
	SAFE_DELETE( g_pEKWonMtrSurface		);
	SAFE_DELETE( g_pEKCreditSurface		);
	SAFE_DELETE( g_pEKButtonSurface		);
	SAFE_DELETE( g_pEKCashOutSurface	);
    SAFE_DELETE( g_pDisplay				);
	SAFE_DELETE( g_pEKTchOneSurface     );
	SAFE_DELETE( g_pEKChgBetSurface     );
	/* Clear Zebs surfaces */
	SAFE_DELETE( g_pEKPayScreenSurface	);
	SAFE_DELETE( g_pEKTktTypeSurface	);
	SAFE_DELETE( g_pEKWayBoxSurface		);
	SAFE_DELETE( g_pEKHelpBGSurface		);
	SAFE_DELETE( g_pEKSTOvalSurface		);
	SAFE_DELETE( g_pEKBlowerSurface		);
	SAFE_DELETE( g_pEKBigClearSurface	);
}

//-----------------------------------------------------------------------------
// Name: MainWndProc()
// Desc: The main window procedure
//-----------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    static HRESULT hr;
	int    CT=0;
	switch (msg)
    {
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
				case IDF_KEY_C:
				{
					CT = gs->GetActiveTicket(); CT--;

					// Cancel Button was pressed so process the button click
					sndPlaySound("sounds\\btnclick.wav",SND_ASYNC);
					// Based upon the current mode the cancel button position will be determined

					if (nState == sPOW)
					/* Clear button pressed in Proof-of-Win */
					{
						int i;

						POWtkt = -1;

						gs->m_pGS.won = 0;

						for (i = 0; i < 4; i++)
							gs->m_pGS.credits -= gs->m_pGS.tkt[i].price;

						if (gs->m_pGS.credits < 0)
						/* Not enough credits for next game, delete all tickets */
						{
							for (i = 0; i < 4; i++)
							{
								gs->m_pGS.credits += gs->m_pGS.tkt[i].price;
								memset(&gs->m_pGS.tkt[i],0,sizeof(gs->m_pGS.tkt[i]));
							}
						}
						
						PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDM_MODE_IDLE, HIWORD(wParam)), lParam);
					}
					/* Cancel button pressed */
					else
					{
						if (nState == sWAYTKT || nState == sWAYENTRY || nState == sWAYPLAYIT)
						{
                            gs->m_pGS.credits += wtvalue; tvalue = 0; wtvalue = 0;
						}
						else
						{
							gs->m_pGS.credits += tvalue; tvalue = 0;
						}

						if(nState == sSTRAIGHT)
						{
							SelectButton(EKBtn[7],504,190);
						}
						else if(nState == sBIGTKTUP)
						{
							SelectButton(EKBtn[7],504,374);
						}
						else if (nState == sQUICKPICK || nState == sSPECIALS || nState == sHOUSETKT || nState == sHSENTRY || nState == sVTENTRY || nState == sHZENTRY || nState == sWAYTKT || nState == sWAYENTRY || nState == sWAYPLAYIT)
						{
							SelectButton(EKBtn[7],544,266);
						}

						memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					}
					PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDM_MODE_IDLE, HIWORD(wParam)), lParam);
					break;
				}
					
				case IDF_KEY_P:
					// Play It Button was pressed so process the button click
					CT = gs->GetActiveTicket(); CT--;

					if (nState != sWAYENTRY && nState != sWAYTKT)
					{

						if (gs->m_pGS.credits < gs->m_pGS.tkt[CT].price)
						{
							sndPlaySound("sounds\\horn.wav",SND_ASYNC);
							dwMoreCreditsMsg = GetTickCount();
							break;
						}
						else
						{
							gs->m_pGS.credits += tvalue; tvalue = 0;
							gs->m_pGS.credits -= gs->m_pGS.tkt[CT].price;
						}
					}

					if (nState == sSTRAIGHT)
					{
						SelectButton(EKBtn[8],504,255);

						if (gs->m_pGS.tkt[CT].picked <= 1 || (gs->m_pGS.tkt[CT].picked > 10 && gs->m_pGS.tkt[CT].picked < 20) )
						/* Invalid # of spots */
						{
							sndPlaySound("sounds\\horn.wav",SND_ASYNC);
							dwInvalidSpotsMsg = GetTickCount();
							break;
						}
					}
					else if (nState == sQUICKPICK || nState == sHSENTRY || nState == sVTENTRY || nState == sHZENTRY)
					{
						if (nState == sVTENTRY || nState == sHZENTRY)
						{
							CalcWayTkt();
						}

						SelectButton(EKBtn[8],466,266);

					}
					else if (nState == sWAYENTRY)
					/* Group it button */
					{
						char buf[256];

						SelectButton(EKBtn[45],466,266);

						if (gs->m_pGS.tkt[CT].picked == 0)
						/* Invalid # of spots */
						{
							sndPlaySound("sounds\\horn.wav",SND_ASYNC);
							dwInvalidSpotsMsg = GetTickCount();
							break;
						}

						gs->m_pGS.tkt[CT].grpcount = GetGroupNum(CT);


						/* Blink the numbers in the initial drawing phase */
						bBlinkNbrs = TRUE;

						CalcWayTkt();
						PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDM_MODE_WAYPLAYIT, HIWORD(wParam)), lParam);
						break;
					}
					else if (nState == sWAYPLAYIT)
					{
						char bbuf[256];
						SelectButton(EKBtn[8],466,266);
						CalcWayTkt();
					}
					else if (nState == sWAYTKT)
						break;
					else if (nState == sSPECIALS)
					{
						if (gs->m_pGS.tkt[CT].rate == 0)
						/* Play it pressed without a special being picked */
							break;
						else
							SelectButton(EKBtn[8],466,266);
					}
					else if (nState == sHOUSETKT)
						break;

					gs->UpdateGameState();
					PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDM_MODE_IDLE, HIWORD(wParam)), lParam);
					break;

				case IDF_KEY_Y:
					// Pay table 1 activated
					SelectButton(EKBtn[1],466,436);
					nPayTableState = nState;
					PostMessage(hWnd,WM_COMMAND,MAKEWPARAM(IDM_MODE_PAYTABLE1,HIWORD(wParam)),lParam);
				break;

				case IDF_KEY_G:
					// Back to game
					SelectButton(EKBtn[24],466,436);
					if (nState == sHELPSCRN)
					/* Back to previous state */
						nState = nHelpState;
					else if (nState == sPAYTABLE1 || nState == sPAYTABLE2)
					{
						nState = nPayTableState;
					}
					else
						PostMessage(hWnd,WM_COMMAND,MAKEWPARAM(IDM_MODE_IDLE,HIWORD(wParam)),lParam);
				break;

				case IDF_KEY_M:
					// More button, to pay table 2
					if (nState == sPOW && (POWlines > 0 && POWpages > 0 && POWpage < POWpages - 1))
					{
						int x;

						if (POWtkt == 1 || POWtkt == 3)
							x = 45;
						else
							x = 259;
						SelectButton(EKBtn[25],  x, 350); // More
						POWpage++;
					}
					else if (nState != sPOW)
					{
						SelectButton(EKBtn[25],544,436);
						gs->UpdateGameState();
						PostMessage(hWnd,WM_COMMAND,MAKEWPARAM(IDM_MODE_PAYTABLE2,HIWORD(wParam)),lParam);
					}
				break;
				case IDF_KEY_B:
					// Back to pay table 1
					if (nState == sPOW && (POWlines > 0 && POWpages > 1 && POWpage != 0))
					{
						int x;

						if (POWtkt == 1 || POWtkt == 3)
							x = 120;
						else
							x = 334;

						SelectButton(EKBtn[26],  x, 350); // Back
						POWpage--;
					}
					else if (nState != sPOW)
					{
						SelectButton(EKBtn[26],544,436);
						gs->UpdateGameState();
						PostMessage(hWnd,WM_COMMAND,MAKEWPARAM(IDM_MODE_PAYTABLE1,HIWORD(wParam)),lParam);
					}
				break;
				case IDF_KEY_T:
				/* Top to bottom */
				{
					CT = gs->GetActiveTicket(); CT--;

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					SelectButton(EKBtn[27],466,40);
					gs->m_pGS.tkt[CT].rate = 1;
					gs->m_pGS.tkt[CT].type = tTOPBOT;
					gs->m_pGS.tkt[CT].bet = lastbet;
					gs->m_pGS.tkt[CT].price = lastbet;
					gs->m_pGS.tkt[CT].combo = 1;
				}
				break;
				case IDF_KEY_L:
				/* Left to right */
				{
					CT = gs->GetActiveTicket(); CT--;

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					SelectButton(EKBtn[28],466,95);
					gs->m_pGS.tkt[CT].rate = 2;
					gs->m_pGS.tkt[CT].type = tLEFTRT;
					gs->m_pGS.tkt[CT].bet = lastbet;
					gs->m_pGS.tkt[CT].price = lastbet;
					gs->m_pGS.tkt[CT].combo = 1;
				}
				break;
				case IDF_KEY_E:
				/* Edges */
				{
					CT = gs->GetActiveTicket(); CT--;

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					SelectButton(EKBtn[29],466,150);
					gs->m_pGS.tkt[CT].rate = 3;
					gs->m_pGS.tkt[CT].type = tEDGE;
					gs->m_pGS.tkt[CT].bet = lastbet;
					gs->m_pGS.tkt[CT].price = lastbet;
					gs->m_pGS.tkt[CT].combo = 1;
				}
				break;
				case IDF_KEY_O:
				/* Odds & Evens */
				{
					CT = gs->GetActiveTicket(); CT--;

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					SelectButton(EKBtn[30],466,205);
					gs->m_pGS.tkt[CT].rate = 4;
					gs->m_pGS.tkt[CT].type = tODDEVEN;
					gs->m_pGS.tkt[CT].bet = lastbet;
					gs->m_pGS.tkt[CT].price = lastbet;
					gs->m_pGS.tkt[CT].combo = 1;
				}
				break;
				case IDF_KEY_U:
				/* 190 Up/Down */
				{
					int g, s, index = 0, spot = 1;
					int Nbrs[] = { 1,11,21,31,2,12,22,32,3,13,23,33,4,14,24,34,5,15,25,35,6,16,26,36,7,17,27,37,8,18,28,38,9,19,29,39,10,20,30,40,
					41,51,61,71,42,52,62,72,43,53,63,73,44,54,64,74,45,55,65,75,46,56,66,76,47,57,67,77,48,58,68,78,49,59,69,79,50,60,70,80 };
					CT = gs->GetActiveTicket(); CT--;

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					SelectButton(EKBtn[31],466,165);

					/* Set current bet to $.05 */
					dfltbet = 5;
					lastbet = dfltbet;

					/* Set state and begin work on ticket */
					nState = sHSENTRY;

					memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					gs->m_pGS.tkt[CT].grpcount = 20;
					gs->m_pGS.tkt[CT].rate = 0;
					gs->m_pGS.tkt[CT].picked = 8;
					gs->m_pGS.tkt[CT].ways[6] = 8;
					gs->m_pGS.tkt[CT].combo = 190;
					gs->m_pGS.tkt[CT].bet = 5;
					gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].combo;
					gs->m_pGS.tkt[CT].type = t190UD;

					for (g = 0; g < gs->m_pGS.tkt[CT].grpcount; g++)
					{
						for (s = 0; s < 4; s++, index++)
							gs->m_pGS.tkt[CT].groups[g][s] = Nbrs[index];
					}

					gs->UpdateGameState();
					break;
				}

				case IDF_KEY_X:
				{
				/* 190 Boxes */
					int g, s, index = 0;
					int Nbrs[]= { 1,2,11,12,3,4,13,14,5,6,15,16,7,8,17,18,9,10,19,20,21,22,31,32,23,24,33,34,25,26,35,36,27,28,37,38,29,30,39,40,
					41,42,51,52,43,44,53,54,45,46,55,56,47,48,57,58,49,50,59,60,61,62,71,72,63,64,73,74,65,66,75,76,67,68,77,78,69,70,79,80 };
					CT = gs->GetActiveTicket(); CT--;

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					SelectButton(EKBtn[32],544,165);

					/* Set current bet to $.05 */
					dfltbet = 5;
					lastbet = dfltbet;

					/* Set state and begin work on ticket */
					nState = sHSENTRY;

					memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					gs->m_pGS.tkt[CT].grpcount = 20;
					gs->m_pGS.tkt[CT].rate = 0;
					gs->m_pGS.tkt[CT].picked = 8;
					gs->m_pGS.tkt[CT].ways[6] = 8;
					gs->m_pGS.tkt[CT].combo = 190;
					gs->m_pGS.tkt[CT].bet = 5;
					gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].combo;
					gs->m_pGS.tkt[CT].type = t190BOX;

					for (g = 0; g < gs->m_pGS.tkt[CT].grpcount; g++)
					{
						for (s = 0; s < 4; s++, index++)
							gs->m_pGS.tkt[CT].groups[g][s] = Nbrs[index];
					}
					gs->UpdateGameState();
					break;
				}

				case IDF_KEY_Z:
				/* Horizontal Rows */
					CT = gs->GetActiveTicket(); CT--;
					SelectButton(EKBtn[33],466,211);

					/* Set current bet to $1.00 */
					dfltbet = 100;
					lastbet = dfltbet;

					/* Set state and begin work on ticket */
					nState = sHSENTRY;

					memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					gs->m_pGS.tkt[CT].grpcount = 0;
					gs->m_pGS.tkt[CT].rate = 0;
					gs->m_pGS.tkt[CT].picked = 10;
					gs->m_pGS.tkt[CT].combo = 0;
					gs->m_pGS.tkt[CT].bet = dfltbet;
					gs->m_pGS.tkt[CT].price = dfltbet;
					gs->m_pGS.tkt[CT].type = tHZROW;

					gs->UpdateGameState();
					PostMessage(hWnd,WM_COMMAND,MAKEWPARAM(IDM_MODE_HZENTRY,HIWORD(wParam)),lParam);
				break;
                
				case IDF_KEY_V:
				/* Vertical Rows */
					CT = gs->GetActiveTicket(); CT--;
					SelectButton(EKBtn[34],544,211);

					/* Set current bet to $1.00 */
					dfltbet = 100;
					lastbet = dfltbet;

					/* Set state and begin work on ticket */
					nState = sHSENTRY;

					memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					gs->m_pGS.tkt[CT].grpcount = 0;
					gs->m_pGS.tkt[CT].rate = 0;
					gs->m_pGS.tkt[CT].picked = 8;
					gs->m_pGS.tkt[CT].combo = 0;
					gs->m_pGS.tkt[CT].bet = dfltbet;
					gs->m_pGS.tkt[CT].price = dfltbet;

					gs->m_pGS.tkt[CT].type = tVTROW;

					gs->UpdateGameState();
					PostMessage(hWnd,WM_COMMAND,MAKEWPARAM(IDM_MODE_VTENTRY,HIWORD(wParam)),lParam);
				break;

				case IDF_KEY_R:
				/* "Run Game" button selected */
				{
					if (nState == sPOW)
					{
						SelectButton(EKBtn[23],465,4);

						if (gs->m_pGS.played > gs->m_pGS.credits)
						/* Not enough credits */
						{
							sndPlaySound("sounds\\horn.wav",SND_ASYNC);
							dwMoreCreditsMsg = GetTickCount();
							break;
						}
						else
						{
                            gs->m_pGS.credits -= gs->m_pGS.played;

							ReCalcBetMeter();
							gs->m_pGS.won = 0;

							if (CalcDraw())
								nState = 102;
						}
					}
					else
					{
						SelectButton(EKBtn[23],504,374);
						//DrawHiLiteEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[23], SHOW_HILITE, 504, 374);
						//btick=GetTickCount()+250;
						//while(btick>GetTickCount());// visual button click
						//DrawHiLiteEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[23], SHOW_NORMAL, 504, 374);
						PostMessage(hWnd,WM_COMMAND,MAKEWPARAM(IDM_MODE_RUNGAME,HIWORD(wParam)),lParam);
					}
				}
				break;
                case IDM_EXIT:
                    // Received key/menu command to exit app
					pMediaControl->Release();
					pVidWin->Release();
					pEvent->SetNotifyWindow(NULL, 0, 0);
					pGraph->Release();

					CoUninitialize();
            	    PostMessage( hWnd, WM_CLOSE, 0, 0 );
                    return 0L;
					break;

				case IDM_MODE_ATTRACT:
					// Change mode command to sIDLE
					nState = sATTRACT;
					break;

				case IDM_MODE_CASHOUT:
				/* Cash Out button clicked */
				{
					int t;

					sndPlaySound("sounds\\coinout.wav",SND_ASYNC);

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;

					DrawHiLiteCashOutButton(&g_pDisplay, g_pEKCashOutSurface, EKBtn[0], SHOW_HILITE, 513, 294);
					btick=GetTickCount()+250;
					while(btick>GetTickCount());// visual button click
					DrawHiLiteCashOutButton(&g_pDisplay, g_pEKCashOutSurface, EKBtn[0], SHOW_NORMAL, 513, 294);


					for (t = 0; t < 4; t++)
						memset(&gs->m_pGS.tkt[t],0,sizeof(gs->m_pGS.tkt[t]));
					gs->m_pGS.played = 0;
					gs->m_pGS.won = 0;
					gs->m_pGS.credits = 0;

					gs->UpdateGameState();
					
					break;
				}
				case IDM_MODE_DUMPBALLS:
					// Change mode command to sDUMPBALLS
					nState = sDUMPBALLS;
					break;

				case IDM_MODE_HELPSCREEN:
				// Change mode command to sHELPSCRN
				{
					SelectButton(EKBtn[2],544,436);
					nHelpState = nState;
					nState = sHELPSCRN;
					break;
				}

				case IDM_MODE_HOUSETICKET:
				{
					// House Ticket button was pressed so process the button click

					// Based upon the current mode the house ticket button position will be determined

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;

					if(nState == sBIGTKTUP)
						SelectButton(EKBtn[6],544,288);

					gs->UpdateGameState();

					// Change mode command to sHOUSETKT
					nState = sHOUSETKT;
					break;
				}

				case IDM_MODE_HSENTRY:
					// Change mode command to sHSENTRY
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					nState = sHSENTRY;
					break;

				case IDM_MODE_HZENTRY:
					// Change mode command to sHZENTRY
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					nState = sHZENTRY;
					break;

				case IDM_MODE_IDLE:
					// Change mode command to sIDLE
					ReCalcBetMeter();
					gs->UpdateGameState();
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					nState = sIDLE;
					break;

				case IDM_MODE_PAYTABLE1:
					// Change mode command to sPAYTABLE1
					gs->UpdateGameState();
					nState = sPAYTABLE1;
					break;

				case IDM_MODE_PAYTABLE2:
					// Change mode command to sPAYTABLE2
					nState = sPAYTABLE2;
					break;

				case IDM_MODE_PROOFWIN:
					// Change mode command to sPOW
					nState = sPOW;
					break;

				case IDM_MODE_QPENTRY:
				{
					// Change mode command to sQPENTRY
					nState = sQPENTRY;
					break;
				}

				case IDM_MODE_QUICKPICK:
				{
					int CT = gs->GetActiveTicket(); CT--;
					// Quick Pick button was pressed so process the button click

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					// Based upon the current mode the quick pick button position will be determined
					
					if(nState == sBIGTKTUP)
						SelectButton(EKBtn[3],466,238);

					dfltbet = 100;
					lastbet=dfltbet;	// start all new tickets at default bet ($1.00)

					memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					gs->m_pGS.tkt[CT].grpcount=1;
					gs->m_pGS.tkt[CT].rate=0;
					gs->m_pGS.tkt[CT].picked=0;
					gs->m_pGS.tkt[CT].combo=1;
					gs->m_pGS.tkt[CT].bet=dfltbet;
					gs->m_pGS.tkt[CT].price=dfltbet;

					gs->UpdateGameState();

					// Change mode command to sQUICKPICK
					nState = sQUICKPICK;
					break;
				}

				case IDM_MODE_RUNGAME:
				/* Time to run our tickets */
				{
					ReCalcBetMeter();

					gs->m_pGS.won = 0;
					//gs->m_pGS.credits -= gs->m_pGS.played;

					nState = 100;

					if (CalcDraw())
					{

						nState = 101;
					}

				}
				break;

				case IDM_MODE_SPECIALS:
				{
					CT = gs->GetActiveTicket(); CT--;
					// Specials button was pressed so process the button click
					
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;

					if(nState == sBIGTKTUP)
						SelectButton(EKBtn[5],466,288);

					/* Set current bet to $1.00 */
					dfltbet = 100;
					lastbet = dfltbet;

					memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					gs->m_pGS.tkt[CT].grpcount = 1;
					gs->m_pGS.tkt[CT].rate = 0;
					gs->m_pGS.tkt[CT].picked = 1;
					gs->m_pGS.tkt[CT].combo = 1;
					gs->m_pGS.tkt[CT].bet = 0;
					gs->m_pGS.tkt[CT].price = 0;

					gs->UpdateGameState();

					// Change mode command to sSPECIALS
					nState = sSPECIALS;
					break;
				}

				case IDM_MODE_SPENTRY:
					// Change mode command to sSPENTRY
					nState = sSPENTRY;
					break;

				case IDM_MODE_STRAIGHT:
					// Change mode command to sSTRAIGHT
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					nState = sSTRAIGHT;
					break;

				case IDM_MODE_VTENTRY:
					// Change mode command to sVTENTRY
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					nState = sVTENTRY;
					break;

				case IDM_MODE_WAYENTRY:
					// Change mode command to sWAYENTRY
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					nState = sWAYENTRY;
					break;

				case IDM_MODE_WAYPLAYIT:
					// Change mode command to sWAYPLAYIT
					nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					nState = sWAYPLAYIT;
					break;

				case IDM_MODE_WAYTICKET:
				{
					int way = 2, CT = gs->GetActiveTicket(); CT--;

					nMsgScrollPos = 0; dwMsgScrollDelay = 0;

					// Way Ticket button was pressed so process the button click
					sndPlaySound("sounds\\btnclick.wav",SND_ASYNC);
					// Based upon the current mode the way ticket button position will be determined

					/* Set current bet to $1.00 */
					dfltbet = 100;
					lastbet = dfltbet;

					if(nState == sBIGTKTUP)
						SelectButton(EKBtn[4],544,238);

					memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
					gs->m_pGS.tkt[CT].grpcount=1;
					gs->m_pGS.tkt[CT].rate=0;
					gs->m_pGS.tkt[CT].picked=0;
					gs->m_pGS.tkt[CT].combo=1;
					gs->m_pGS.tkt[CT].bet=dfltbet;
					gs->m_pGS.tkt[CT].price=dfltbet;
					gs->m_pGS.tkt[CT].type = tWAYTKT;

					gs->UpdateGameState();

					// Change mode command to sWAYTKT
					nState = sWAYTKT;
					break;
				}

				/* Quick pick buttons */
				case IDF_KEY_0:
				{
					SelectButton(EKBtn[17],466,216);
					CalcQP(10);
				}
				break;
				case IDF_KEY_1:
				{
					SelectButton(EKBtn[18],544,216);
					CalcQP(20);
				}
				break;
				case IDF_KEY_2:
				{
					SelectButton(EKBtn[9],466,32);
					CalcQP(2);
				}
				break;
				case IDF_KEY_3:
				{
					SelectButton(EKBtn[10],544,32);
					CalcQP(3);
				}
				break;
				case IDF_KEY_4:
				{
					SelectButton(EKBtn[11],466,78);
					CalcQP(4);
				}
				break;
				case IDF_KEY_5:
				{
					SelectButton(EKBtn[12],544,78);
					CalcQP(5);
				}
				break;
				case IDF_KEY_6:
				{
					SelectButton(EKBtn[13],466,124);
					CalcQP(6);
				}
				break;
				case IDF_KEY_7:
				{
					SelectButton(EKBtn[14],544,124);
					CalcQP(7);
				}
				break;
				case IDF_KEY_8:
				{
					SelectButton(EKBtn[15],466,170);
					CalcQP(8);
				}
				break;
				case IDF_KEY_9:
				{
					SelectButton(EKBtn[16],544,170);
					CalcQP(9);
				}
				break;

				/* 0 = 10 spot, 1 = 20 spot */
				case IDF_KEY_A0:
					SelectButton(EKBtn[43],466,216);
					CalcPlayWay(10);
					break;
				case IDF_KEY_A1:
					SelectButton(EKBtn[44],544,216);
					CalcPlayWay(20);
					break;
				case IDF_KEY_A2:
					SelectButton(EKBtn[35],466,32);
					CalcPlayWay(2);
					break;
				case IDF_KEY_A3:
					SelectButton(EKBtn[36],544,32);
					CalcPlayWay(3);
					break;
				case IDF_KEY_A4:
					SelectButton(EKBtn[37],466,78);
					CalcPlayWay(4);
					break;
				case IDF_KEY_A5:
					SelectButton(EKBtn[38],544,78);
					CalcPlayWay(5);
					break;
				case IDF_KEY_A6:
					SelectButton(EKBtn[39],466,124);
					CalcPlayWay(6);
					break;
				case IDF_KEY_A7:
					SelectButton(EKBtn[40],544,124);
					CalcPlayWay(7);
					break;
				case IDF_KEY_A8:
					SelectButton(EKBtn[41],466,170);
					CalcPlayWay(8);
					break;
				case IDF_KEY_A9:
					SelectButton(EKBtn[42],544,170);
					CalcPlayWay(9);
					break;

				case IDF_KEY_F1:	// Received key command to explode the big ticket.
					ProcExplodeTkt(0);
					break;

				case IDF_KEY_F2:
					ProcExplodeTkt(1);
					break;

				case IDF_KEY_F3:
					ProcExplodeTkt(2);
					break;

				case IDF_KEY_F4:
					ProcExplodeTkt(3);
					break;

				case IDF_KEY_F5:
				/* 5 cents clicked */
				{

					CT = gs->GetActiveTicket(); CT--;
					int type = gs->m_pGS.tkt[CT].type;
					//if (nState == sQUICKPICK)
					//{
					//	if (gs->m_pGS.tkt[CT].picked == 0)
					//		break;
					//	else
					//		SelectButton(EKBtn[19],466,332);
					//}
					//else
					//	SelectButton(EKBtn[19],466,332);

					if (type != tVTROW && type != tHZROW && type != t190BOX && type != t190UD)
					{
						if ((nState == sWAYPLAYIT || nState == sWAYENTRY || nState == sWAYTKT))
						{
							if (gs->m_pGS.tkt[CT].combo <= 4)
								break;
						}
						else
							break;
					}
					else
					{
						if ((nState == sHZENTRY || nState == sVTENTRY) && gs->m_pGS.tkt[CT].grpcount <= 4)
							break;
					}

					if (type == t190UD || type == t190BOX)
					/* Select penny */
						SelectButton(EKBtnPenny,466,332);
					else
					/* Nickel */
						SelectButton(EKBtn[19],466,332);

					ProcBet(1);
					//lastbet = 5;
					//gs->m_pGS.tkt[CT].bet = lastbet;

					//if (nState == sSPECIALS || nState == sVTENTRY || nState == sHZENTRY || nState == sHOUSETKT || nState == sWAYTKT || nState == sWAYPLAYIT || nState == sWAYENTRY)
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].combo;
					//else
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet;

					break;
				}
				case IDF_KEY_F6:
				/* 25 cents clicked */
				{
					CT = gs->GetActiveTicket(); CT--;
					int type = gs->m_pGS.tkt[CT].type;
					
					if (nState == sQUICKPICK)
					{
						if (gs->m_pGS.tkt[CT].picked == 0)
							break;
						else
							SelectButton(EKBtn[20],544,332);
					}
					else
						if (type == t190UD || type == t190BOX)
						/* Select nickel */
							SelectButton(EKBtn[19],544,332);
						else
						/* Quarter */
							SelectButton(EKBtn[20],544,332);

					ProcBet(2);
					//lastbet = 25;
					//gs->m_pGS.tkt[CT].bet = lastbet;

					//if (nState == sSPECIALS || nState == sVTENTRY || nState == sHZENTRY || nState == sHOUSETKT || nState == sWAYTKT || nState == sWAYPLAYIT || nState == sWAYENTRY)
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].combo;
					//else
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet;
					break;
				}
				case IDF_KEY_F7:
				/* 1 dollar clicked */
				{
					CT = gs->GetActiveTicket(); CT--;
					int type = gs->m_pGS.tkt[CT].type;

					if (nState == sQUICKPICK)
					{
						if (gs->m_pGS.tkt[CT].picked == 0)
							break;
						else
							SelectButton(EKBtn[21],466,378);
					}
					else
						if (type == t190UD || type == t190BOX)
						/* Select quarter */
							SelectButton(EKBtn[20],466,378);
						else
						/* Dollar */
							SelectButton(EKBtn[21],466,378);

					ProcBet(3);
					//lastbet = 100;
					//gs->m_pGS.tkt[CT].bet = lastbet;

					//if (nState == sSPECIALS || nState == sVTENTRY || nState == sHZENTRY || nState == sHOUSETKT || nState == sWAYTKT || nState == sWAYPLAYIT || nState == sWAYENTRY)
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].combo;
					//else
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet;
					break;
				}
				case IDF_KEY_F8:
				/* 5 dollars clicked */
				{
					CT = gs->GetActiveTicket(); CT--;
					int type = gs->m_pGS.tkt[CT].type;

					if (nState == sQUICKPICK)
					{
						if (gs->m_pGS.tkt[CT].picked == 0)
							break;
						else
							SelectButton(EKBtn[22],544,378);
					}
					else
						if (type == t190UD || type == t190BOX)
						/* Select dollar */
							SelectButton(EKBtn[21],544,378);
						else
						/* Five dollars */
							SelectButton(EKBtn[22],544,378);

					ProcBet(4);
					//lastbet = 500;
					//gs->m_pGS.tkt[CT].bet = lastbet;

					//if (nState == sSPECIALS || nState == sVTENTRY || nState == sHZENTRY || nState == sHOUSETKT || nState == sWAYTKT || nState == sWAYPLAYIT || nState == sWAYENTRY)
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].combo;
					//else
					//	gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet;
					break;
				}
				case IDF_KEY_F9:
					sndPlaySound("sounds\\chaching.wav",SND_ASYNC);
					if (gs->m_pGS.credits == 0 && nState == sIDLE)
						nMsgScrollPos = 0; dwMsgScrollDelay = 0;
					gs->m_pGS.credits += 1000;
					break;

				case IDF_KEY_F10:
					if (nState == sATTRACT)
					{
						pEvent->SetNotifyWindow(NULL, 0, 0);
						pMediaControl->Stop();
						pPos->put_CurrentPosition(0);

						pVidWin->put_Visible(OAFALSE);

						nState = sIDLE;
					}
					else
					{
						pEvent->SetNotifyWindow((OAHWND)gs->GetHWnd(), WM_GRAPHNOTIFY, 0);
						pVidWin->put_Visible(OATRUE);
						pMediaControl->Run();

						nState = sATTRACT;
					}
				break;
				case IDF_KEY_Q:
				/* Key for printing a ticket */
				{
					DCB dcb;
					COMMTIMEOUTS commtimeouts;
					HANDLE hComm;
					BOOL fWaitingOnRead = FALSE, fRes = FALSE;
					char buf[20], buffer[256];
					DWORD val;

					hComm = CreateFile("COM1",
						GENERIC_READ | GENERIC_WRITE,
						0,
						0,
						OPEN_EXISTING,
						0,
						0);

					if (hComm == INVALID_HANDLE_VALUE)
						/* Unable to open serial port */
					{
						MessageBox(hWnd,"Unable to open printer serial port(COM1)","Error",MB_OK | MB_ICONERROR);
						break;
					}

					SetupComm(hComm,128, 128);

					GetCommState(hComm,&dcb);

					dcb.BaudRate = 9600;
					dcb.ByteSize = 8;
					dcb.Parity = NOPARITY;
					dcb.StopBits = ONESTOPBIT;
					dcb.fAbortOnError = TRUE;

					SetCommState(hComm,&dcb);

					GetCommTimeouts(hComm,&commtimeouts);
					commtimeouts.ReadIntervalTimeout = 5000;
					commtimeouts.ReadTotalTimeoutConstant = 5000;
					commtimeouts.ReadTotalTimeoutMultiplier = 10;
					commtimeouts.WriteTotalTimeoutConstant = 50;
					commtimeouts.WriteTotalTimeoutMultiplier = 10;
					SetCommTimeouts(hComm,&commtimeouts);

                    /* COM port opened successfully, check to see if printer is on */

					/* Reset printer */
					buf[0] = 27; buf[1] = 42;
					WriteFile(hComm,buf,2,&val,NULL);
					//WriteABuffer(hComm,buf,2);
					sprintf(buffer,"WriteFile succeeded, buf==%s,val=%d,buf[0]=%d,buf[1]=%d",buf,val,buf[0],buf[1]);
					MessageBox(hWnd,buffer,"Status",MB_OK);

					buf[0] = 27; buf[1] = 69;
					WriteFile(hComm,buf,2,&val,NULL);
					//WriteABuffer(hComm,buf,2);
					sprintf(buffer,"WriteFile succeeded, buf==%s,val=%d,buf[0]=%d,buf[1]=%d",buf,val,buf[0],buf[1]);
					MessageBox(hWnd,buffer,"Status",MB_OK);

					if (ReadFile(hComm,buf,1,&val,NULL))
					{
						buf[val] = 0;
						sprintf(buffer,"ReadFile succeeded, buf==%s,val=%d,buf[0]=%d",buf,val,buf[0]);
						MessageBox(hWnd,buffer,"Status",MB_OK);
					}
					else
					{
						sprintf(buffer,"ReadFile failed, GetLastError()==%d",GetLastError());
						MessageBox(hWnd,buffer,"Status",MB_OK);
					}

					CloseHandle(hComm);
					break;

				}
				break;

                case IDM_SHOW_DIALOG:
                    {
                        HINSTANCE hInst;
#ifdef _WIN64
                        hInst = (HINSTANCE) GetWindowLongPtr( hWnd, GWLP_HINSTANCE );
#else
                        hInst = (HINSTANCE) GetWindowLong( hWnd, GWL_HINSTANCE );
#endif
                        g_hWndDlg = CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG_EXIT_PERMISSION),
                                                 hWnd, (DLGPROC) ExitDlgProc );
                        ShowWindow( g_hWndDlg, SW_SHOWNORMAL );
						g_bActive = TRUE;
                    }
                    break;
            }
            break; // Continue with default processing

		case WM_GRAPHNOTIFY:
		/* Event notifications from filter graph(attract mode) */
		{
			long evCode, param1, param2;
			HRESULT hr;

			if (pEvent == NULL) return 0;

			while (hr = pEvent->GetEvent(&evCode,&param1,&param2,0), SUCCEEDED(hr))
			{
				hr = pEvent->FreeEventParams(evCode,param1,param2);

				if (evCode == EC_COMPLETE)
				/* Restart video */
				{
					pPos->put_CurrentPosition(0);
					pMediaControl->Run();
				}
			}
		}
		break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
			// Get the mouse x and y position for touch screen processing
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);

			if (msg == WM_RBUTTONUP)
				brClick = TRUE;
			else
				brClick = FALSE;

			if (nState == sATTRACT)
			{
				hr = IDF_KEY_F10;
				goto SendMsg;
			}

			if (dwInvalidSpotsMsg)
				break;

			hr = DecodePosition(xPos, yPos, nState);

			if (hr == IDF_KEY_R)
			/* See if "Run game" was right-clicked */
			{
				if (brClick == TRUE)
					bDraw120 = TRUE;
				else
					bDraw120 = FALSE;
			}

			if(hr>=1 && hr<=80 && nState != sPOW)
			/* Spot touched */
			{
				int result = ProcessNumericTouch(hr, nState);

				if(nState == sBIGTKTUP)
				{
					nState = sSTRAIGHT;
					result = ProcessNumericTouch(hr,nState);
					break;
				}
				else if (nState == sWAYTKT || nState == sWAYPLAYIT)
				{
					nState = sWAYENTRY;
					result = ProcessNumericTouch(hr,nState);
					break;
				}
			}
			else
			/* Button pressed */
			{
				if (nState == sIDLE)
				{
					if (hr == IDM_MODE_RUNGAME && ActiveTickets() < 1)
					/* Cannot click "run game" without active tickets */
						break;
					else if (hr == IDM_MODE_CASHOUT && gs->m_pGS.credits < 1)
					/* Cannot click "Cash out" with no cash! */
						break;
				}
				else if (nState == sPOW && OPT_USEBIGDRAW && POWBigDraw == 0 && hr == IDM_MODE_MSGTOUCH)
				{
					POWBigDraw = 1;
				}
				else if (nState == sPOW && POWBigDraw == 0 && OPT_USEBIGDRAW)
					break;
			}

SendMsg:
			PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(hr, HIWORD(wParam)), lParam);
			break;

        case WM_SIZE:
            // Check to see if we are losing our window...
            if( SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam )
                g_bActive = FALSE;
            else
                g_bActive = TRUE;
            break;

        case WM_EXITMENULOOP:
            // Ignore time spent in menu
            g_dwLastTick = timeGetTime();
            break;

        case WM_EXITSIZEMOVE:
            // Ignore time spent resizing
            g_dwLastTick = timeGetTime();
            break;

        case WM_SYSCOMMAND:
            // Prevent moving/sizing and power loss in fullscreen mode
            switch( wParam )
            {
                case SC_MOVE:
                //case SC_SIZE:
                //case SC_MAXIMIZE:
                //case SC_MONITORPOWER:
                    return TRUE;
            }
            break;

        case WM_DESTROY:
            // Cleanup and close the app
            FreeDirectDraw();
            PostQuitMessage( 0 );
            return 0L;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

//-----------------------------------------------------------------------------
// Name: ExitDlgProc()
// Desc: A dialog that has two challege questions and a password that must all
//		 be correctly answered in order for the system to grant the user leave to
//		 exit to the operating system.
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ExitDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static char strMsg[32];
	static char strResponce1[32];
	static char strResponce2[32];
	static char strPwd[32];
	static int nFocus;
	HWND hWndTextBox = NULL;
	HWND hWndParent = NULL;

    switch (msg)
    {
        case WM_INITDIALOG:
            {
				ZeroMemory( &strMsg, sizeof( strMsg ) );
				ZeroMemory( &strResponce1, sizeof( strResponce1 ) );
				ZeroMemory( &strResponce2, sizeof( strResponce2 ) );
				ZeroMemory( &strPwd, sizeof( strPwd ) );
				nFocus = 1;
            }
            return TRUE;

        case WM_COMMAND:
			if( LOWORD(wParam) == IDC_BTN1)
				strcat(strMsg, "1");
			if( LOWORD(wParam) == IDC_BTN2)
				strcat(strMsg, "2");
			if( LOWORD(wParam) == IDC_BTN3)
				strcat(strMsg, "3");
			if( LOWORD(wParam) == IDC_BTN4)
				strcat(strMsg, "4");
			if( LOWORD(wParam) == IDC_BTN5)
				strcat(strMsg, "5");
			if( LOWORD(wParam) == IDC_BTN6)
				strcat(strMsg, "6");
			if( LOWORD(wParam) == IDC_BTN7)
				strcat(strMsg, "7");
			if( LOWORD(wParam) == IDC_BTN8)
				strcat(strMsg, "8");
			if( LOWORD(wParam) == IDC_BTN9)
				strcat(strMsg, "9");
			if( LOWORD(wParam) == IDC_BTN0)
				strcat(strMsg, "0");
			if( LOWORD(wParam) == IDC_BTNA)
				strcat(strMsg, "A");
			if( LOWORD(wParam) == IDC_BTNB)
				strcat(strMsg, "B");
			if( LOWORD(wParam) == IDC_BTNC)
				strcat(strMsg, "C");
			if( LOWORD(wParam) == IDC_BTND)
				strcat(strMsg, "D");
			if( LOWORD(wParam) == IDC_BTNE)
				strcat(strMsg, "E");
			if( LOWORD(wParam) == IDC_BTNF)
				strcat(strMsg, "F");
			if( LOWORD(wParam) == IDC_BTNG)
				strcat(strMsg, "G");
			if( LOWORD(wParam) == IDC_BTNH)
				strcat(strMsg, "H");
			if( LOWORD(wParam) == IDC_BTNI)
				strcat(strMsg, "I");
			if( LOWORD(wParam) == IDC_BTNJ)
				strcat(strMsg, "J");
			if( LOWORD(wParam) == IDC_BTNK)
				strcat(strMsg, "K");
			if( LOWORD(wParam) == IDC_BTNL)
				strcat(strMsg, "L");
			if( LOWORD(wParam) == IDC_BTNM)
				strcat(strMsg, "M");
			if( LOWORD(wParam) == IDC_BTNN)
				strcat(strMsg, "N");
			if( LOWORD(wParam) == IDC_BTNO)
				strcat(strMsg, "O");
			if( LOWORD(wParam) == IDC_BTNP)
				strcat(strMsg, "P");
			if( LOWORD(wParam) == IDC_BTNQ)
				strcat(strMsg, "Q");
			if( LOWORD(wParam) == IDC_BTNR)
				strcat(strMsg, "R");
			if( LOWORD(wParam) == IDC_BTNS)
				strcat(strMsg, "S");
			if( LOWORD(wParam) == IDC_BTNT)
				strcat(strMsg, "T");
			if( LOWORD(wParam) == IDC_BTNU)
				strcat(strMsg, "U");
			if( LOWORD(wParam) == IDC_BTNV)
				strcat(strMsg, "V");
			if( LOWORD(wParam) == IDC_BTNW)
				strcat(strMsg, "W");
			if( LOWORD(wParam) == IDC_BTNX)
				strcat(strMsg, "X");
			if( LOWORD(wParam) == IDC_BTNY)
				strcat(strMsg, "Y");
			if( LOWORD(wParam) == IDC_BTNZ)
				strcat(strMsg, "Z");
			if( LOWORD(wParam) == IDC_BTN10)
				strcat(strMsg, "@");
			if( LOWORD(wParam) == IDC_BTN11)
				strcat(strMsg, ".");
			if( LOWORD(wParam) == IDC_BTN12)
				strcat(strMsg, "*");
            switch( LOWORD(wParam) )
            {
				case IDC_BTN1:
				case IDC_BTN2:
				case IDC_BTN3:
				case IDC_BTN4:
				case IDC_BTN5:
				case IDC_BTN6:
				case IDC_BTN7:
				case IDC_BTN8:
				case IDC_BTN9:
				case IDC_BTN0:
				case IDC_BTNA:
				case IDC_BTNB:
				case IDC_BTNC:
				case IDC_BTND:
				case IDC_BTNE:
				case IDC_BTNF:
				case IDC_BTNG:
				case IDC_BTNH:
				case IDC_BTNI:
				case IDC_BTNJ:
				case IDC_BTNK:
				case IDC_BTNL:
				case IDC_BTNM:
				case IDC_BTNN:
				case IDC_BTNO:
				case IDC_BTNP:
				case IDC_BTNQ:
				case IDC_BTNR:
				case IDC_BTNS:
				case IDC_BTNT:
				case IDC_BTNU:
				case IDC_BTNV:
				case IDC_BTNW:
				case IDC_BTNX:
				case IDC_BTNY:
				case IDC_BTNZ:
				case IDC_BTN10:
				case IDC_BTN11:
				case IDC_BTN12:
					switch (nFocus)
					{
						case 1:
							hWndTextBox = GetDlgItem(hDlg, IDC_EDIT_1ST_CHALLENGE_RESPONCE);
							break;
						case 2:
							hWndTextBox = GetDlgItem(hDlg, IDC_EDIT_2ND_CHALLENGE_RESPONCE);
							break;
						case 3:
							hWndTextBox = GetDlgItem(hDlg, IDC_EDIT_PASSWORD_RESPONCE);
							break;
					}
									
					SetWindowText(hWndTextBox, (LPSTR) strMsg);
					break;

				case IDC_AC_BUTTON1:
					strcpy(strResponce1, TEXT(strMsg));
					nFocus = 2;
					ZeroMemory( &strMsg, sizeof( strMsg ) );
					break;
					
				case IDC_AC_BUTTON2:
					strcpy(strResponce2, TEXT(strMsg));
					nFocus = 3;
					ZeroMemory( &strMsg, sizeof( strMsg ) );
					break;
					
				case IDC_AP_BUTTON1:
					strcpy(strPwd, TEXT(strMsg));
					//nFocus = 1;
					ZeroMemory( &strMsg, sizeof( strMsg ) );
					break;
					
				case IDCANCEL:
					EndDialog( hDlg, TRUE );
					return TRUE;
					break;

                case IDOK:
					if(strcmp(strResponce1,TEXT("TIME2DV8")) == 0 && 
						strcmp(strResponce2, TEXT("UROK2GO")) == 0 &&
						strcmp(strPwd, TEXT("10SPOT")) == 0)
					{
						hWndParent = GetParent(hDlg);
            			PostMessage( hWndParent, WM_CLOSE, 0, 0 );
						return TRUE;
					}
					else
					{
						EndDialog( hDlg, TRUE );
						return TRUE;
					}
					break;
            }
            break;

        case WM_MOVE:
            // The window is moving around, so re-draw the backbuffer
            DisplayFrame();
            break;

        case WM_DESTROY:
            g_hWndDlg = NULL;
            break;
    }

    return FALSE;
}

//-----------------------------------------------------------------------------
// Name: ProcessNextFrame()
// Desc: Move the sprites, blt them to the back buffer, then 
//       flips the back buffer to the primary buffer
//-----------------------------------------------------------------------------
HRESULT ProcessNextFrame()
{
    HRESULT hr;

    // Figure how much time has passed since the last time
    DWORD dwCurrTick = timeGetTime();
    DWORD dwTickDiff = dwCurrTick - g_dwLastTick;

    // Don't update if no time has passed 
//    if( dwTickDiff == 0 )
//        return S_OK; 

    g_dwLastTick = dwCurrTick;

    // Move the sprites according to how much time has passed
    for( int iSprite = 0; iSprite < NUM_SPRITES; iSprite++ )
       UpdateSprite( &g_Sprite[ iSprite ], dwTickDiff / 1000.0f );

    // Display the sprites on the screen
    if( FAILED( hr = DisplayFrame() ) )
    {
        if( hr != DDERR_SURFACELOST )
            return hr;

        // The surfaces were lost so restore them 
		RestoreSurfaces();
		DisplayFrame();
    }

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: UpdateSprite()
// Desc: Move the sprite around and make it bounce based on how much time 
//       has passed
//-----------------------------------------------------------------------------
VOID UpdateSprite( SPRITE_STRUCT* pSprite, FLOAT fTimeDelta )
{    
    // Update the sprite position
    pSprite->fPosX += pSprite->fVelX * fTimeDelta;
    pSprite->fPosY += pSprite->fVelY * fTimeDelta;

    // Clip the position, and bounce if it hits the edge
    if( pSprite->fPosX < 0.0f )
    {
        pSprite->fPosX  = 0;
        pSprite->fVelX = -pSprite->fVelX;
    }

    if( pSprite->fPosX >= SCREEN_WIDTH - SPRITE_DIAMETER )
    {
        pSprite->fPosX = SCREEN_WIDTH - 1 - SPRITE_DIAMETER;
        pSprite->fVelX = -pSprite->fVelX;
    }

    if( pSprite->fPosY < 0 )
    {
        pSprite->fPosY = 0;
        pSprite->fVelY = -pSprite->fVelY;
    }

    if( pSprite->fPosY > SCREEN_HEIGHT - SPRITE_DIAMETER )
    {
        pSprite->fPosY = SCREEN_HEIGHT - 1 - SPRITE_DIAMETER;
        pSprite->fVelY = -pSprite->fVelY;
    }   
}

//-----------------------------------------------------------------------------
// Name: DisplayFrame()
// Desc: Blts a the sprites to the back buffer, then flips the 
//       back buffer onto the primary buffer.
//-----------------------------------------------------------------------------
HRESULT DisplayFrame()
{
	char buf[256];
	int count, CT = gs->GetActiveTicket(); CT--;
    HRESULT hr;
	unsigned long ticks;

	if (nState == sATTRACT)
	{
		return NULL;
	}

	// These are the task we do in every state
    // Fill the back buffer with black, ignoring errors until the flip
	ticks = GetTickCount();
    g_pDisplay->Clear( 0 );
	DrawBackground(&g_pDisplay, g_pEKBaseSurface, EKBase, 0, 0);
	DrawBetMeter(&g_pDisplay, g_pEKBetMtrSurface, BetMtr, MtrNbrs, MtrPunc, gs->m_pGS.played, 20, 448);
	DrawWonMeter(&g_pDisplay, g_pEKWonMtrSurface, WonMtr, MtrNbrs, MtrPunc, gs->m_pGS.won, 143, 448);
	DrawCreditMeter(&g_pDisplay, g_pEKCreditSurface, CreditMtr, MtrNbrs, MtrPunc, gs->m_pGS.credits, 286, 448);

	/* Randomize numbers */
	cycle_r64();

	switch (nState)
	{

			/*

			DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, 462, 0);
			DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, 20, 19);
			DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, 234, 19);
			DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, 20, 240);
			DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, 234, 240);
			DrawDefaultSmallTicketHeader(&g_pDisplay, g_pEKSTHdr1Surface, TktHdrs[0], 22, 21);
			DrawDefaultSmallTicketHeader(&g_pDisplay, g_pEKSTHdr2Surface, TktHdrs[1], 236, 21);
			DrawDefaultSmallTicketHeader(&g_pDisplay, g_pEKSTHdr3Surface, TktHdrs[2], 22, 242);
			DrawDefaultSmallTicketHeader(&g_pDisplay, g_pEKSTHdr4Surface, TktHdrs[3], 236, 242);
			DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 210);
			DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[0], 20, 210);
			DrawFrame1(&g_pDisplay, g_pEKFrame1Surface, Frame162x65, 460, 205);
			DrawTouchTktMessage(&g_pDisplay, g_pEKRMsgSurface, TouchTkt, 2, 468, 209);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 1, 463, 81);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			{for( int iSprite = 0; iSprite < NUM_SPRITES; iSprite++ )
				{
					g_pDisplay->Blt( (DWORD)g_Sprite[iSprite].fPosX, 
								     (DWORD)g_Sprite[iSprite].fPosY, 
									 g_pDXLogoSurface, NULL );
				}}*/
		case 101:
		case 102:
		case 103:
		case sIDLE:
		/* 
		** Idle & ball drop states:
		** sIDLE: regular small tickets
		** 101: State in which we animate/draw the blower
		** 102: Ball drop loop
		** 103: Ball drop sequence complete, game over
		*/
		{
			DWORD delay = OPT_BALLDROPDELAY;		/* time in ms before dropping another ball */
			int type, index, xpos[4] = { 20, 234, 20, 234 }, ypos[4] = { 19, 19, 240, 240 };
			int xspos[4] = { 22, 236, 22, 236 }, yspos[4] = { 21, 21, 242, 242 };
			int xopos[4] = { 163, 375, 163, 375 }, yopos[4] = { 22, 22, 243, 243 };
			int nbrs[21];

			/*
			for( int iSprite = 0; iSprite < NUM_SPRITES; iSprite++ )
				{
					g_pDisplay->Blt( (DWORD)g_Sprite[iSprite].fPosX, 
								     (DWORD)g_Sprite[iSprite].fPosY, 
									 g_pDXLogoSurface, NULL );
				}
				*/

			for (index = 0; index < 21; index++)
				nbrs[index] = 0;

			if (nState == sIDLE)
			{
				DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, 462, 0);
				//DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 210);
				
				//DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[0], 20, 210);
				//DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[0],20,210);

				DrawFrame1(&g_pDisplay, g_pEKFrame1Surface, Frame162x65, 460, 205);
				DrawTouchTktMessage(&g_pDisplay, g_pEKRMsgSurface, TouchTkt, 2, 468, 209);
				DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);

				if(gs->m_pGS.credits > 0)
				/* Money inserted? */
				{
                    if(ActiveTickets() == 0)
					{
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[1],20,210);
					}
					else if (ActiveTickets() < 4)
					{
						DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[23], SHOW_NORMAL, 504, 374); // Run Game


						/*
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,10);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,40);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,90);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,130);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,190);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,250);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,270);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,300);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,340);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,380);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,400);
						*/

						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[21],20,210);
					}
					else
					{
						DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[23], SHOW_NORMAL, 504, 374); // Run Game
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[22],20,210);
					}

					DrawCashOutButton(&g_pDisplay, g_pEKCashOutSurface, EKBtn[0], SHOW_NORMAL, 513, 294); // Cash Out
				}
				else
					DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[0],20,210);
			}
			else if (nState == 101 || nState == 102)
			/* Blower state / ball drop, draw "GAME CLOSED" in both states */
			{
				DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 210);
				DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[2], 20, 210); // Game closed
			}
			if (nState == 102)
			/* Blower has been drawn, put "GAME IN PROGRESS" msg on screen */
			{
				DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 2, 463, 10);
			}

			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button

			if (OPT_USEBIGDRAW && (nState != sIDLE && nState != 103))
			/* Draw big ticket */
			{
				if( FAILED (hr = g_pEKBTBaseSurface->DrawBitmap(LargeTkt, 0, 0, 442, 402)))
					return hr;

				DrawBigDrawBase(&g_pDisplay, g_pEKBTBaseSurface, gs, 0, &nbrs[0], LargeTkt, &LargeSpot[0], 8, 21);
				DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
				DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,"GAME DRAW",11,25);
				DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 232);
				DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[2], 20, 232); // Game closed
			}
			else
			{
				/* Clear default ticket surface */
				g_pEKSTBaseSurface->SetColorKey(SCREEN_COLORKEY);

				gs->m_bRedraw = TRUE;

				for (count = 0; count < 4; count++)
				{
					if (gs->m_bRedraw)
					/* Draw our ticket/bases */
					{
						DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[count], ypos[count]);
						DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[count], TktHdrs[count], xspos[count], yspos[count]);
						gs->m_bRedraw = FALSE;
					}
					else
					/* Surfaces have been drawn, no need to re-draw */
					{
						g_pDisplay->Blt(xpos[count], ypos[count], g_pEKSTBaseSurface, NULL);
						g_pDisplay->Blt(xspos[count], yspos[count], STHdr[count], NULL);
					}
				}

				/* PERFORMANCE MARKER: 10-20ms at this point */

				for (index = 0; index < 4; index++)
				/* Cycle through tickets and execute the corresponding drawing functions */
				{
					type = gs->m_pGS.tkt[index].type;

					if (type == tWAYTKT ||
						type == tHZROW ||
						type == tVTROW ||
						type == t190UD ||
						type == t190BOX)
					/* Draw way ticket, and horizontal/vertical entry */
					{
						DrawSmallWayTicket(&g_pDisplay,g_pEKSTBaseSurface,gs,index,SmallTkt,SmlGrpLtr,xpos[index],ypos[index]);
						DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,bigtkthdr[11],xspos[index],yspos[index]);
						sprintf(buf,"%d",gs->m_pGS.tkt[index].price);
						DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,index,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[index],yopos[index]);
					}

					else if (type == tSTRAIGHT ||
						type == tQUICKPICK)
					/* Draw straight tickets & quick pick */
					{
						DrawSmallSpotTicket(&g_pDisplay,g_pEKSTBaseSurface,gs,index,SmallTkt,&SmallNbr[0],xpos[index],ypos[index]);
						sprintf(buf,"%4d WAY %2d",gs->m_pGS.tkt[index].combo,gs->m_pGS.tkt[index].picked);
						DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[index],yspos[index]);
						sprintf(buf,"%d",gs->m_pGS.tkt[index].price);
						DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,index,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[index],yopos[index]);
					}

					else if (type == tTOPBOT ||
						type == tLEFTRT ||
						type == tEDGE ||
						type == tODDEVEN)
					/* Draw special tickets */
					{
						DrawSmallSpecialTicket(&g_pDisplay,g_pEKSTBaseSurface,gs,index,SmallTkt,SmallNbr[0],xpos[index],ypos[index]);
						DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,bigtkthdr[type - 1],xspos[index],yspos[index]);
						sprintf(buf,"%d",gs->m_pGS.tkt[index].price);
						DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,index,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[index],yopos[index]);
					}
					else
					/* Draw default ticket */
					{
						//DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[index], ypos[index]);
						//DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[index], TktHdrs[index], xspos[index], yspos[index]);
					}
				}
			}

			if (dwInsertMoneyMsg)
			{
				/* Display message for ~2500ms */
				if ((dwInsertMoneyMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[11], 20, 210);
				}
				else
					dwInsertMoneyMsg = 0;
			}

			if (dwMoreCreditsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwMoreCreditsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[4], 20, 210);
				}
				else
					dwMoreCreditsMsg = 0;
			}

			if (nState == 101)
			/* Draw blower here */
			{
				int index;
				LPDIRECTDRAWSURFACE7 pddsFrontBuffer, pddsBackBuffer;

				sndPlaySound("sounds\\zing.wav",SND_ASYNC);

				for (index = 10; index <= 398; index += OPT_BALLBLOWERADVANCE)
				/* Loop through and animate the drawing of the blower */
				{
					DrawBlowerPortion(&g_pDisplay,g_pEKBlowerSurface,index,EKBase,Blower,465,32);

					// Updating the primary buffer with a blt
					pddsFrontBuffer = g_pDisplay->GetFrontBuffer();
					pddsBackBuffer = g_pDisplay->GetBackBuffer();

					if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
						return hr;
				}

				/* Complete drawing */
				DrawBlowerPortion(&g_pDisplay,g_pEKBlowerSurface,398,EKBase,Blower,465,32);
				pddsFrontBuffer = g_pDisplay->GetFrontBuffer();
				pddsBackBuffer = g_pDisplay->GetBackBuffer();
				if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
					return hr;

				nState = 102;
			}
			else if (nState == 102)
			/* Draw complete blower & drop balls */
			{
				int index, i, tktindex;
				DWORD temp;
				LPDIRECTDRAWSURFACE7 pddsFrontBuffer, pddsBackBuffer;


				/* Clear # of entries caught */
				for (i = 0; i < 4; i++)
				{
					gs->m_pGS.tkt[i].caught[0] = 0;
					//gs->m_pGS.tkt[i].caught[1] = 0;

					// BUG FIXED(11/13/03): No wins on 2 spots
					//gs->m_pGS.tkt[i].caught[1] = 0;
				}

				/* Draw blower */
				DrawBlowerPortion(&g_pDisplay,g_pEKBlowerSurface,398,EKBase,Blower,465,32);
				pddsFrontBuffer = g_pDisplay->GetFrontBuffer();
				pddsBackBuffer = g_pDisplay->GetBackBuffer();
				if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
					return hr;

				/* Now, loop and draw 20 balls */
				temp = GetTickCount();
				for (index = 0; index < 20; index++)
				{
					nbrs[index] = SeqDraw[index];
					if (OPT_USEBIGDRAW)
					{
						DrawBigDrawBase(&g_pDisplay, g_pEKBTBaseSurface, gs, index, &nbrs[0], LargeTkt, &LargeSpot[0], 8, 21);
						DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
						DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,"GAME DRAW",11,25);
						DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 232);
						DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[2], 20, 232); // Game closed
					}
					else
					{
						for (tktindex = 0; tktindex < 4; tktindex++)
						/* Draw catches on small tickets */
						{
							type = gs->m_pGS.tkt[tktindex].type;

							switch (type)
							{
								case tWAYTKT:
								case tHZROW:
								case tVTROW:
								case t190UD:
								case t190BOX:
									/* Draw a small way ticket with every catch */
									DrawSmallWayTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmlGrpLtr,xpos[tktindex],ypos[tktindex]);
									sprintf(buf,"CAUGHT %2d",gs->m_pGS.tkt[tktindex].caught[0]);
									DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
									sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
									DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
								break;
								case tSTRAIGHT:
								case tQUICKPICK:
									/* Small quick pick ticket w/catches */
									DrawSmallSpotTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,xpos[tktindex],ypos[tktindex]);
									sprintf(buf,"CAUGHT %2d",gs->m_pGS.tkt[tktindex].caught[0]);
									DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
									sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
									DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
								break;
								case tTOPBOT:
								case tLEFTRT:
								case tEDGE:
								case tODDEVEN:
									/* Special ticket w/catches */
									DrawSmallSpecialTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmallNbr[0],xpos[tktindex],ypos[tktindex]);

									if (type == tTOPBOT)
										sprintf(buf,"TOP %2d BOTTOM %2d",gs->m_pGS.tkt[tktindex].caught[0],gs->m_pGS.tkt[tktindex].caught[1]);
									else if (type == tLEFTRT)
										sprintf(buf,"LEFT %2d RIGHT %2d",gs->m_pGS.tkt[tktindex].caught[0],gs->m_pGS.tkt[tktindex].caught[1]);
									else if (type == tEDGE)
										sprintf(buf,"CAUGHT %2d",gs->m_pGS.tkt[tktindex].caught[0]);
									else
										sprintf(buf,"ODD %2d EVEN %2d",gs->m_pGS.tkt[tktindex].caught[1],gs->m_pGS.tkt[tktindex].caught[0]);

									DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
									sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
									DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
								break;
								default:
									DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[tktindex], ypos[tktindex]);
									DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[tktindex], TktHdrs[tktindex], xspos[tktindex], yspos[tktindex]);
								break;

							}
						}

					}
					sndPlaySound("sounds\\blurbsnd.wav",SND_ASYNC);
					DrawBallDrop(&g_pDisplay,g_pEKBlowerSurface,index,&SeqDraw[0],Blower, Balls, 465, 32);

					i = GetTickCount();

					while (i + delay > GetTickCount());
				}

				//sprintf(buf,"Took %dms to drop balls",GetTickCount() - temp);
				//MessageBox(g_hWnd,buf,"Information",MB_OK | MB_ICONINFORMATION);

				nMsgScrollPos = 0; dwMsgScrollDelay = 0;
				nState = 103;
				init103 = TRUE;
			}
			else if (nState == 103)
			/* Everythings done, so lets finish up */
			{
				LPDIRECTDRAWSURFACE7 pddsFrontBuffer, pddsBackBuffer;
				int tktindex, index = 20;
				long win;

				POWBigDraw = 0;

				if (init103)
					/* Calculate winnings */
				{
					//CalcDraw

					win = CalcWinningTkts();
				}

				if (OPT_USEBIGDRAW)
				{

					DrawBigDrawBase(&g_pDisplay, g_pEKBTBaseSurface, gs, index, &nbrs[0], LargeTkt, &LargeSpot[0], 8, 21);
					DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
					DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,"GAME DRAW",11,25);
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 232);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[2], 20, 232); // Game closed
				}
				else
				{
					for (tktindex = 0; tktindex < 4; tktindex++)
					/* Draw catches on small tickets */
					{
						type = gs->m_pGS.tkt[tktindex].type;

						switch (type)
						{
							case tWAYTKT:
							case tHZROW:
							case tVTROW:
							case t190UD:
							case t190BOX:
								/* Draw a small way ticket with every catch */
								DrawSmallWayTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmlGrpLtr,xpos[tktindex],ypos[tktindex]);
								sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
								DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
								sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
								DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
							break;
							case tSTRAIGHT:
							case tQUICKPICK:
								/* Small quick pick ticket w/catches */
								DrawSmallSpotTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,xpos[tktindex],ypos[tktindex]);
								sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
								DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
								sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
								DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
							break;
							case tTOPBOT:
							case tLEFTRT:
							case tEDGE:
							case tODDEVEN:
								/* Special ticket w/catches */
								DrawSmallSpecialTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmallNbr[0],xpos[tktindex],ypos[tktindex]);
								sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
								DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
								sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
								DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
							break;
							default:
								DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[tktindex], ypos[tktindex]);
								DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[tktindex], TktHdrs[tktindex], xspos[tktindex], yspos[tktindex]);
							break;

						}

						DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 210);
						DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[2], 20, 210);
					}

				}
				DrawFullBlower(&g_pDisplay,g_pEKBlowerSurface,&SeqDraw[0],Blower, Balls, 465, 32);

				// Updating the primary buffer with a blt
				pddsFrontBuffer = g_pDisplay->GetFrontBuffer();
				pddsBackBuffer = g_pDisplay->GetBackBuffer();

				if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
					return hr;

				if (init103)
				{
					if (win)
					/* They won! So now lets process the win */
					{
						LPDIRECTDRAWSURFACE7 pddsFrontBuffer, pddsBackBuffer;
						long inc = 1, tcredits;
						unsigned long MeterTick;

						pddsFrontBuffer = g_pDisplay->GetFrontBuffer();
						pddsBackBuffer = g_pDisplay->GetBackBuffer();

						if (Yahoo)
							sndPlaySound("sounds\\Yahoo.wav",SND_SYNC);
						else
							sndPlaySound("sounds\\Winner.wav",SND_SYNC);

						if (win >= OPT_CREDITADDS)
							inc = win / OPT_CREDITADDS;

						tcredits = gs->m_pGS.credits + win;
						gs->m_pGS.won = 0;

						MeterTick = GetTickCount() + 100;

						while (gs->m_pGS.credits < tcredits)
						/* Loop through and sequentially add to the meters */
						{
							while (GetTickCount() < MeterTick);
							
							MeterTick = GetTickCount() + OPT_CREDITDELAY;

							if ((tcredits - inc * 2) < gs->m_pGS.credits)
							/* Last pass */
							{
								gs->m_pGS.won = win;
								gs->m_pGS.credits = tcredits;
							}
							else
							{
								gs->m_pGS.won += inc;
								gs->m_pGS.credits += inc;
							}

							/* Update win/bet meters every pass */
							DrawWonMeter(&g_pDisplay, g_pEKWonMtrSurface, WonMtr, MtrNbrs, MtrPunc, gs->m_pGS.won, 143, 448);
							DrawCreditMeter(&g_pDisplay, g_pEKCreditSurface, CreditMtr, MtrNbrs, MtrPunc, gs->m_pGS.credits, 286, 448);

							if( FAILED( hr = pddsFrontBuffer->Blt( NULL, pddsBackBuffer, NULL, DDBLT_WAIT, NULL ) ) )
								return hr;

							sndPlaySound("sounds\\coinout.wav",SND_SYNC);
						}

						gs->m_pGS.credits = tcredits;
						gs->m_pGS.won = win;
					}
					else
						sndPlaySound("sounds\\Boing.wav",SND_SYNC);

					init103 = FALSE;
				}

				/* Switch state over to sPOW(Proof of Win) */
				POWtkt = -1;
				nState = sPOW;

				break;
			}
		}
		break;

		case sPOW:
		/* Proof-of-win screen */
		{
			int tktindex, type, index, xpos[4] = { 20, 234, 20, 234 }, ypos[4] = { 19, 19, 240, 240 };
			int xspos[4] = { 22, 236, 22, 236 }, yspos[4] = { 21, 21, 242, 242 };
			int xopos[4] = { 163, 375, 163, 375 }, yopos[4] = { 22, 22, 243, 243 };
			int nbrs[21], count;
			CSurface* STHdr[4] = { g_pEKSTHdr1Surface, g_pEKSTHdr2Surface, g_pEKSTHdr3Surface, g_pEKSTHdr4Surface} ;

			DrawFullBlower(&g_pDisplay,g_pEKBlowerSurface,&SeqDraw[0],Blower, Balls, 465, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button

			index = 20;
			
			for (count = 0; count < 20; count++)
				nbrs[count] = SeqDraw[count];

			if (OPT_USEBIGDRAW && POWBigDraw == 0)
			{
				DrawBigDrawBase(&g_pDisplay, g_pEKBTBaseSurface, gs, index, &nbrs[0], LargeTkt, &LargeSpot[0], 8, 21);
				DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
				sprintf(buf,"%d TICKETS WON.",wins);
				DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,buf,11,25);
				DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 232);
				DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, "      TOUCH THIS MESSAGE TO VIEW PLAYED TICKETS.", 20, 232); // You won X tickets
				break;
			}
			else
			{
				//DrawClearButton(&g_pDisplay,g_pEKBigClearSurface,ClearBtn,SHOW_NORMAL,460,4);
				//DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[23], SHOW_NORMAL, 504, 374); // Run Game
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[23], SHOW_NORMAL, 465, 4); // Run Game
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, ClearBtn, SHOW_NORMAL, 475 + BW, 4); // Clear

				if (POWtkt != -1)
				/* Proof-of-win ticket selected */
				{
					int lxpos[4]= {  45,260,45,254 };	// logo over tkt # 2,3,0,1
					int lypos[4]= { 275,275,84, 84 };
					int xppos[4]= { 234,20,234,20 };
					tktindex = POWtkt;
					type = gs->m_pGS.tkt[tktindex].type;

					DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[tktindex], ypos[tktindex]);
					DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[tktindex], TktHdrs[tktindex], xspos[tktindex], yspos[tktindex]);

					switch (type)
					{
						case tWAYTKT:
						case tHZROW:
						case tVTROW:
						case t190UD:
						case t190BOX:
							/* Draw a small way ticket with every catch */
							DrawSmallWayTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmlGrpLtr,xpos[tktindex],ypos[tktindex]);
							sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
							DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
							sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
							DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
						break;
						case tSTRAIGHT:
						case tQUICKPICK:
							/* Small quick pick ticket w/catches */
							DrawSmallSpotTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,xpos[tktindex],ypos[tktindex]);
							sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
							DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
							sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
							DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
						break;
						case tTOPBOT:
						case tLEFTRT:
						case tEDGE:
						case tODDEVEN:
							/* Special ticket w/catches */
							DrawSmallSpecialTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmallNbr[0],xpos[tktindex],ypos[tktindex]);
							sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
							DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
							sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
							DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
						break;
						default:
							DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[tktindex], ypos[tktindex]);
							DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[tktindex], TktHdrs[tktindex], xspos[tktindex], yspos[tktindex]);
						break;

					}


					/* Draw Proof-of-win stuff */
					DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, lxpos[tktindex], lypos[tktindex]);
					DrawPOW(&g_pDisplay,g_pEKFrame5Surface,gs,&wcs,Frame204x424,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,tktindex,xppos[tktindex],20);
				}
				else
				/* Display all tickets */
				{
					/* Clear default ticket surface */
					g_pEKSTBaseSurface->SetColorKey(SCREEN_COLORKEY);

					gs->m_bRedraw = TRUE;

					for (count = 0; count < 4; count++)
					{
						if (gs->m_bRedraw)
						/* Draw our ticket/bases */
						{
							DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[count], ypos[count]);
							DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[count], TktHdrs[count], xspos[count], yspos[count]);
							gs->m_bRedraw = FALSE;
						}
						else
						/* Surfaces have been drawn, no need to re-draw */
						{
							g_pDisplay->Blt(xpos[count], ypos[count], g_pEKSTBaseSurface, NULL);
							g_pDisplay->Blt(xspos[count], yspos[count], STHdr[count], NULL);
						}
					}

					if (dwMoreCreditsMsg)
					{
						/* Display message for ~2500ms */
						if ((dwMoreCreditsMsg + 2500) > GetTickCount())
						{
							DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
							DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[4], 20, 210);
						}
						else
							dwMoreCreditsMsg = 0;
					}
					else
					{
						DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface, MsgCntr, 20, 210);
						//DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[3], 20, 210);
						DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface,MsgFont,MsgNbrs,MsgPunc,messages[3],20,210);
					}

					for (tktindex = 0; tktindex < 4; tktindex++)
					/* Draw catches on small tickets */
					{
						type = gs->m_pGS.tkt[tktindex].type;

						switch (type)
						{
							case tWAYTKT:
							case tHZROW:
							case tVTROW:
							case t190UD:
							case t190BOX:
							/* Draw a small way ticket with every catch */
								DrawSmallWayTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmlGrpLtr,xpos[tktindex],ypos[tktindex]);
								sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
								DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
								sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
								DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
							break;
							case tSTRAIGHT:
							case tQUICKPICK:
								/* Small quick pick ticket w/catches */
								DrawSmallSpotTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,xpos[tktindex],ypos[tktindex]);
								sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
								DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
								sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
								DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
							break;
							case tTOPBOT:
							case tLEFTRT:
							case tEDGE:
							case tODDEVEN:
								/* Special ticket w/catches */
								DrawSmallSpecialTicketC(&g_pDisplay,g_pEKSTBaseSurface,gs,tktindex,index,&SeqDraw[0],&SmallNbr[0],SmallTkt,SmallNbr[0],xpos[tktindex],ypos[tktindex]);
								sprintf(buf,"WIN  %s  ",CalcDecimal(0,6,2,gs->m_pGS.tkt[tktindex].won));
								DrawSmallTicketHeader(&g_pDisplay,g_pEKSTHdr1Surface,SmlBlankHdr,SmlHdrFont,SmlHdrNbrs,SmlHdrPunc,buf,xspos[tktindex],yspos[tktindex]);
								sprintf(buf,"%d",gs->m_pGS.tkt[tktindex].price);
								DrawSmallBetText(&g_pDisplay,g_pEKSTOvalSurface,tktindex,SmlOval,SmlBetPunc,SmlBetNbrs,buf,xopos[tktindex],yopos[tktindex]);
							break;
							default:
								DrawDefaultSmallTicketBase(&g_pDisplay, g_pEKSTBaseSurface, SmallTkt, xpos[tktindex], ypos[tktindex]);
								DrawDefaultSmallTicketHeader(&g_pDisplay, STHdr[tktindex], TktHdrs[tktindex], xspos[tktindex], yspos[tktindex]);
							break;

						}
					}
				}
			}
		}

		break;

		case sBIGTKTUP:
			DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, 462, 0);
			DrawBigTicketBase(&g_pDisplay, g_pEKBTBaseSurface, gs, LargeTkt, &LargeSpot[0], 8, 21);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame1(&g_pDisplay, g_pEKFrame1Surface, Frame162x65, 460, 105);
			DrawTouchTktMessage(&g_pDisplay, g_pEKRMsgSurface, TouchTkt, 1, 468, 109);
			DrawORMsg(&g_pDisplay, g_pEKOrLabelSurface, OrLabel, 524, 177);
			DrawFrame2(&g_pDisplay, g_pEKFrame2Surface, Frame162x141, 460, 204);
			DrawORMsg(&g_pDisplay, g_pEKOrLabelSurface, OrLabel, 524, 348);
			DrawTouchOneMsg(&g_pDisplay, g_pEKTchOneSurface, TouchOne, 2, 470, 211);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[3], SHOW_NORMAL, 466, 238); // Quick Pick
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[4], SHOW_NORMAL, 544, 238); // Way Ticket
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[5], SHOW_NORMAL, 466, 288); // Special Ticket
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[6], SHOW_NORMAL, 544, 288); // House Ticket
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 504, 374); // Cancel Button
			DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[0],11,25);
			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);

			DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[13], 20, 232);

			break;

		case sSTRAIGHT:
		/* Do tasks for straight ticket entry */
		{
			char waybuf[16];
			int CT = gs->GetActiveTicket(); CT--;

			DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, 462, 0);
			DrawBigTicketBase(&g_pDisplay, g_pEKBTBaseSurface, gs, LargeTkt, &LargeSpot[0], 8, 21);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame3(&g_pDisplay, g_pEKFrame3Surface, Frame164x324, 460, 105);
			DrawTouchTktMessage(&g_pDisplay, g_pEKRMsgSurface, TouchTkt, 1, 468, 109);
			DrawChangeBet(&g_pDisplay, g_pEKChgBetSurface, ChgBet, 494, 312);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 504, 190); // Cancel Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[8], SHOW_NORMAL, 504, 255); // Play It Button
			//DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 544, 332); // Quarter Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 466, 378); // Dollar Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[22], SHOW_NORMAL, 544, 378); // 5 Dollar Button
			sprintf(waybuf,"1 WAY %d",gs->m_pGS.tkt[CT].picked);
			DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,waybuf,11,25);
			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);
			sprintf(waybuf,"%d",gs->m_pGS.tkt[CT].price);
			DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,waybuf);

			if (nSpotsMax)
			{
				/* Display message for ~2500ms */
				if ((nSpotsMax + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[8], 20, 232);
				}
				else
					nSpotsMax = 0;
			}
			else if (dwInvalidSpotsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwInvalidSpotsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[7], 20, 232);
				}
				else
					dwInvalidSpotsMsg = 0;
			}
			else if (dwMoreCreditsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwMoreCreditsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[4], 20, 210);
				}
				else
					dwMoreCreditsMsg = 0;
			}
			else
				DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[17], 20, 232);

			break;
		}
		case sQUICKPICK:
		/* Quick pick */
		{
			int CT = gs->GetActiveTicket(); CT--;

			DrawBigTicketBase(&g_pDisplay, g_pEKBTBaseSurface, gs, LargeTkt, &LargeSpot[0], 8, 21);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame4(&g_pDisplay, g_pEKFrame4Surface, Frame164x424, 460, 4);
			DrawTouchOneMsg(&g_pDisplay, g_pEKTchOneSurface, TouchOne, 1, 470,10);

			/* Draw spot buttons */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[9], SHOW_NORMAL, 466, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[10], SHOW_NORMAL, 544, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[11], SHOW_NORMAL, 466, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[12], SHOW_NORMAL, 544, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[13], SHOW_NORMAL, 466, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[14], SHOW_NORMAL, 544, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[15], SHOW_NORMAL, 466, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[16], SHOW_NORMAL, 544, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[17], SHOW_NORMAL, 466, 216);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[18], SHOW_NORMAL, 544, 216);

			/* Draw play it, cancel, help, and paytable */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 544, 266); // Cancel Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[8], SHOW_NORMAL, 466, 266); // Play It Button

			/* Change bet section */
			DrawChangeBet(&g_pDisplay, g_pEKChgBetSurface, ChgBet, 494, 312);
			//DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 544, 332); // Quarter Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 466, 378); // Dollar Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[22], SHOW_NORMAL, 544, 378); // 5 Dollar Button

			/* Other stuff now */
			if (gs->m_pGS.tkt[CT].picked == 0)
				DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[1],11,25);
			else
			{
				char buf[64];
				sprintf(buf,"1 WAY %d",gs->m_pGS.tkt[CT].picked);
				DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,buf,11,25);
			}
			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);
			sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
			DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);

			if (dwMoreCreditsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwMoreCreditsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[4], 20, 210);
				}
				else
					dwMoreCreditsMsg = 0;
			}
			else if (!gs->m_pGS.tkt[CT].picked)
                DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[14], 20, 232);
			else
				DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[18], 20, 232);

			break;
		}

		case sSPECIALS:
		/* Draw special ticket screen */
			DrawBigTicketBase(&g_pDisplay, g_pEKBTBaseSurface, gs, LargeTkt, &LargeSpot[0], 8, 21);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame4(&g_pDisplay, g_pEKFrame4Surface, Frame164x424, 460, 4);
			DrawTouchOneMsg(&g_pDisplay, g_pEKTchOneSurface, TouchOne, 1, 470,10);

			/* Ticket type buttons & images */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[27], SHOW_NORMAL, 466, 40); // Top to bottom
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[28], SHOW_NORMAL, 466, 95); // Left to right
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[29], SHOW_NORMAL, 466, 150); // Edge
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[30], SHOW_NORMAL, 466, 205); // Odd/Even
			DrawTktTypes(&g_pDisplay, g_pEKTktTypeSurface, Images);

			/* Change bet section */
			DrawChangeBet(&g_pDisplay, g_pEKChgBetSurface, ChgBet, 494, 312);
			//DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 544, 332); // Quarter Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 466, 378); // Dollar Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[22], SHOW_NORMAL, 544, 378); // 5 Dollar Button

			/* Draw play it, cancel, help, and paytable */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 544, 266); // Cancel Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[8], SHOW_NORMAL, 466, 266); // Play It Button

			/* Draw stuff on-the-fly */
			if (gs->m_pGS.tkt[CT].type != 0)
				DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[gs->m_pGS.tkt[CT].type - 1],11,25);
			else
				DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[2],11,25);

			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);
			sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
			DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);

			if (dwMoreCreditsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwMoreCreditsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[4], 20, 210);
				}
				else
					dwMoreCreditsMsg = 0;
			}
			else if (!gs->m_pGS.tkt[CT].rate)
				DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[15], 20, 232);
			else
				DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[19], 20, 232);

		break;
		
		case sWAYTKT:
		{
			/* Draw main items */
			DrawBigTicketBase(&g_pDisplay, g_pEKBTBaseSurface, gs, LargeTkt, &LargeSpot[0], 8, 21);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame4(&g_pDisplay, g_pEKFrame4Surface, Frame164x424, 460, 4);
			DrawTouchOneMsg(&g_pDisplay, g_pEKTchOneSurface, TouchOne, 1, 470,10);

			/* Draw way buttons */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[35], SHOW_NORMAL, 466, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[36], SHOW_NORMAL, 544, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[37], SHOW_NORMAL, 466, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[38], SHOW_NORMAL, 544, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[39], SHOW_NORMAL, 466, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[40], SHOW_NORMAL, 544, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[41], SHOW_NORMAL, 466, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[42], SHOW_NORMAL, 544, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[43], SHOW_NORMAL, 466, 216);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[44], SHOW_NORMAL, 544, 216);

			/* Change bet section */
			DrawChangeBet(&g_pDisplay, g_pEKChgBetSurface, ChgBet, 494, 312);
			if (gs->m_pGS.tkt[CT].combo > 4)
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 544, 332); // Quarter Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 466, 378); // Dollar Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[22], SHOW_NORMAL, 544, 378); // 5 Dollar Button

			/* Draw group it, cancel, help, and paytable */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 544, 266); // Cancel Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[45], SHOW_NORMAL, 466, 266); // Group It Button

			DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
			//DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[9], 20, 232);
			DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[9], 20, 232);

			DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[11],11,25);
			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);
			sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
			DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);
			DrawWayBox(&g_pDisplay, g_pEKWayBoxSurface,gs,&wcs, WayNbrs, EKBtn[35]);

			break;
		}
		case sWAYENTRY:
		{
			int CT = gs->GetActiveTicket(); CT--;
			/* Draw main items */
			DrawBigTicketBase(&g_pDisplay, g_pEKBTBaseSurface, gs, LargeTkt, &LargeSpot[0], 8, 21);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame4(&g_pDisplay, g_pEKFrame4Surface, Frame164x424, 460, 4);
			DrawTouchOneMsg(&g_pDisplay, g_pEKTchOneSurface, TouchOne, 1, 470,10);

			/* Draw way buttons */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[35], SHOW_NORMAL, 466, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[36], SHOW_NORMAL, 544, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[37], SHOW_NORMAL, 466, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[38], SHOW_NORMAL, 544, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[39], SHOW_NORMAL, 466, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[40], SHOW_NORMAL, 544, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[41], SHOW_NORMAL, 466, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[42], SHOW_NORMAL, 544, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[43], SHOW_NORMAL, 466, 216);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[44], SHOW_NORMAL, 544, 216);

			/* Change bet section */
			DrawChangeBet(&g_pDisplay, g_pEKChgBetSurface, ChgBet, 494, 312);
			if (gs->m_pGS.tkt[CT].combo > 4)
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 544, 332); // Quarter Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 466, 378); // Dollar Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[22], SHOW_NORMAL, 544, 378); // 5 Dollar Button

			/* Draw group it, cancel, help, and paytable */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 544, 266); // Cancel Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[45], SHOW_NORMAL, 466, 266); // Group It Button

			/* The rest goes here */
			DrawWayLtrs(&g_pDisplay,g_pEKBTBaseSurface,gs,LargeTkt,BigGrpLtr);
			DrawWayBox(&g_pDisplay, g_pEKWayBoxSurface,gs,&wcs, WayNbrs, EKBtn[35]);
			sprintf(buf,"1 WAY %d",gs->m_pGS.tkt[CT].picked);

			DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,buf,11,25);
			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);
			sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
			DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);

			if (nSpotsMax)
			{
				/* Display message for ~2500ms */
				if ((nSpotsMax + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[8], 20, 232);
				}
				else
					nSpotsMax = 0;
			}

			if (dwInvalidSpotsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwInvalidSpotsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[7], 20, 232);
				}
				else
					dwInvalidSpotsMsg = 0;
			}


			if (bBlinkNbrs)
			/* Blink the numbers for a variable number of ms */
			{
				DrawWayBoxBlanks(&g_pDisplay, g_pEKWayBoxSurface,gs,&wcs, &AffectedCombos[0], EKBtn[35]);

				if (dwBlinkNbrs == 0)
					dwBlinkNbrs = GetTickCount();
				else
				{
					if ((dwBlinkNbrs + OPT_WAYBLINKDELAY) < GetTickCount())
					/* Blink duration expired */
					{
						dwBlinkNbrs = GetTickCount();
						bBlinkNbrs = FALSE;
					}
				}
			}
			else
			{
               if ((dwBlinkNbrs + OPT_WAYBLINKDELAY) < GetTickCount())
			   /* Time to re-blink */
			   {
				   bBlinkNbrs = TRUE;
				   dwBlinkNbrs = 0;
			   }
			}

			//DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
			//DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[9], 20, 232);

			break;
		}
		case sWAYPLAYIT:
		{
			/* Draw main items */
			DrawBigTicketBase(&g_pDisplay, g_pEKBTBaseSurface, gs, LargeTkt, &LargeSpot[0], 8, 21);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame4(&g_pDisplay, g_pEKFrame4Surface, Frame164x424, 460, 4);
			DrawTouchOneMsg(&g_pDisplay, g_pEKTchOneSurface, TouchOne, 1, 470,10);

			/* Draw way buttons */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[35], SHOW_NORMAL, 466, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[36], SHOW_NORMAL, 544, 32);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[37], SHOW_NORMAL, 466, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[38], SHOW_NORMAL, 544, 78);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[39], SHOW_NORMAL, 466, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[40], SHOW_NORMAL, 544, 124);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[41], SHOW_NORMAL, 466, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[42], SHOW_NORMAL, 544, 170);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[43], SHOW_NORMAL, 466, 216);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[44], SHOW_NORMAL, 544, 216);

			/* Change bet section */
			DrawChangeBet(&g_pDisplay, g_pEKChgBetSurface, ChgBet, 494, 312);
			if (gs->m_pGS.tkt[CT].combo > 4)
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 544, 332); // Quarter Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 466, 378); // Dollar Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[22], SHOW_NORMAL, 544, 378); // 5 Dollar Button

			/* Draw play it, cancel, help, and paytable */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 544, 266); // Cancel Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[8], SHOW_NORMAL, 466, 266); // Play It Button


			DrawWayLtrs(&g_pDisplay,g_pEKBTBaseSurface,gs,LargeTkt,BigGrpLtr);
			DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
			//DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[10], 20, 232);
			DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[10], 20, 232);
			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);
			sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
			DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);
			DrawWayBox(&g_pDisplay, g_pEKWayBoxSurface,gs,&wcs, WayNbrs, EKBtn[35]);

			sprintf(buf,"%d TOTAL WAYS",gs->m_pGS.tkt[CT].combo);
			DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,buf,11,25);

			if (bBlinkNbrs)
			/* Blink the numbers for a variable number of ms */
			{
				DrawWayBoxBlanks(&g_pDisplay, g_pEKWayBoxSurface,gs,&wcs, &AffectedCombos[0], EKBtn[35]);

				if (dwBlinkNbrs == 0)
					dwBlinkNbrs = GetTickCount();
				else
				{
					if ((dwBlinkNbrs + OPT_WAYBLINKDELAY) < GetTickCount())
					/* Blink duration expired */
					{
						dwBlinkNbrs = GetTickCount();
						bBlinkNbrs = FALSE;
					}
				}
			}
			else
			{
               if ((dwBlinkNbrs + OPT_WAYBLINKDELAY) < GetTickCount())
			   /* Time to re-blink */
			   {
				   bBlinkNbrs = TRUE;
				   dwBlinkNbrs = 0;
			   }
			}

			if (dwMoreCreditsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwMoreCreditsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[4], 20, 210);
				}
				else
					dwMoreCreditsMsg = 0;
			}

			break;
		}

		case sHZENTRY:
		case sVTENTRY:
		case sHOUSETKT:
		case sHSENTRY:
		/* Draws the house ticket section */

			CT = gs->GetActiveTicket(); CT--;

			/* Main items */
			DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, 462, 0);
			DrawWayLtrs(&g_pDisplay,g_pEKBTBaseSurface,gs,LargeTkt,BigGrpLtr);
			DrawBigTicketHeader(&g_pDisplay, g_pEKBTHdrSurface, BigHdr, 11, 25);
			DrawGameStat(&g_pDisplay, g_pEKGameStatSurface, GameStat, 3, 463, 81);
			DrawFrame3(&g_pDisplay, g_pEKFrame3Surface, Frame164x324, 460, 107);
			DrawTouchOneMsg(&g_pDisplay, g_pEKTchOneSurface, TouchOne, 1, 470,125);

			/* House ticket buttons */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[31], SHOW_NORMAL, 466, 165); // 190 up down
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[32], SHOW_NORMAL, 544, 165); // 190 boxed
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[33], SHOW_NORMAL, 466, 211); // Horizontal rows
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[34], SHOW_NORMAL, 544, 211); // Vertical rows

			/* Change bet section */
			DrawChangeBet(&g_pDisplay, g_pEKChgBetSurface, ChgBet, 494, 312);

			if (gs->m_pGS.tkt[CT].type == t190UD || gs->m_pGS.tkt[CT].type == t190BOX)
			/* Draw bets in diff places for 190/WAY 8 */
			{
				//DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtnPenny, SHOW_NORMAL, 466, 332); // Penny Button
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 544, 332); // Nickel Button
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 466, 378); // Quarter Button
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 544, 378); // Dollar Button
			}
			else
			/* Draw bets in regular places */
			{
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[20], SHOW_NORMAL, 544, 332); // Quarter Button
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[21], SHOW_NORMAL, 466, 378); // Dollar Button
				DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[22], SHOW_NORMAL, 544, 378); // 5 Dollar Button
				if ((nState == sHZENTRY || nState == sVTENTRY) && gs->m_pGS.tkt[CT].grpcount > 4)
					DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[19], SHOW_NORMAL, 466, 332); // Nickle Button
			}

			/* Draw play it, cancel, help, and paytable */
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[1], SHOW_NORMAL, 466, 436); // Pay Table
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[2], SHOW_NORMAL, 544, 436); // Help Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[7], SHOW_NORMAL, 544, 266); // Cancel Button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[8], SHOW_NORMAL, 466, 266); // Play It Button

			/* The rest goes here */
			DrawBigOval(&g_pDisplay,g_pEKBTHdrSurface,BigOval);
			sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
			DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);

			if (nState == sVTENTRY)
			/* In vertical entry mode */
			{
				sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
				DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);

				if (gs->m_pGS.tkt[CT].groups[0][0] == 0)
				{
					DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[10],11,25);
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
					//DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[6], 20, 232);
				}
				else
				{
					sprintf(buf,"%d WAY %d",gs->m_pGS.tkt[CT].grpcount,gs->m_pGS.tkt[CT].picked);
					DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,buf,11,25);
				}

				DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[5], 20, 232);
			}
			else if (nState == sHZENTRY)
			/* In horizontal entry mode */
			{
				sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
				DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);

				if (gs->m_pGS.tkt[CT].groups[0][0] == 0)
				{
					DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[9],11,25);
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,232);
					//DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[5], 20, 232);
				}
				else
				{
					sprintf(buf,"%d WAY %d",gs->m_pGS.tkt[CT].grpcount,gs->m_pGS.tkt[CT].picked);
					DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,buf,11,25);
				}

				DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[5], 20, 232);
			}
			else
			/* House ticket mode */
			{
				sprintf(buf,"%d",gs->m_pGS.tkt[CT].price);
				DrawBigBetText(&g_pDisplay,g_pEKBTHdrSurface,BigOval,BigBetPunc,BigBetNbrs,buf);

				if (gs->m_pGS.tkt[CT].type == t190UD || gs->m_pGS.tkt[CT].type == t190BOX)
				{
					DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[8],11,25);
					DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[20], 20, 232);
				}
				else
				{
					DrawTicketText(&g_pDisplay,g_pEKBTHdrSurface,BigHdrFont,BigHdrNbrs,bigtkthdr[7],11,25);
					DoScrollingWork(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[16], 20, 232);
				}
			}

			if (dwMoreCreditsMsg)
			{
				/* Display message for ~2500ms */
				if ((dwMoreCreditsMsg + 2500) > GetTickCount())
				{
					DrawMessageCenter(&g_pDisplay, g_pEKMsgCtrSurface,MsgCntr,20,210);
					DrawMsgCntrText(&g_pDisplay,g_pEKMsgCtrSurface, MsgFont, MsgNbrs, MsgPunc, messages[4], 20, 210);
				}
				else
					dwMoreCreditsMsg = 0;
			}

			break;
		case sPAYTABLE1:
		/* Draws pay table #1 & buttons */
			DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, 462, 0);
			DrawPayScreen(&g_pDisplay,g_pEKPayScreenSurface,PayTbl1,20,20);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[24], SHOW_NORMAL, 466, 436); // Game button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[25], SHOW_NORMAL, 544, 436); // More
			break;
		case sPAYTABLE2:
		/* Pay table #2 & buttons */
			DrawGameLogo(&g_pDisplay, g_pEKLogoSurface, EKLogo, 462, 0);
			DrawPayScreen(&g_pDisplay,g_pEKPayScreenSurface,PayTbl2,20,20);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[24], SHOW_NORMAL, 466, 436); // Game button
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[26], SHOW_NORMAL, 544, 436); // Back
			break;
		case sHELPSCRN:
		/* Help screen */
			DrawHelpBG(&g_pDisplay,g_pEKHelpBGSurface,HelpBG,0,0);
			DrawEKButton(&g_pDisplay, g_pEKButtonSurface, EKBtn[24], SHOW_NORMAL, 466, 436); // Game button

			/* Determine current screen for help instructions */
			/* 12,12 (for blting to bg surface from helpbmp) */
			if (nHelpState == sIDLE)
				DrawHelpScreen(&g_pDisplay,g_pEKHelpBGSurface,HelpIdle,0,0);
			else if (nHelpState == sQUICKPICK)
				DrawHelpScreen(&g_pDisplay,g_pEKHelpBGSurface,HelpQP,0,0);
			else if (nHelpState == sSPECIALS)
				DrawHelpScreen(&g_pDisplay,g_pEKHelpBGSurface,HelpSpecials,0,0);
			else if (nHelpState == sHOUSETKT || nHelpState == sHSENTRY)
			{
				DrawHelpScreen(&g_pDisplay,g_pEKHelpBGSurface,HelpHouse,0,0);
			}
			else if (nHelpState == sWAYTKT || nHelpState == sWAYENTRY || nHelpState == sWAYPLAYIT)
				DrawHelpScreen(&g_pDisplay,g_pEKHelpBGSurface,HelpWay,0,0);

			break;
	}

	// Updating the primary buffer with a blt
	//LPDIRECTDRAWSURFACE7 pddsFrontBuffer = g_pDisplay->GetFrontBuffer();
	//LPDIRECTDRAWSURFACE7 pddsBackBuffer = g_pDisplay->GetBackBuffer();

	//sprintf(buf,"Took %dms to process DisplayFrame()(pre-flip)\r\n",GetTickCount() - ticks);
	//OutputDebugString(buf);
	if( FAILED( hr = (g_pDisplay->GetFrontBuffer())->Blt( NULL, g_pDisplay->GetBackBuffer(), NULL, DDBLT_WAIT, NULL ) ) )
		return hr;
	//sprintf(buf,"Took %dms to process DisplayFrame()(post-flip)\r\n",GetTickCount() - ticks);
	//OutputDebugString(buf);

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: RestoreSurfaces()
// Desc: Restore all the surfaces, and redraw the sprite surfaces.
//-----------------------------------------------------------------------------
HRESULT RestoreSurfaces()
{
    HRESULT hr;

    if( FAILED( hr = g_pDisplay->GetDirectDraw()->RestoreAllSurfaces() ) )
        return hr;

    // No need to re-create the surface, just re-draw it.
    if( FAILED( hr = g_pEKBaseSurface->DrawBitmap( EKBase, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) ) )
        return hr;
    if( FAILED( hr = g_pEKBetMtrSurface->DrawBitmap( BetMtr, 0, 0, 116, 28 ) ) )
        return hr;
    if( FAILED( hr = g_pEKWonMtrSurface->DrawBitmap( WonMtr, 0, 0, 136, 28 ) ) )
        return hr;
    if( FAILED( hr = g_pEKCreditSurface->DrawBitmap( CreditMtr, 0, 0, 152, 28 ) ) )
        return hr;

	switch (nState)
	{
		case sATTRACT:
			if( FAILED( hr = g_pEKLogoSurface->DrawBitmap( EKLogo, 0, 0, 156, 79 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTBaseSurface->DrawBitmap( SmallTkt, 0, 0, 204, 186 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr1Surface->DrawBitmap( TktHdrs[0], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr2Surface->DrawBitmap( TktHdrs[1], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr3Surface->DrawBitmap( TktHdrs[2], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr4Surface->DrawBitmap( TktHdrs[3], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKMsgCtrSurface->DrawBitmap( MsgCntr, 0, 0, 418, 25 ) ) )
				return hr;
			if( FAILED( hr = g_pTextSurface->DrawText( NULL, messages[0], 0, 0, RGB(0,0,0), RGB(255, 255, 0) ) ) )
				return hr;
			if( FAILED( hr = g_pEKFrame1Surface->DrawBitmap( Frame162x65, 0, 0, 162, 65 ) ) )
				return hr;
			/*if( FAILED( hr = g_pDXLogoSurface->DrawBitmap( MAKEINTRESOURCE( IDB_DIRECTX ),
                                                 SPRITE_DIAMETER, SPRITE_DIAMETER ) ) )
				return hr;*/
			break;

		case sIDLE:
			if( FAILED( hr = g_pEKLogoSurface->DrawBitmap( EKLogo, 0, 0, 156, 79 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTBaseSurface->DrawBitmap( SmallTkt, 0, 0, 204, 186 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr1Surface->DrawBitmap( TktHdrs[0], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr2Surface->DrawBitmap( TktHdrs[1], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr3Surface->DrawBitmap( TktHdrs[2], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKSTHdr4Surface->DrawBitmap( TktHdrs[3], 0, 0, 200, 18 ) ) )
				return hr;
			if( FAILED( hr = g_pEKMsgCtrSurface->DrawBitmap( MsgCntr, 0, 0, 418, 25 ) ) )
				return hr;
			if( FAILED( hr = g_pTextSurface->DrawText( NULL, messages[0], 0, 0, RGB(0,0,0), RGB(255, 255, 0) ) ) )
				return hr;
			if( FAILED( hr = g_pEKFrame1Surface->DrawBitmap( Frame162x65, 0, 0, 162, 65 ) ) )
				return hr;
			break;

		case sBIGTKTUP:
			if( FAILED( hr = g_pEKLogoSurface->DrawBitmap( EKLogo, 0, 0, 156, 79 ) ) )
				return hr;
			if( FAILED( hr = g_pEKFrame1Surface->DrawBitmap( Frame162x65, 0, 0, 162, 65 ) ) )
				return hr;
			if( FAILED( hr = g_pEKBTBaseSurface->DrawBitmap( LargeTkt, 0, 0, 442, 402 ) ) )
				return hr;
			if( FAILED( hr = g_pEKBTHdrSurface->DrawBitmap( BigHdr, 0, 0, 435, 45 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[1], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[2], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[3], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[4], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[5], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[6], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKTchOneSurface->DrawBitmap( TouchOne, 0, 0, 143, 19 ) ) )
				return hr;
			break;

		case sSTRAIGHT:
			if( FAILED( hr = g_pEKLogoSurface->DrawBitmap( EKLogo, 0, 0, 156, 79 ) ) )
				return hr;
			if( FAILED( hr = g_pEKBTBaseSurface->DrawBitmap( LargeTkt, 0, 0, 442, 402 ) ) )
				return hr;
			if( FAILED( hr = g_pEKBTHdrSurface->DrawBitmap( BigHdr, 0, 0, 435, 45 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[1], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[2], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[7], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[8], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[19], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[20], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[21], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[22], 0, 0, 73, 42 ) ) )
				return hr;
		break;

		case sPAYTABLE1:
			if( FAILED( hr = g_pEKPayScreenSurface->DrawBitmap( PayTbl1, 0, 0, 604, 405) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[24], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[25], 0, 0, 73, 42 ) ) )
				return hr;
		break;
		case sPAYTABLE2:
			if( FAILED( hr = g_pEKPayScreenSurface->DrawBitmap( PayTbl2, 0, 0, 604, 405) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[24], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[25], 0, 0, 73, 42 ) ) )
				return hr;
		break;
		/*
		case sQUICKPICK:
			if( FAILED( hr = g_pEKBTBaseSurface->DrawBitmap( LargeTkt, 0, 0, 442, 402 ) ) )
				return hr;
			if( FAILED( hr = g_pEKBTHdrSurface->DrawBitmap( BigHdr, 0, 0, 435, 45 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[1], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[2], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[7], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[8], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[19], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[20], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[21], 0, 0, 73, 42 ) ) )
				return hr;
			if( FAILED( hr = g_pEKButtonSurface->DrawBitmap( EKBtn[22], 0, 0, 73, 42 ) ) )
				return hr;
				*/

	}

    return S_OK;
}



//--------------------------------------------------------------------------------
// Name: LoadAllGraphics()
// Desc: Load all of the Bitmaps used in this application for use on the surfaces.
//--------------------------------------------------------------------------------
BOOL LoadAllGraphics()
{
	int i;
	char str[255];
    ZeroMemory( &str, sizeof(str) );

	EKBase = GetBitmapFromFile(EKBkgrnd);
	EKLogo = GetBitmapFromFile(EKLogoPath);
	Frame162x65 = GetBitmapFromFile(rSideMsgFrame);
	Frame162x141 = GetBitmapFromFile(Frame162x141Path);
	Frame164x324 = GetBitmapFromFile(Frame164x324Path);
	Frame164x424 = GetBitmapFromFile(Frame164x424Path);
	Frame204x424 = GetBitmapFromFile(Frame204x424Path);
	TouchTkt = GetBitmapFromFile(TouchTktPath);
	GameStat = GetBitmapFromFile(GameStatPath);
	TouchOne = GetBitmapFromFile(TouchOnePath);
	ChgBet = GetBitmapFromFile(ChgBetPath);
	MsgCntr = GetBitmapFromFile(msgCenter);
	OrLabel = GetBitmapFromFile(OrLabelPath);
	for(i=0; i<4; i++)
		TktHdrs[i] = GetBitmapFromFile(smheaders[i]);
	for (i = 0; i < 4; i++)
		Images[i] = GetBitmapFromFile(image[i]);
	BigHdr = GetBitmapFromFile(LTHeaderPath);
	LargeTkt = GetBitmapFromFile(LTBasePath);
	SmallTkt = GetBitmapFromFile(STBasePath);
	BetMtr = GetBitmapFromFile(meterPath[0]);
	WonMtr = GetBitmapFromFile(meterPath[1]);
	CreditMtr = GetBitmapFromFile(meterPath[2]);
	MtrNbrs = GetBitmapFromFile(mtrNbrsPath);
	MtrPunc = GetBitmapFromFile(mtrPuncPath);
	for(i=0; i<50; i++)
		EKBtn[i] = GetBitmapFromFile(btnArray[i]);
	LargeSpot[0] = GetBitmapFromFile(LTSpecialMarkPath);
	SmallNbr[0] = GetBitmapFromFile(STSpecialMarkPath);
	for(i=0; i<80; i++)
	{
		sprintf(str, "bmps\\largetkt\\largespt\\lt%02d.bmp", i+1);
		LargeSpot[i+1] = GetBitmapFromFile(str);
		//ZeroMemory( &str, sizeof(str) );
		sprintf(str, "bmps\\smalltkt\\smallnbr\\st%02d.bmp", i+1);
		SmallNbr[i+1] = GetBitmapFromFile(str);
	}

	/* Load zebs graphics */
	ClearBtn = GetBitmapFromFile(pszClear);
	Balls = GetBitmapFromFile(pszBalls);
	Blower = GetBitmapFromFile(pszBlower);
	PayTbl1 = GetBitmapFromFile(pszPayTable1);
	PayTbl2 = GetBitmapFromFile(pszPayTable2);
	BigHdrFont = GetBitmapFromFile(pszBigHdrFont);
	BigHdrNbrs = GetBitmapFromFile(pszBigHdrNbrs);
	SmlHdrFont = GetBitmapFromFile(pszSmlHdrFont);
	SmlHdrNbrs = GetBitmapFromFile(pszSmlHdrNbrs);
	SmlHdrPunc = GetBitmapFromFile(pszSmlHdrPunc);
	SmlBetNbrs = GetBitmapFromFile(pszSmlBetNbrs);
	SmlBetPunc = GetBitmapFromFile(pszSmlBetPunc);
	BigBetPunc = GetBitmapFromFile(pszBigBetPunc);
	BigBetNbrs = GetBitmapFromFile(pszBigBetNbrs);
	BigOval = GetBitmapFromFile(pszBigOval);
	SmlOval = GetBitmapFromFile(pszSmlOval);
	MsgFont = GetBitmapFromFile(pszMsgFont);
	MsgNbrs = GetBitmapFromFile(pszMsgNbrs);
	MsgPunc = GetBitmapFromFile(pszMsgPunc);
	BigGrpLtr = GetBitmapFromFile(pszBigGrpLtr);
	SmlGrpLtr = GetBitmapFromFile(pszSmlGrpLtr);
	WayNbrs = GetBitmapFromFile(pszWayNbrs);
	SmlBlankHdr = GetBitmapFromFile(pszSTBlankHdr);
	HelpBG = GetBitmapFromFile(pszHelpBG);
	HelpIdle = GetBitmapFromFile(pszHelpIdle);
	HelpQP = GetBitmapFromFile(pszHelpQP);
	HelpSpecials = GetBitmapFromFile(pszHelpSpecials);
	HelpWay = GetBitmapFromFile(pszHelpWay);
	HelpHouse = GetBitmapFromFile(pszHelpHouse);
	EKBtnPenny = GetBitmapFromFile(pszEKBtnPenny);

	return true;
}


//------------------------------------------------------------------------------
// Name: GetBitmapFromFile(TCHAR* strBMP)
// Desc: Is a helper function used to load a Bitmap from a disk file, and then save
//		 an HBITMAP handle to the Bitmap object for future references.
//--------------------------------------------------------------------------------
HBITMAP GetBitmapFromFile(TCHAR* strBMP)
{
	HBITMAP hBMP = NULL;
    BITMAP         bmp;

	hBMP = (HBITMAP) LoadImage( NULL, strBMP, IMAGE_BITMAP, 0, 0, 
								LR_LOADFROMFILE | LR_CREATEDIBSECTION );
    if( hBMP == NULL )
		return 0L;

    // Get size of the bitmap
    GetObject( hBMP, sizeof(bmp), &bmp );

	return hBMP;

}

//--------------------------------------------------------------------------------
// Name: int ActiveTickets()
// Desc: Is a helper function used to count the number of active tickets currently 
//		 established in the state.gam Structure.
//--------------------------------------------------------------------------------
int ActiveTickets()
{
	int t=0;
	int active=0;
    
	for(t=0;t<4;t++)
    {
		if(gs->m_pGS.tkt[t].type)
			active++;
	}
	return(active);
}


//--------------------------------------------------------------------------------
// Name: HRESULT ProcessNumericTouch(long num, int nState)
// Desc: Is a helper function used to Process the screen touch at a numeric position 
//		 on the big data entry ticket.
//--------------------------------------------------------------------------------
HRESULT ProcessNumericTouch(long num, int nState)
{
	int CT, s, g = 0, n = 0;
	bool remove = false;

	sndPlaySound("sounds\\btnclick.wav",SND_ASYNC);
	CT = gs->GetActiveTicket(); CT--;

    if(nState==sBIGTKTUP)	// if 1st spot touched
	{	
		/* Set current bet to $1.00 */
		dfltbet = 100;
		lastbet = dfltbet;

		nMsgScrollPos = 0; dwMsgScrollDelay = 0;

    	memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
        gs->m_pGS.tkt[CT].grpcount=1;
        gs->m_pGS.tkt[CT].rate=0;
        gs->m_pGS.tkt[CT].picked=0;
        gs->m_pGS.tkt[CT].combo=1;
	    gs->m_pGS.tkt[CT].type=tSTRAIGHT;	// mark type of ticket
	    gs->m_pGS.tkt[CT].bet=dfltbet;
	    gs->m_pGS.tkt[CT].price=dfltbet;
		return(0);
    }
    else if(nState==sSTRAIGHT)				// are we in straight ticket entry ?
	{
		for(s=0;s<20;s++)					// if so check for spot removal
        {
			if(gs->m_pGS.tkt[CT].groups[0][s]==num)
            {
    			remove=true;
            	break;
            }
		}
		if(!remove)
		{
			if(gs->m_pGS.tkt[CT].picked < 20)
			{
				gs->m_pGS.tkt[CT].groups[0][gs->m_pGS.tkt[CT].picked]=num; // save 1st spot touched
				gs->m_pGS.tkt[CT].picked+=1;
				gs->UpdateGameState();
				return(gs->m_pGS.tkt[CT].picked);
			}
			else
			/* Max spots reached, raise flag to display msg */
			{
				nSpotsMax = GetTickCount();
				sndPlaySound("sounds\\horn.wav",SND_ASYNC);
				return(gs->m_pGS.tkt[CT].picked);
			}
		}
		else
		{
			for(;s<20;s++)
			{
				gs->m_pGS.tkt[CT].groups[0][s]=gs->m_pGS.tkt[CT].groups[0][s+1];
				gs->m_pGS.tkt[CT].groups[0][s+1]=0;
			}
			gs->m_pGS.tkt[CT].picked-=1;
			gs->UpdateGameState();
			return(gs->m_pGS.tkt[CT].picked);
		}
	}
	else if(nState==sHZENTRY)
    // Do Processing for Horizontal Entry Touch
	{
		int row, letr, prevgrpcount = gs->m_pGS.tkt[CT].grpcount;

		row = CalcHoriz(num,&letr);

		if (prevgrpcount == 5 && gs->m_pGS.tkt[CT].grpcount == 4 && gs->m_pGS.tkt[CT].bet == 5)
			gs->m_pGS.tkt[CT].bet = 100;

		gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].grpcount;

		return(0);
	}
	else if(nState==sVTENTRY)
    // Do Processing for Vertical Entry Touch
	{
		int col, letr, prevgrpcount = gs->m_pGS.tkt[CT].grpcount;

		col = CalcVert(num,&letr);

		if (prevgrpcount == 5 && gs->m_pGS.tkt[CT].grpcount == 4 && gs->m_pGS.tkt[CT].bet == 5)
			gs->m_pGS.tkt[CT].bet = 100;

		gs->m_pGS.tkt[CT].price = gs->m_pGS.tkt[CT].bet * gs->m_pGS.tkt[CT].grpcount;

		return(0);
	}
	else if(nState==sWAYENTRY)
	/* Does DrawWayEntry() in borland app */
	{

		for (g = 0; g < 20; g++)
		{
			for (s = 0; s < 20; s++)
			{
				if (gs->m_pGS.tkt[CT].groups[g][s] == num)
				{
					for (n = 0; n < 20; n++)
						gs->m_pGS.tkt[CT].groups[g][n] = 0;
					remove = true;
					break;
				}
			}
			if (remove)
				break;
		}

		if (remove)
		/* Spot removal */
		{
			gs->m_pGS.tkt[CT].grpcount -= 1;
			
			if (gs->m_pGS.tkt[CT].grpcount < 1)
				gs->m_pGS.tkt[CT].grpcount = 1;

			gs->m_pGS.tkt[CT].picked = GetGroupItemNum(CT,gs->m_pGS.tkt[CT].grpcount - 1);
			RecalcGroups(gs->m_pGS.tkt[CT].grpcount);
			/* DrawWayBtns(); */
			CalcWayTkt();
			/* DrawWaysPlayed(); */
		}
		else
		/* Adding spot */
		{
			g = gs->m_pGS.tkt[CT].grpcount; g--;

			if (gs->m_pGS.tkt[CT].picked >= 20)
			{
				nSpotsMax = GetTickCount();
				sndPlaySound("sounds\\horn.wav",SND_ASYNC);
				return(gs->m_pGS.tkt[CT].picked);
			}
			for (s = 0; s < 20; s++)
			{
				if (gs->m_pGS.tkt[CT].groups[g][s] == 0)
				/* Put spot touched here */
				{
					gs->m_pGS.tkt[CT].groups[g][s] = num;

					if (s == 0)
						gs->m_pGS.tkt[CT].picked = 1;
					else
						gs->m_pGS.tkt[CT].picked++;

					break;
				}

			}

		}
		return(0);
	}
	return(0);
}

BOOL SelectButton(HBITMAP Button, int cXpos, int cYpos)
/*
** SelectButton()
** Highlights a button at the specified location 
*/
{
	int CT = gs->GetActiveTicket(); CT--;

	sndPlaySound("sounds\\btnclick.wav",SND_ASYNC);

	DrawHiLiteEKButton(&g_pDisplay, g_pEKButtonSurface, Button, SHOW_HILITE, cXpos, cYpos);
	btick=GetTickCount()+250;
	while(btick>GetTickCount());// visual button click
	DrawHiLiteEKButton(&g_pDisplay, g_pEKButtonSurface, Button, SHOW_NORMAL, cXpos, cYpos);

	return TRUE;
}

void CalcQP(int qp)
{
	bool duped;
	int picked, b,i,spot=qp, CT = gs->GetActiveTicket(); CT--;
	
	picked = gs->m_pGS.tkt[CT].picked;
	memset(&gs->m_pGS.tkt[CT],0,sizeof(gs->m_pGS.tkt[CT]));
    while(spot) {						// get qp # of spots
       	duped=false;
       	b=get_ball();
        for(i=0;i<20;i++) {
          	if(gs->m_pGS.tkt[CT].groups[0][i]) {
               	if(b==gs->m_pGS.tkt[CT].groups[0][i]) {
                   	duped=true;
                    break;
                }
            }
            else break;
        }
        if(!duped) {
           	gs->m_pGS.tkt[CT].groups[0][i]=b;

            spot-=1;
        }
    }
	gs->m_pGS.tkt[CT].grpcount=1;		// 1 group played
	gs->m_pGS.tkt[CT].combo=1;			// 1 combo
	gs->m_pGS.tkt[CT].picked=qp;		// save way
    gs->m_pGS.tkt[CT].rate=0;			// regular rate
	gs->m_pGS.tkt[CT].bet=lastbet;		// and whatever default BET is now
    gs->m_pGS.tkt[CT].price=lastbet;
    gs->m_pGS.tkt[CT].type=tQUICKPICK;
    tktways[CT]=qp;

	if (picked == 0)
	{
		nMsgScrollPos = 0; dwMsgScrollDelay = 0;
	}
	
}

int get_ball(void)
{
	int n=(int) RND();
    if(n<0)
    	n*=-1;
    n%=80;
    n+=1;
    return n;
}

void RecalcGroups(int grps)
{
	int g,s;
	int CT = gs->GetActiveTicket(); CT--;

    for(g=0;g<grps;g++) {
		if(gs->m_pGS.tkt[CT].groups[g][0]==0) {		// if this group removed ...
           	for(s=0;s<20;s++) {             	// shift next group in
               	gs->m_pGS.tkt[CT].groups[g][s]=gs->m_pGS.tkt[CT].groups[g+1][s];
               	gs->m_pGS.tkt[CT].groups[g+1][s]=0;  // clear this group
            }
        }
    }
}

void CalcWayTkt(void)
{
	char buf[256];
	int j,k,w;

	AT = gs->GetActiveTicket(); AT--;

    gs->m_pGS.tkt[AT].combo=0;	// put total combos here

	if (gs->m_pGS.tkt[AT].type == tWAYTKT)
	/* Activate ways to play */
	{
		for(w=0;w<10;w++)
		{
    		gs->m_pGS.tkt[AT].ways[w]=WaysToPlay[AT][w];
		}
	}
	else if (gs->m_pGS.tkt[AT].type == tHZROW)
	/* Horizontal entry */
	{
		gs->m_pGS.tkt[AT].ways[8] = 10;
	}
	else if (gs->m_pGS.tkt[AT].type == tVTROW)
	/* Vertical entry */
	{
		gs->m_pGS.tkt[AT].ways[6] = 8;
	}

	//sprintf(buf,"wcs.combo[]=%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",wcs.combo[0],wcs.combo[1],wcs.combo[2],wcs.combo[3],wcs.combo[4],wcs.combo[5],wcs.combo[6],wcs.combo[7],wcs.combo[8],wcs.combo[9],wcs.combo[10]);

	//MessageBox(g_hWnd,buf,"combo=",MB_OK);

	/* Make list of "affected combos" */
	if (bDelAffectedWays == TRUE)
	{
		for (w=0;w<21;w++)
			AffectedCombos[w] = wcs.combo[w];
	}
	else
        bDelAffectedWays = TRUE;

	sprintf(buf,"gs->m_pGS.tkt[%d].ways[0]==%d(Before CWT)\n",AT,gs->m_pGS.tkt[AT].ways[0]);
	OutputDebugString(buf);
	ComputeWayTkt(AT,false);	// no pay, just get combos
	sprintf(buf,"gs->m_pGS.tkt[%d].ways[0]==%d(After CWT)\n",AT,gs->m_pGS.tkt[AT].ways[0]);
	OutputDebugString(buf);
    for(j=0;j<10;j++) {
    	if(gs->m_pGS.tkt[AT].ways[j]) {
			sprintf(buf,"gs->m_pGS.tkt[%d].ways[%d]==%d(Loop)\n",AT,j,gs->m_pGS.tkt[AT].ways[j]);
			OutputDebugString(buf);
		    k=1;
			while(wcs.ways[k]) {
            	if(wcs.ways[k]==gs->m_pGS.tkt[AT].ways[j]) {
					if(wcs.counts[k]) {
                    	wcs.combo[gs->m_pGS.tkt[AT].ways[j]] += wcs.counts[k];
                    }
                }
			    k++;
            }
           	if(wcs.combo[gs->m_pGS.tkt[AT].ways[j]]) {
	           	/* DrawWayBox(gs->m_pGS.tkt[AT].ways[j],combo[gs->m_pGS.tkt[AT].ways[j]]); */
                gs->m_pGS.tkt[AT].combo+=wcs.combo[gs->m_pGS.tkt[AT].ways[j]];
            }
            // check total combo for limit > 9999 ????
        }
    }

	gs->m_pGS.tkt[AT].price = gs->m_pGS.tkt[AT].bet * gs->m_pGS.tkt[AT].combo;
}

long ComputeWayTkt(int tk,bool payit)
{
	int g,i,j,k;
	long winnings=0,win,twin;
	char buf[256];

	memset(&wcs,0,sizeof(wcs));

	wcs.counts[0]=1;							// must start with 1 way 0
	taddcnt=addcnt=1;						// indices to combinations
//	for(g=0;g<gs->m_pGS.tkt[tk].grpcount;g++) {	// up to 20 groups...
	for(g=0;g<20;g++) {						// up to 20 groups...
    	for(j=0;j<20;j++) {					// up to 20 spots...
			if(gs->m_pGS.tkt[tk].groups[g][j]) {	// if a spot here...
				for(k=0;k<20;k++) {
					if(gs->m_pGS.tkt[tk].groups[g][j]==SeqDraw[k]) {
						wcs.hits[g]+=1;
						break;
					}
				}
				wcs.eagrp[g]+=1;				// incr # of spots in each group
			}
            else break;						// end of spots this group
        }
	}
//    for(g=0;g<st.tkt[tk].grpcount;g++) {
//    	sprintf(str,"GRP %2d HITS %4d EAGRP %4d",g+1,hits[g],wcs.eagrp[g]);
//        MainForm->Memo1->Lines->Add(str);
//    }
//    for(g=0;g<10;g++) {
//    	sprintf(str,"WAY %2d  %4d",g+1,st.tkt[tk].ways[g]);
//        MainForm->Memo1->Lines->Add(str);
//    }

//	for(i=0;i<st.tkt[tk].grpcount;i++) {	// for all the groups
	for(i=0;i<20;i++) {						// for all the groups
    	if(wcs.eagrp[i]) {
			addcnt=taddcnt;						// include combs from last grp calc
			for(j=0;j<addcnt;j++)				// save old count values
				wcs.ocounts[j]=wcs.counts[j];
			for(j=0;j<addcnt;j++) {
				newhit=wcs.katch[j]+wcs.hits[i];		// add hits for this comb
				newway=wcs.ways[j]+wcs.eagrp[i];		// get comb
				if(newway>20)					// combo more than we need?
					continue;					// yes, skip next
				for(k=0;k<taddcnt;k++) {		// new combination?
					if(newway==wcs.ways[k] && newhit==wcs.katch[k])
	                	break;					// no
	            }
				if(k==taddcnt) {				// new combination?
					wcs.ways[taddcnt]=newway;		// yes, save it
					wcs.katch[taddcnt]=newhit;
					wcs.ocounts[taddcnt++]=0;		// clear next
				}
				wcs.counts[k]=wcs.ocounts[j]+wcs.ocounts[k];// add comb/hit variation
			}
		}
    }
    if(!payit)
    	return(0);
	win=0;

    for(j=0;j<10;j++) {
    	if(gs->m_pGS.tkt[tk].ways[j]) {
		    k=1;
			while(wcs.ways[k]) {
            	if(wcs.ways[k]==gs->m_pGS.tkt[tk].ways[j]) 
				{
					if(wcs.counts[k]) 
					{
		               	twin=(PayTable(gs->m_pGS.tkt[tk].ways[j],gs->m_pGS.tkt[tk].rate,wcs.katch[k],gs->m_pGS.tkt[tk].bet))*wcs.counts[k];	// way,catch,bet
                        win+=twin;
                    }
                }
			    k++;
            }
        }
    }
	winnings+=win;
    return(winnings);
}
bool LoadPayTables(void)
{
	FILE *fp;
    bool status=true;
    char file[20];
    int c,f;
    long pay[5][21]={
//    		{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21}};
    		{12500,6250,1000,250,25,15,10,5,0,0,0,0,0,5,10,15,25,250,1000,6250,12500},// top/bot
    		{12500,6250,1000,250,25,15,10,5,0,0,0,0,0,5,10,15,25,250,1000,6250,12500},// left/right
    		{12500,6250,1000,250,25,15,10,5,0,0,0,0,0,5,10,15,25,250,1000,6250,12500},// edge
    		{12500,6250,1000,250,25,10,5,0,0,0,0,0,0,0,5,10,25,250,1000,6250,12500},// odd/even
    		{12500,6250,1000,250,25,15,10,5,0,0,0,0,0,5,10,15,25,250,1000,6250,12500}};

	sprintf(SpecWay[0],"TOP/BOTTOM");
	sprintf(SpecWay[1],"LEFT/RIGHT");
	sprintf(SpecWay[2],"  EDGE    ");
	sprintf(SpecWay[3]," ODD/EVEN ");

	if (OPT_CREATENEWPAYTABLE == 1)
	/* Create new regular paytable */
	{
		/* Paytable from Sept. 2003
		long spot2[3] = { 0, 0, 375 };
		long spot3[4] = { 0, 0, 125, 3750 };
		long spot4[5] = { 0, 0, 0, 125, 5500 };
		long spot5[6] = { 0, 0, 0, 125, 625, 6250 };
		long spot6[7] = { 0, 0, 0, 250, 625, 2750, 50000 };
		long spot7[8] = { 0, 0, 0, 0, 125, 625, 5000, 25000 };
		long spot8[9] = { 0, 0, 0, 0, 0, 250, 1250, 75000, 112500 };
		long spot9[10] = { 0, 0, 0, 0, 0, 250, 1000, 7500, 112500, 625000 };
		long spot10[11] = { 0, 0, 0, 0, 0, 125, 375, 5000, 20000, 112500, 625000 };
		long spot20[21] = { 2500, 150, 50, 25, 0, 0, 0, 25, 50, 150, 500, 1000, 5000, 30000, 80000, 150000, 250000, 250000, 250000, 250000, 250000 };
		*/

		/* Paytable from Nov. 2003 */
		long spot2[3] = { 0, 0, 375 };
		long spot3[4] = { 0, 0, 50, 1100 };
		long spot4[5] = { 0, 0, 25, 150, 3500 };
		long spot5[6] = { 0, 0, 25, 50, 325, 12000 };
		long spot6[7] = { 0, 0, 0, 25, 225, 2500, 40000 };
		long spot7[8] = { 0, 0, 0, 25, 75, 250, 10000, 200000 };
		long spot8[9] = { 0, 0, 0, 0, 125, 250, 1250, 18000, 400000 };
		long spot9[10] = { 0, 0, 0, 0, 50, 200, 400, 3000, 100000, 625000 };
		long spot10[11] = { 0, 0, 0, 0, 25, 100, 400, 3000, 25000, 125000, 625000 };
		long spot20[21] = { 2500, 150, 50, 25, 0, 0, 0, 25, 50, 150, 500, 1000, 5000, 30000, 80000, 150000, 250000, 250000, 250000, 250000, 250000 };


		memset((void*)&tbl,0,sizeof(tbl));
		tbl.rate = 1;
		strcpy(tbl.name,"REGULAR");
		tbl.price = 25;
		tbl.balls = 80;
		tbl.draw = 20;

		memcpy(&tbl.spot2[0],&spot2[0],sizeof(spot2));
		memcpy(&tbl.spot3[0],&spot3[0],sizeof(spot3));
		memcpy(&tbl.spot4[0],&spot4[0],sizeof(spot4));
		memcpy(&tbl.spot5[0],&spot5[0],sizeof(spot5));
		memcpy(&tbl.spot6[0],&spot6[0],sizeof(spot6));
		memcpy(&tbl.spot7[0],&spot7[0],sizeof(spot7));
		memcpy(&tbl.spot8[0],&spot8[0],sizeof(spot8));
		memcpy(&tbl.spot9[0],&spot9[0],sizeof(spot9));
		memcpy(&tbl.spot10[0],&spot10[0],sizeof(spot10));
		memcpy(&tbl.spot20[0],&spot20[0],sizeof(spot20));

		if((fp=fopen("regular1.tbl","w+b"))!=NULL) {
			fwrite(&tbl,sizeof(tbl),1,fp);
			fclose(fp);
		}
	}
	if ((fp=fopen("regular.tbl","rb")) !=NULL ) {
		if(fread(&tbl,sizeof(tbl),1,fp)!=NULL) {
	        fclose(fp);
            status=true;
        }
        else {
        	fclose(fp);
            return(false);
        }
    }
	if(status) {
    	for(f=1;f<=4;f++) {
        	sprintf(file,"special%d.tbl",f);
			if((fp=fopen(file,"rb"))!=NULL) {
				if(fread(&spcltbl[f-1],sizeof(spcltbl[f-1]),1,fp)!=NULL)
			        fclose(fp);
		        else {
		        	fclose(fp);
		            return(false);
		        }
            }
			else {
				if((fp=fopen(file,"w+b"))!=NULL) {
			    	memset(&spcltbl[f-1],0,sizeof(spcltbl[f-1]));
                   	spcltbl[f-1].rate=(char)(f-1);
                    spcltbl[f-1].price=5;
                    for(c=0;c<=20;c++)
                    	spcltbl[f-1].spot20[c]=pay[f-1][c];
					fwrite(&spcltbl[f-1],sizeof(spcltbl[f-1]),1,fp);
			        fclose(fp);
			    }
		        else {
		        	fclose(fp);
		            return(false);
		        }
            }
        }
    }
    return(status);
}

long PayTable(int way,int rate,int caught,long bet)
{
	long win;

	if(rate==0) {		// regular ticket
	    switch(way) {
	    	case  0:	return(0);	// invalid way
	        case  1:	win=tbl.spot1[caught];break;
	        case  2:	win=tbl.spot2[caught];break;
	        case  3:	win=tbl.spot3[caught];break;
	        case  4:	win=tbl.spot4[caught];break;
	        case  5:	win=tbl.spot5[caught];break;
	        case  6:	win=tbl.spot6[caught];break;
	        case  7:	win=tbl.spot7[caught];break;
	        case  8:	win=tbl.spot8[caught];break;
	        case  9:	win=tbl.spot9[caught];break;
	        case 10:	win=tbl.spot10[caught];break;
	        case 11:	win=tbl.spot11[caught];break;
	        case 12:	win=tbl.spot12[caught];break;
	        case 13:	win=tbl.spot13[caught];break;
	        case 14:	win=tbl.spot14[caught];break;
	        case 15:	win=tbl.spot15[caught];break;
	        case 20:	win=tbl.spot20[caught];break;
	        default:	return(0);
		}
	    if(bet==tbl.price)
		    return(win);
	    win = (bet*win) / tbl.price;
	    return(win);
    }
    else {
        win=spcltbl[rate-1].spot20[caught];
	    if(bet==spcltbl[rate-1].price)
		    return(win);
	    win = (bet*win) / spcltbl[rate-1].price;
	    return(win);
    }
}

int GetGroupNum(int tkt)
/*
** GetGroupNum()
** Returns the number of valid groups
*/
{
	int index, retval = 1;

	for (index = 0; index < 20; index++)
		if (gs->m_pGS.tkt[tkt].groups[index][0] != 0)
			retval++;
	
	return retval;
}

int CalcHoriz(int spot,int *grpletr)
{
	bool remove=false;
	int b=0,s,grp,startrow;

	int CT = gs->GetActiveTicket(); CT--;

	s=startrow=(((spot-1)/10)*10)+1;	// scale to 1,11,21,31 ....
    if(startrow) {
	    for(grp=0;grp<8;grp++) {
		    if(gs->m_pGS.tkt[CT].groups[grp][0]==0) {		// row not played yet
			    for(b=0;b<10;s++,b++)
			       	gs->m_pGS.tkt[CT].groups[grp][b]=s;		// put spot in this group
	            break;
	        }
		    else {
		       	if(gs->m_pGS.tkt[CT].groups[grp][b]==s) {	// this row already played ?
				    for(b=0;b<10;b++)					// MUST REJUSTIFY ENTIRE TKT !!!!
			           	//gs->m_pGS.tkt[CT].groups[grp][b++]=0;// yes, clear entire group
						gs->m_pGS.tkt[CT].groups[grp][b]=0;// yes, clear entire group
			        remove=true;
	                break;;
		        }
		    }
	    }
		if(remove) {
		   	gs->m_pGS.tkt[CT].grpcount-=1;
		   	gs->m_pGS.tkt[CT].combo-=1;
		    if(gs->m_pGS.tkt[CT].grpcount==0)
		       	startrow=-1;				// no rows played, clear tkt
	        else {
	            RecalcGroups(8);			// justify groups
	           	startrow=0;					// must redraw tkt
	        }
		}
		else {
		    *grpletr=gs->m_pGS.tkt[CT].grpcount;
		   	gs->m_pGS.tkt[CT].grpcount+=1;
		   	gs->m_pGS.tkt[CT].combo+=1;
	    }
	   	gs->m_pGS.tkt[CT].picked=10;
	   	gs->m_pGS.tkt[CT].rate=0;			// regular rate
        gs->m_pGS.tkt[CT].price=gs->m_pGS.tkt[CT].bet*gs->m_pGS.tkt[CT].combo;
    }

    return(startrow);	// actual row #
}
int CalcVert(int spot,int *grpletr)
{
	bool remove=false;
	int b,s,grp,startcol;

	int CT = gs->GetActiveTicket(); CT--;

    s=startcol=spot%10;
    if(!startcol)		// #'s 10-80 ?
    	s=startcol=10;
    for(grp=0;grp<10;grp++) {
	    if(gs->m_pGS.tkt[CT].groups[grp][0]==0) {		// this column available ?
		    for(b=0;b<8;s+=10,b++)
		       	gs->m_pGS.tkt[CT].groups[grp][b]=s;		// put spot in this group
            break;
        }
	    else {
	       	if(gs->m_pGS.tkt[CT].groups[grp][0]==s) {	// remove this column ?
			    for(b=0;b<8;b++)					// MUST REJUSTIFY ENTIRE TKT !!!!
		           	//gs->m_pGS.tkt[CT].groups[grp][b++]=0;// yes, clear entire group
					gs->m_pGS.tkt[CT].groups[grp][b]=0;
		        remove=true;
                break;;
	        }
	    }
    }
	if(remove) {
	   	gs->m_pGS.tkt[CT].grpcount-=1;
	   	gs->m_pGS.tkt[CT].combo-=1;
	    if(gs->m_pGS.tkt[CT].grpcount==0)
	       	startcol=-1;				// no columns played, clear tkt
        else {
            RecalcGroups(10);			// justify groups
           	startcol=0;					// must redraw tkt
        }
	}
	else {
	    *grpletr=gs->m_pGS.tkt[CT].grpcount;
	   	gs->m_pGS.tkt[CT].grpcount+=1;
	   	gs->m_pGS.tkt[CT].combo+=1;
    }
   	gs->m_pGS.tkt[CT].picked=8;
   	gs->m_pGS.tkt[CT].rate=0;			// regular rate
    gs->m_pGS.tkt[CT].price=gs->m_pGS.tkt[CT].bet*gs->m_pGS.tkt[CT].combo;
    return(startcol);	// actual col #
}

void CalcPlayWay(int way)
{
	bool remove=false;
	int w;
	int CT = gs->GetActiveTicket(); CT--;


    for(w=0;w<10;w++) {			// check to remove way or add it back in
    	if(WaysToPlay[CT][w]==way) {
        	remove=true;
            break;
        }
    }
    if(remove) {
//		if(way==20)
//	    	WaysToPlay[9]=0;
//	    else WaysToPlay[way-2]=0;	// scale 2-10 to elements 0-8
    	WaysToPlay[CT][w]=0;
    }
    else {
		if(way==20)
	    	WaysToPlay[CT][9]=20;
	    else WaysToPlay[CT][way-2]=way;	// scale 2-10 to elements 0-8
    }

	bDelAffectedWays = FALSE;

    CalcWayTkt();
}

int GetGroupItemNum(int tkt, int grp)
/*
** GetGroupNum()
** Helper function to retreieve the number of items from a specified group
*/
{
	int i;
	int retval = 0;

	for (i = 0; i < 20; i++)
	{
		if (gs->m_pGS.tkt[tkt].groups[grp][i] != 0)
			retval++;
		else
			break;
	}

	return retval;
}

void ProcExplodeTkt(int tkt)
/*
** ProcExplodeTkt()
** Called whenever a smaller ticket is "exploded" into a bigger one
*/
{

	if (nState == sPOW)
	/* In Proof-of-Win screen, only show specific ticket */
	{
			AT = tkt + 1;
			gs->SetActiveTicket(AT);

			if (POWtkt == -1)
			{
				sndPlaySound("sounds\\btnclick.wav",SND_ASYNC);
				POWlines = 0;
				POWpage = 0;
				POWpages = 0;
				POWbtn = 0;
                POWtkt = tkt;
			}
			else
			{
				if (tkt == POWtkt)
				{
					sndPlaySound("sounds\\btnclick.wav",SND_ASYNC);
					POWtkt = -1;
				}
			}
	}
	else
	{
		if (gs->m_pGS.credits)
		{
			sndPlaySound("sounds\\btnclick.wav",SND_ASYNC);

			nMsgScrollPos = 0; dwMsgScrollDelay = 0;
			AT = tkt + 1;
			gs->SetActiveTicket(AT);

			dfltbet = 100;
			lastbet = gs->m_pGS.tkt[tkt].bet;
			tvalue = gs->m_pGS.tkt[tkt].price;
			wtvalue = gs->m_pGS.tkt[tkt].price;

			if(gs->m_pGS.tkt[tkt].type==tQUICKPICK)
			{
                nState = sQUICKPICK;
			}
			else if(gs->m_pGS.tkt[tkt].type==tSTRAIGHT)
				nState = sSTRAIGHT;
			else if(gs->m_pGS.tkt[tkt].type==tWAYTKT)
			{
				CalcWayTkt();

				if (gs->m_pGS.tkt[tkt].groups[0][0] != 0)
					nState = sWAYPLAYIT;
				else
					nState = sWAYTKT;
			}
			else if(gs->m_pGS.tkt[tkt].type>=4 && gs->m_pGS.tkt[tkt].type <=7)
				nState = sSPECIALS;
			else if(gs->m_pGS.tkt[tkt].type >= 8)
			{
				if (gs->m_pGS.tkt[tkt].type == tVTROW)
					nState = sVTENTRY;
				else if (gs->m_pGS.tkt[tkt].type == tHZROW)
					nState = sHZENTRY;
				else
					nState = sHSENTRY;
					//nState = sHOUSETKT;
			}
			else
				nState = sBIGTKTUP;
		}
		else
		/* "Signal" the draw of credit message */
		{
			sndPlaySound("sounds\\horn.wav",SND_ASYNC);
			dwInsertMoneyMsg = GetTickCount();
		}
	}
}

bool CalcDraw(void)
{
	if (bDraw120)
	{
		int t;
		int testdraw[]= { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
		for(t=0;t<20;t++)
    		SeqDraw[t]=testdraw[t];
		return(true);
	}
	else
	{
		bool duped;
		int d;
		int i,ballnbr;

		memset(&SeqDraw,0,sizeof(SeqDraw));
		for(d=0;d<20;d++) {
    		duped=true;
			while(duped) {
           		duped=false;
           		ballnbr=get_ball();
				for(i=0;i<20;i++) {
               		if(SeqDraw[i]) {
                   		if(ballnbr == SeqDraw[i]) {
                       		duped=true;
							break;
						}
					}
					else {
                   		SeqDraw[i]=ballnbr;
						break;
					}
				}
	    		cycle_r64();
			}
		}
	}
    return(true);
}

DWORD RND(void)
{
	static int called=0;
    unsigned long rv;
    if(!called) {				//. init RNG seed
    	called=1;
        rnum[0]=1;
        rnum[1]=0xff;
    }
	for(int i=0;i<20;++i) 		//. iterate
    	rv=cycle_r64();
    return rv;					//. return RNG
}

DWORD cycle_r64(void)
{
	unsigned long h=rnum[0];	//. high dword
	unsigned long l=rnum[1];	//. low dword
    char hh=(char)high(h);		//. capture MSb of each dword (for Shift Overflow)
    char hl=(char)high(l);
    l<<=1;						//. left shift 64 bits
    h<<=1;
    h+=hl;
    if(hh) 						//. if high bit was clear, feedback tap positions
    	l^=TAP;
	rnum[0]=h;					//. store
	rnum[1]=l;
    return l;					//. return low 32 bits as random val
}

char* CalcDecimal(char comma,char len,char dec_pos,long value)
{
	static char str[30];
	char nstr[30];
	int s,x,y,z,negative=0,positions=0;

	memset(str,' ',30);
	str[29] = 0;
	memset(nstr,0,30);	/* clear target string			*/
	if(value < 0) {			/* negative 'value'					*/
		negative = 1;			/* set neg flag							*/
		value *= -1;			/* make it a positive value	*/
		positions += 1;		/* add 1 pos for '-' sign		*/
	}
	else if(value > 9999999999L) {				/* max value = 9,999,999,999	*/
		for(y = 0;y < len+dec_pos+1;y++)		/* just fill field with '*' 	*/
			str[y] = '+';
		str[y] = '\0';
		return(str);												/* caller must check					*/
	}
	if(comma) {															/* is a comma required ?			*/
		if(dec_pos) {													/* if decimal position req'd	*/
			if(value > 99999999L && dec_pos==2)
				positions += 2;										/* add 2 pos for decimal 			*/
			else if(value > 99999L && dec_pos==2)
				positions += 1;										/* add 1 pos for decimal			*/
			else if(value > 9999999L && dec_pos==1)
				positions += 2;										/* add 2 pos for decimal			*/
			else if(value > 9999L && dec_pos==1)
				positions += 1;										/* add 1 pos for decimal			*/
		}

		else {                                /* no decimal position req'd	*/
			if(value > 999999999L)
				positions += 3;                   /* add 3 for comma's					*/
			else if(value > 999999L)
				positions += 2;										/* add 2 for comma's					*/
			else if(value > 999L)
				positions += 1;										/* add 1 for comma						*/
		}
	}
	ltoa(value,str,10);           				/* convert 'value' to string	*/
	s = strlen(str);											/* get length of 'string'			*/
	if(s < 2 && dec_pos == 2) {           /* if decimal & strlen < 2		*/
		str[2] = '\0';
		str[1] = str[0];
		str[0] = '0';
		s = 2;
	}
	if( (s-dec_pos+positions) <= len) {		/* if enough room for req value	*/
		for(x = 0;x < (len-(s-dec_pos)-positions+negative);x++) /* add leading spaces */
			nstr[x] = ' ';
		if(s-dec_pos <= 3) {								/* no commas req'd 				*/
			for(y=0;y < s-dec_pos;x++,y++)		/* copy remaining values	*/
				nstr[x] = str[y];
			if(dec_pos)												/* if decimal required 		*/
				nstr[x++] = '.';
			for(z=0;z < dec_pos;x++,y++,z++){ /* copy balance of value	*/
				if(str[y] == ' ')
					str[y] = '0';
				nstr[x] = str[y];
			}
		}
		else if(s-dec_pos <= 6) { 					/* 1 comma req'd ?      	*/
			for(y=0;y < s-(3+dec_pos);x++,y++)/* copy remaining values	*/
				nstr[x] = str[y];
			if(comma)                         /* if comma required			*/
				nstr[x++] = ',';
			for(;y < s-dec_pos;x++,y++)
				nstr[x] = str[y];
			if(dec_pos)												/* if decimal required		*/
				nstr[x++] = '.';
			for(z=0;z < dec_pos;x++,y++,z++)	/* copy balance of value	*/
				nstr[x] = str[y];
		}
		else if(s-dec_pos <= 9) { 					/* 2 comma's req'd ?      */
			for(y=0;y < s-(6+dec_pos);x++,y++)/* copy remaining values	*/
				nstr[x] = str[y];
			if(comma)                         /* if comma required			*/
				nstr[x++] = ',';
			for(;y < s-(3+dec_pos);x++,y++) 	/* copy remaining values	*/
				nstr[x] = str[y];
			if(comma)                         /* if comma required			*/
				nstr[x++] = ',';
			for(;y < s-dec_pos;x++,y++)       /* copy remaining values	*/
				nstr[x] = str[y];
			if(dec_pos)												/* if decimal required		*/
				nstr[x++] = '.';
			for(z=0;z < dec_pos;x++,y++,z++)	/* copy balance of value	*/
				nstr[x] = str[y];
		}
		str[0] = '\0';
		strcpy(str,nstr);
	}
	else {															/* more chars than requested len	*/
		for(y = 0;y < len+dec_pos+1;y++)	/* just fill field with '*' 			*/
			str[y] = '*';
		str[y] = '\0';
		return(str);
	}
	if(negative) {
		if(str[0] != ' ') {
			str[0] = '-';
			for(y = 1;y < len+dec_pos+1;y++)	/* just fill field with '*' */
				str[y] = '*';
			str[y] = '\0';
			return(str);
		}
		memset(nstr,0,30);
		for(x=0,y=0;x < len+dec_pos+negative;x++,y++) {
			if(str[x] == ' ') {
				if(str[x+1] != ' ') { 	/* if next char != space */
					nstr[y++] = '-';  		/* put - sign */
					nstr[y] = str[++x];
				}
				else nstr[y] = str[x];	/* copy space */
			}
			else nstr[y] = str[x];
		}
		strcpy(str,nstr);
	}
	return (str);
}

long CalcWinningTkts(void)
{
	int t;
    long totalwin=0;

	wins = 0;
	gs->m_pGS.won=0;	// insure its cleared
	memset(&tktcatch,0,sizeof(tktcatch));
    Yahoo=false;
    for(t=0;t<4;t++)
	{
		gs->m_pGS.tkt[t].won = CalcWinTkt(t,true);
		if (gs->m_pGS.tkt[t].won)
		{
    		totalwin+= gs->m_pGS.tkt[t].won;
			wins++;
		}
	}
    return(totalwin);
}

long CalcWinTkt(int t,bool showit)
{
	int d,g,s;
	long win,twin=0;
   	if(gs->m_pGS.tkt[t].grpcount==1) {		// this tkt played ?
       	if(gs->m_pGS.tkt[t].rate==0) {		// regular tkt ?
		    for(g=0;g<gs->m_pGS.tkt[t].grpcount;g++) {
    			for(s=0;s<20;s++) {
                	for(d=0;d<20;d++) {
	     				if(SeqDraw[d]==gs->m_pGS.tkt[t].groups[g][s]) {
    	        			tktcatch[t]+=1;
                            break;
                        }
                    }
                }
            }
            if(tktcatch[t]==gs->m_pGS.tkt[t].picked)		// caught em all !
            	Yahoo=true;
        }
        else tktcatch[t]=ComputeSpecial(20,gs->m_pGS.tkt[t].rate);

       	win=PayTable(gs->m_pGS.tkt[t].picked,gs->m_pGS.tkt[t].rate,tktcatch[t],gs->m_pGS.tkt[t].bet);	// way,catch,bet

		if(win)
            twin+=win;
        if(showit)
			twin = twin + 0;
	       	//DrawTktCaught(t,true,win);
    }
   	else if(gs->m_pGS.tkt[t].grpcount>1) {		// this tkt playing groups ?
       	if(gs->m_pGS.tkt[t].rate==0) {		// regular tkt (better be) ?
           	win=ComputeWayTkt(t,true);
			char buf[256];
			sprintf(buf,"CalcWinTkt(), ticket %d won %d\n",t,win);
			OutputDebugString(buf);
			if(win)
                twin+=win;
            if(showit)
				twin = twin + 0;
	           	//DrawTktCaught(t,true,win);
        }
    }
    return(twin);
}

int ComputeSpecial(int drawnbr,int type)
{
//	char s[10];
	int b,g,katch=0;
	int top[]= { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40 };
	int left[]={ 1,2,3,4,5,11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45,51,52,53,54,55,61,62,63,64,65,71,72,73,74,75 };
	int edge[]={ 1,2,3,4,5,6,7,8,9,10,11,20,21,30,31,40,41,50,51,60,61,70,71,72,73,74,75,76,77,78,79,80 };
	int odd[]= { 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79 };

    switch(type) {
    	case 1:					// top/bottom (just calc top numbers)
           	for(b=0;b<drawnbr;b++) {
            	for(g=0;g<40;g++) {
	               	if(SeqDraw[b]==top[g])
	                   	katch++;	// incr catch count
                }
            }
        	break;
        case 2:   				// left/right (just calc left numbers)
           	for(b=0;b<drawnbr;b++) {
            	for(g=0;g<40;g++) {
	               	if(SeqDraw[b]==left[g])
	                   	katch++;	// incr catch count
                }
            }
        	break;
        case 3:   				// edge
           	for(b=0;b<drawnbr;b++) {
            	for(g=0;g<32;g++) {
	               	if(SeqDraw[b]==edge[g])
	                   	katch++;	// incr catch count
                }
            }
        	break;
        case 4:					// odd/even (just calc odd numbers)
           	for(b=0;b<drawnbr;b++) {
            	for(g=0;g<40;g++) {
	               	if(SeqDraw[b]==odd[g])
	                   	katch++;	// incr catch count
                }
            }
        	break;
        default:
        	break;
    }
	return(katch);
}

void ReCalcBetMeter(void)
{
	int t;

    gs->m_pGS.played=0;					// clear bet meter
    for(t=0;t<4;t++) {
       	if(gs->m_pGS.tkt[t].grpcount)		// this tkt played ?
			gs->m_pGS.played+=gs->m_pGS.tkt[t].price;
    }
}

HRESULT DrawPOW(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS, WAY_COMBO_STRUCT* info,
					  HBITMAP hBMPBlankPOW, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, int t, DWORD xPos, DWORD yPos)
/*
** DrawPOW()
** Draws the proof-of-win information on the passed surface
*/
{
	HRESULT hr;
    char winline[30];
	int x = 0,y=20;
    int j,k;
    long win,twin;
    FILE *fp;

    POWlines=0;
    memset(&tktcatch,0,sizeof(tktcatch));
	sprintf(winline,"   PROOF OF WIN TICKET %d",t+1);
//   	x=xpos[t];

	/* Draw blank POW */
	if( FAILED (hr = pSurface->DrawBitmap(hBMPBlankPOW, 0, 0, 204, 424)))
		return hr;

	sprintf(winline,"   PROOF OF WIN TICKET %d",t+1);
    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y);
	sprintf(winline,"    TICKET BET %s",CalcDecimal(true,5,2,(pGS->m_pGS.tkt[t].bet)));
    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y += 20);
    x-=4;
    win=CalcWinTkt(t,false);		// no pay, just calc ways caught
   	if(pGS->m_pGS.tkt[t].grpcount==1) {		// this straight tkt ?
       	if(pGS->m_pGS.tkt[t].rate==0) {		// regular tkt ?
        	sprintf(winline,"CAUGHT  CATCH  WAY    WIN");
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 20);
            if(win) {
	        	sprintf(winline,"   1     %2d     %2d%s",tktcatch[t],pGS->m_pGS.tkt[t].picked,CalcDecimal(true,6,2,(win)));
			    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 40);
            }
            else {
	        	sprintf(winline,"     NO WINNING CATCHES");
			    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 40);
            }
        }
        else if(pGS->m_pGS.tkt[t].rate==1) {
			sprintf(winline,"CAUGHT %2d ON TOP",tktcatch[t]);
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 40);
			sprintf(winline,"CAUGHT %2d ON BOTTOM",20-tktcatch[t]);
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 60);
        }
        else if(pGS->m_pGS.tkt[t].rate==2) {
			sprintf(winline,"CAUGHT %2d ON LEFT",tktcatch[t]);
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 40);
			sprintf(winline,"CAUGHT %2d ON RIGHT",20-tktcatch[t]);
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 60);
        }
        else if(pGS->m_pGS.tkt[t].rate==3) {
			sprintf(winline,"CAUGHT %2d OUT OF 20",tktcatch[t]);
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 40);
        }
        else if(pGS->m_pGS.tkt[t].rate==4) {
			sprintf(winline,"CAUGHT %2d ODD NUMBERS",tktcatch[t]);
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 40);
			sprintf(winline,"CAUGHT %2d EVEN NUMBERS",20-tktcatch[t]);
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 60); 
        }
    }
    else {	// way ticket
		if( (fp = fopen("pow.lst","w+b") ) == NULL) { // cant open
//        	sprintf(ErrMsg,"ERROR : UNABLE TO OPEN STATE FILE !");
//        	ShowErr();
         	return NULL;
      	}
       	sprintf(winline,"CAUGHT  CATCH  WAY    WIN");
	    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y += 20);
    	win=0;
	    for(j=0;j<10;j++) {
	    	if(pGS->m_pGS.tkt[t].ways[j]) {
			    k=1;
				while(info->ways[k]) {
	            	if(info->ways[k]==pGS->m_pGS.tkt[t].ways[j]) {
						if(info->counts[k]) {
			               	twin=(PayTable(pGS->m_pGS.tkt[t].ways[j],pGS->m_pGS.tkt[t].rate,info->katch[k],pGS->m_pGS.tkt[t].bet))*info->counts[k];	// way,catch,bet
                            win+=twin;
                            if(twin) {
					        	sprintf(winline,"  %2d     %2d     %2d%s",info->counts[k],info->katch[k],pGS->m_pGS.tkt[t].ways[j],CalcDecimal(true,6,2,(twin)));
//							    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y += 20);
						       	fwrite(&winline,sizeof(winline),1,fp);
                                POWlines+=1;
                            }
	                    }
	                }
				    k++;
	            }
	        }
	    }
        fclose(fp);
        if(!win) {
        	sprintf(winline,"     NO WINNING CATCHES");
		    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,y + 20);
        }
    }
    if(POWlines) {
    	POWpages=(POWlines/12)+1;
        //POWpage=0;
    	DrawCatch(ppDisplay,pSurface,pGS,hBMPBlankPOW,hBMPFont,hBMPNbrs,hBMPPunc,t,x);
    }
    x+=4;
    sprintf(winline,"     PAID $ %s",CalcDecimal(true,6,2,(win)));
    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,375);
	sprintf(winline,"  TOUCH TICKET TO CLEAR");
    DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,winline,x,395);

	(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);
	return S_OK;
}

void DrawCatch(CDisplay** ppDisplay, CSurface* pSurface, CGameState* pGS,
					  HBITMAP hBMPBlankPOW, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, int t, DWORD xpos)
{
	FILE *fp;
    bool atend=false;
    char caught[30];
    int y=60,rec,start;
    long pos;

//    DrawClearPage(xpos);
    start=POWpage*12;	// 12 lines/page
	if( (fp = fopen("pow.lst","r+b") ) == NULL) { // cant open
//        	sprintf(ErrMsg,"ERROR : UNABLE TO OPEN STATE FILE !");
//        	ShowErr();
	   	return;
    }
    pos=start*30;
	fseek(fp,pos,SEEK_SET);
    for(rec=0;rec<12;rec++) {
	   	if(fread(&caught,sizeof(caught),1,fp) != NULL) {
			DrawPOWHeader(ppDisplay,pSurface,hBMPFont,hBMPNbrs,hBMPPunc,caught,xpos,y += 20);
        }
        else {
			atend=true;
        	break;
        }
    }
    if(!atend) {	// read 1 more
	   	if(fread(&caught,sizeof(caught),1,fp) == NULL)
			atend=true;
    }
    fclose(fp);
    POWbtn=0;
    if(atend) {				// BACK only
    	if(POWpage>0) {     // if more than 1 page
	    	POWbtn='B';		// save visible btn
				pSurface->DrawBitmapPart(EKBtn[26],100,330,0,0,73,42);
        }
    }
    else {
    	if(POWpage==0) {    // MORE only
	    	POWbtn='M';		// save visible btn
			pSurface->DrawBitmapPart(EKBtn[25],25,330,0,0,73,42);
        }
        else {
	    	POWbtn='A';		// save visible btns

			/* Back & More buttons */
			pSurface->DrawBitmapPart(EKBtn[25],25,330,0,0,73,42);
			pSurface->DrawBitmapPart(EKBtn[26],100,330,0,0,73,42);

        }
    }    
}

void ProcBet(int b)
/*
** ProcBet()
** Does the processing for bet button presses
*/
{
	int CT = gs->GetActiveTicket(); CT--;

	if ((gs->m_pGS.tkt[CT].type == t190UD || gs->m_pGS.tkt[CT].type == t190BOX))
	{
		long tdfltbetbtns[4] = { 1,5,25,100 };

		if(lastbet==tdfltbetbtns[b-1])
        	gs->m_pGS.tkt[CT].bet+=tdfltbetbtns[b-1];
		else gs->m_pGS.tkt[CT].bet=tdfltbetbtns[b-1];
		lastbet=tdfltbetbtns[b-1];
		gs->m_pGS.tkt[CT].price=gs->m_pGS.tkt[CT].bet*gs->m_pGS.tkt[CT].combo;
	}
	else
	{
		if(nState==2||nState==10||nState==12||nState==20||nState==21||nState==32) {// 1 group tkt selected ?
    		if(lastbet==dfltbetbtns[b-1])
        		gs->m_pGS.tkt[CT].bet+=dfltbetbtns[b-1];// * combo ????
			else gs->m_pGS.tkt[CT].bet=dfltbetbtns[b-1];
	//			tktbets[CT]+=dfltbet[b-1];
	//        else tktbets[CT]=dfltbet[b-1];
			lastbet=dfltbetbtns[b-1];
			gs->m_pGS.tkt[CT].price=gs->m_pGS.tkt[CT].bet*gs->m_pGS.tkt[CT].combo;
		}
		else if(nState==31||nState==32||nState==33) {	// multiple groups selected ?
			if(lastbet==dfltbetbtns[b-1])
        		gs->m_pGS.tkt[CT].bet+=dfltbetbtns[b-1];
			else gs->m_pGS.tkt[CT].bet=dfltbetbtns[b-1];
			lastbet=dfltbetbtns[b-1];
			gs->m_pGS.tkt[CT].price=gs->m_pGS.tkt[CT].bet*gs->m_pGS.tkt[CT].combo;
		}
		else if(nState==sWAYENTRY||nState==sWAYPLAYIT) {
			if(lastbet==dfltbetbtns[b-1])
        		gs->m_pGS.tkt[CT].bet+=dfltbetbtns[b-1];
			else gs->m_pGS.tkt[CT].bet=dfltbetbtns[b-1];
			lastbet=dfltbetbtns[b-1];
			gs->m_pGS.tkt[CT].price=gs->m_pGS.tkt[CT].bet*gs->m_pGS.tkt[CT].combo;
		}
	}
}

HRESULT DoScrollingWork(CDisplay** ppDisplay, CSurface* pSurface, HBITMAP hBMPFont, HBITMAP hBMPNbrs, HBITMAP hBMPPunc, TCHAR* strText, 
						DWORD xPos, DWORD yPos )
/* 
** DoScrollingWork()
** This function takes care of all scrolling messages, and makes them happen
*/
{
	HRESULT hr = NULL;
	int pixlen = CalcPixLength(strText), len = strlen(strText), xoffset = 205 - (4 * len);

	if( FAILED (hr = pSurface->DrawBitmap(MsgCntr, 0, 0, 418, 25)))
		return hr;

	if (len <= 56)
	{
		if (dwMsgScrollDelay == 0)
		{
			dwMsgScrollDelay = GetTickCount();

			if (nMsgScrollPos == 0)
				dwMsgScrollDelay += OPT_MSGSTATIONARY + (OPT_MSGSTATIONARY * (OPT_MSGBLINKTIMES * 2));
		}
		else
		{
			if ((dwMsgScrollDelay + OPT_MSGSCROLLDELAY) <= GetTickCount())
			/* Bump X pos of message higher */
			{
				nMsgScrollPos += OPT_MSGSCROLLADVANCE;

				if (nMsgScrollPos > (395 - xoffset))
				{
					nMsgScrollPos = 0;
					bFlag = TRUE;
				}

				dwMsgScrollDelay = 0;
			}
		}

		if (nMsgScrollPos == 0)
		/* Blink here */
		{
			int blink;
			//int blink = dwMsgScrollDelay - GetTickCount();

			if (dwMsgScrollDelay)
				blink = dwMsgScrollDelay - GetTickCount();
			else
				blink = 0;

			if (blink > 0 && blink < OPT_MSGSTATIONARY + (OPT_MSGSTATIONARY * (OPT_MSGBLINKTIMES * 2)))
			{
				if ((blink / OPT_MSGSTATIONARY) % 2)
				/* Blink out message */
				{
					if (!bFlag)
						DrawMessageCenter(ppDisplay,pSurface,MsgCntr,xPos,yPos);
					else
						bFlag = FALSE;
				}
				else
					DrawMsgCntrTextScroll(ppDisplay, pSurface, hBMPFont, hBMPNbrs, hBMPPunc, strText, xPos, xoffset ,yPos);
			}
			else
				DrawMsgCntrTextScroll(ppDisplay, pSurface, hBMPFont, hBMPNbrs, hBMPPunc, strText, xPos, xoffset ,yPos);
		}
		else
		{
			DrawMsgCntrTextScroll(ppDisplay, pSurface, hBMPFont, hBMPNbrs, hBMPPunc, strText, xPos, 395 - nMsgScrollPos,yPos);
		}
	}
	else
	/* Message is too big to fit in window */
	{
		if (dwMsgScrollDelay == 0)
		{
			dwMsgScrollDelay = GetTickCount();

			if (nMsgScrollPos == 0)
				dwMsgScrollDelay += OPT_MSGSTATIONARY + (OPT_MSGSTATIONARY * (OPT_MSGBLINKTIMES * 2));
		}
		else
		{
			if ((dwMsgScrollDelay + OPT_MSGSCROLLDELAY) <= GetTickCount())
			/* Bump X pos of message higher */
			{
				nMsgScrollPos += OPT_MSGSCROLLADVANCE;

				if (nMsgScrollPos > pixlen)
				{
					nMsgScrollPos = 0;
					bFlag = TRUE;
				}

				dwMsgScrollDelay = 0;
			}
		}

		if (nMsgScrollPos == 0)
		/* Blink here */
		{
			int blink;
			//int blink = dwMsgScrollDelay - GetTickCount();

			if (dwMsgScrollDelay)
				blink = dwMsgScrollDelay - GetTickCount();
			else
				blink = 0;

			if (blink > 0 && blink < OPT_MSGSTATIONARY + (OPT_MSGSTATIONARY * (OPT_MSGBLINKTIMES * 2)))
			{
				if ((blink / OPT_MSGSTATIONARY) % 2)
				/* Blink out message */
				{
					if (!bFlag)
						DrawMessageCenter(ppDisplay,pSurface,MsgCntr,xPos,yPos);
					else
						bFlag = FALSE;
				}
				else
					DrawMsgCntrTextScrollL(ppDisplay, pSurface, hBMPFont, hBMPNbrs, hBMPPunc, strText, xPos, nMsgScrollPos,yPos);
			}
			else
				DrawMsgCntrTextScrollL(ppDisplay, pSurface, hBMPFont, hBMPNbrs, hBMPPunc, strText, xPos, nMsgScrollPos ,yPos);
		}
		else
		{
			DrawMsgCntrTextScrollL(ppDisplay, pSurface, hBMPFont, hBMPNbrs, hBMPPunc, strText, xPos, nMsgScrollPos,yPos);
		}

	}

	//(*ppDisplay)->Blt(xPos,yPos,pSurface,NULL);
	return S_OK;
}

unsigned int CalcPixLength(char* string)
/*
** CalcPixLength()
** Help function used to determine pixel-length of specified string
*/
{
	int retval = 0, count, letter;

	for (count = 0; string[count] != 0; count++)
	{
		letter = string[count];

		if ((letter >= 'A' && letter <= 'Z') || (letter >= '0' && letter <= '9') || letter == ' ')
			retval += 8;
		else if (letter == '.' || letter == ',' || letter == '\"')
			retval += 4;
	}

	return retval;
}

BOOL WriteABuffer(HANDLE hComm, char * lpBuf, DWORD dwToWrite)
{
   OVERLAPPED osWrite = {0};
   DWORD dwWritten;
   DWORD dwRes;
   BOOL fRes;

   // Create this write operation's OVERLAPPED structure's hEvent.
   osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   if (osWrite.hEvent == NULL)
      // error creating overlapped event handle
      return FALSE;

   // Issue write.
   if (!WriteFile(hComm, lpBuf, dwToWrite, &dwWritten, &osWrite)) {
      if (GetLastError() != ERROR_IO_PENDING) { 
         // WriteFile failed, but isn't delayed. Report error and abort.
         fRes = FALSE;
      }
      else
	  {
         // Write is pending.
         dwRes = WaitForSingleObject(osWrite.hEvent, INFINITE);
         switch(dwRes)
         {
            // OVERLAPPED structure's event has been signaled. 
            case WAIT_OBJECT_0:
                 if (!GetOverlappedResult(hComm, &osWrite, &dwWritten, FALSE))
                       fRes = FALSE;
                 else
                  // Write operation completed successfully.
                  fRes = TRUE;
                 break;
            
            default:
                 // An error has occurred in WaitForSingleObject.
                 // This usually indicates a problem with the
                // OVERLAPPED structure's event handle.
                 fRes = FALSE;
                 break;
         }
      }
   }
   else
      // WriteFile completed immediately.
      fRes = TRUE;

   CloseHandle(osWrite.hEvent);
   return fRes;
}

void PlayFileInit(void)
{

    // Create the filter graph manager.
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, 
        IID_IGraphBuilder, (void **)&pGraph);
    pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
    pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVidWin);
	pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
	pGraph->QueryInterface(IID_IMediaPosition, (void **)&pPos);

    // Build the graph.
	pGraph->RenderFile(L"attract.avi", NULL);

    //Set the video window.
    pVidWin->put_Owner((OAHWND)gs->GetHWnd());
	pVidWin->put_MessageDrain((OAHWND)gs->GetHWnd());
    pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	pVidWin->put_Caption(L"Touch the screen to play Elite Keno!");

    RECT grc;
    GetClientRect(gs->GetHWnd(), &grc);
    pVidWin->SetWindowPosition(0, 0, grc.right, grc.bottom);
}

void AnimationThread(void* nothing)
/*
** AnimationThread()
** This function allows smoother animation of scrolling
*/
{
	
}
