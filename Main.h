//----------------------------------------------------------------------------------------------
//
// Main.h : Global Defines for the Elite Keno Slot Machine Application.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, & Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <basetsd.h>
#include <ddraw.h>
#include <mmsystem.h>
#include "resource.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//#define PRODUCTION

/* Game options */
#define OPT_WAYBLINKDELAY				500
#define OPT_BALLDROPADVANCE			2
#define OPT_BALLDROPDELAY				100
#define OPT_BALLBLOWERADVANCE	1
#define OPT_CREDITADDS						5
#define OPT_MSGSCROLLDELAY			0
#define OPT_MSGSCROLLADVANCE		3
#define OPT_MSGSTATIONARY				1500
#define OPT_MSGBLINKTIMES				0
#define OPT_CREDITDELAY				125
#define OPT_USEBIGDRAW			0
#define OPT_CREATENEWPAYTABLE	0

/* Other game defines */
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      16
#define SCREEN_COLORKEY	999

#define DRAWDELAY	600

#define BW			68		// button width in pixels
#define BH			34		// button heighth

#define STX			0x02
#define ETX			0x03
#define ESC			0x1b
#define F1			0x0070	// Func Key 1
#define F2			0x0071
#define F3			0x0072
#define F4			0x0073
#define F5			0x0074
#define F6			0x0075
#define F7			0x0076
#define F8			0x0077
#define F9			0x0078

//---------------------------------------------------------------------------
// State defines
#define sIDLE		0
#define sBIGTKTUP	1
#define sSTRAIGHT	2
#define sATTRACT	3
#define sQUICKPICK	10
#define sQPENTRY	12
#define sSPECIALS	20
#define sSPENTRY	21
#define sHOUSETKT	30
#define sHSENTRY	31
#define sHZENTRY	32
#define sVTENTRY	33
#define sWAYTKT		40
#define sWAYENTRY	41
#define sWAYPLAYIT	42
#define sPAYTABLE1	50
#define sPAYTABLE2	51
#define sHELPSCRN	 60
#define sDUMPBALLS	103
#define sPOW		104

//---------------------------------------------------------------------------
// Ticket TYPE defines (used in modifying ticket info)
#define	tQUICKPICK	1
#define tSTRAIGHT	2
#define tWAYTKT		3
#define tTOPBOT		4
#define tLEFTRT		5
#define tEDGE		6
#define tODDEVEN	7
#define t190UD		8
#define t190BOX		9
#define tHZROW		10
#define tVTROW		11

//---------------------------------------------------------------------------
// Button defines
#define SHOW_NORMAL		1
#define SHOW_HILITE		2

// MARS bill validator
#define STANDARD	0x20
// bill validator states
#define IDLING		0x01
#define ESCROWED	0x04
#define STACKED		0x10

#define POLLBILLV	1000	// poll 1 second ???

// bill bit values
#define Denom1		0x08	// $   1.00
#define Denom2		0x10	// $   2.00
#define Denom3		0x18	// $   5.00
#define Denom4		0x20	// $  10.00
#define Denom5		0x28	// $  20.00
#define Denom6		0x30	// $  50.00
#define Denom7		0x38	// $ 100.00


//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Slot Machine Graphics
//-----------------------------------------------------------------------------

static HBITMAP Game;			// offscreen main screen
static HBITMAP EKBase;			// Elite Keno Background Image used as a foundation for every screen
static HBITMAP SaveGame;		// saved copy of game screen
static HBITMAP SaveGame1;		// saved copy of game screen (used in paytable routine)
static HBITMAP SaveGame2;		// saved copy of game screen (used in proof of win routine)
static HBITMAP EKLogo;			// Elite Keno logo
static HBITMAP Frame162x65;		// Small 162x65 Window Frame
static HBITMAP Frame162x141;	// Small 162x141 Window Frame
static HBITMAP Frame164x324;	// Medium 164x324 Window Frame
static HBITMAP Frame164x424;	// Small 164x424 Window Frame
static HBITMAP Frame204x424;	// Small 204x424 Window Frame
static HBITMAP Images[4];		// SPECIAL images (top/bot,...)
static HBITMAP TouchTkt;		// "TOUCH A TICKET"
static HBITMAP TouchOne;		// "TOUCH ONE"
static HBITMAP GameStat;		// "GAME OPEN"
static HBITMAP BlankBtn;		// blank button
static HBITMAP EKBtn[50];		// Button array
static HBITMAP BtnMask;			// transparency mask
static HBITMAP BetMtr;			// BET meter
static HBITMAP WonMtr;			// WON meter
static HBITMAP CreditMtr;		// CREDIT meter
static HBITMAP SmallTkt;		// small KENO tickets (4 ea)
static HBITMAP BlankTkt;		// black'd out small KENO ticket
static HBITMAP LargeTkt;		// large KENO ticket
static HBITMAP LargeSpot[81];	// large KENO ticket spots (X over 1-80)
static HBITMAP SpclLetr;		// Specials lettering ('T','B',...)
static HBITMAP BigOval;			// red oval in large ticket
static HBITMAP SmlOval;			// red oval in small ticket
static HBITMAP TktHdrs[4];		// top of each small ticket
static HBITMAP MtrPunc;			// METER font ( .,)
static HBITMAP MtrNbrs;			// METER font (0-9 $)
static HBITMAP MsgCntr;			// Message Center
static HBITMAP OrLabel;			//
static HBITMAP ChgBet;			// "CHANGE BET"
static HBITMAP BigHdr;			// large ticket header rectangle
static HBITMAP BigHdrFont;		// large ticket header (A-Z)
static HBITMAP BigHdrNbrs;		// large ticket header (0-9 $)
static HBITMAP BigBetPunc;		// large ticket price ( .,)
static HBITMAP BigBetNbrs;		// large ticket price (0-9 $)
static HBITMAP SmlHdrFont;		// small ticket header (A-Z)
static HBITMAP SmlHdrNbrs;		// small ticket header (0-9 $)
static HBITMAP SmlHdrPunc;		// small ticket header ( .,)
static HBITMAP SmlBetPunc;		// small ticket price ( .,)
static HBITMAP SmlBetNbrs;		// small ticket price (0-9 $)
static HBITMAP Blower;			// 2 long tubes (shooter)
static HBITMAP Balls;			// 80 numbered ping pong balls (vertical .bmp)
static HBITMAP Ball;			// 1 Keno ball
static HBITMAP buf;				// offscreen buffer
static HBITMAP Blowback;		// copy of Blower image
static HBITMAP Ballmask;		// transparency mask for Keno balls
static HBITMAP ClearBtn;		// CLEAR button (different size)
static HBITMAP SmallNbr[81];	// group letters in small tickets
static HBITMAP SmallLtr;		// SPECIALS group letter in small tickets
static HBITMAP PayTbl1;			// regular 1-10 & 20 spot paytable
static HBITMAP PayTbl2;			// specials paytable
static HBITMAP BigGrpLtr;		// a-t group letters (large ticket)
static HBITMAP SmlGrpLtr;		// a-t group letters (small ticket)
static HBITMAP WayNbrs;			// small red #'s used in way ticket entry (or countdown clock)
static HBITMAP WayNbrsI;		// (inverted)
static HBITMAP MsgFont;			// Message font(A-Z)
static HBITMAP MsgNbrs;			// Message numbers(0-9)
static HBITMAP MsgPunc;			// Message punctuation
static HBITMAP SmlBlankHdr;		// Blank ticket header
static HBITMAP EKBtnPenny;		// Penny button
/* Help screens */
static HBITMAP HelpBG;			// Help background
static HBITMAP HelpIdle;		// Idle help screen
static HBITMAP HelpQP;			// Quick pick help
static HBITMAP HelpSpecials;		// Special ticket help
static HBITMAP HelpWay;			// Way ticket help
static HBITMAP HelpHouse;		// House help screen

struct TICKET_STRUCT
{
	bool	played;
    bool	replay;
    bool	paidfor;		// price deducted from credits
    int		type;			// type of tkt used in replay
    int		grpcount;
	int		groups[21][21];
    int		combo;
	int		picked;			// current # of selected per group
	int		caught[1];		// # of entries caught
    int		ways[11];
    int		rate;
    long	bet;			// per combo
	long	price;			// total price of ticket
	long	won;			// amount won for ticket
    long	spares[4];
};
extern struct TICKET_STRUCT			tkts[4];

struct METER_STRUCT
{
	long	coin_in;
	long	coin_out;
	long	jackpots;
	long	handle_pulls;
};
extern struct METER_STRUCT			slot_meters;	

struct GAME_STATE_STRUCT
{
	int								basex;
    int 							basey;
	struct TICKET_STRUCT			tkt[4];
	long							played;
    long							won;
	long							credits;
    char							port[6];
    struct METER_STRUCT				meters;
};
extern struct GAME_STATE_STRUCT		st;

struct RATE_TABLE_STRUCT
{
	char			rate;
	char			name[11];
	long			price;
	long 			balls;
	long 			draw;
	long			spot1[2];
	long			spot2[3];
	long			spot3[4];
	long			spot4[5];
	long			spot5[6];
	long			spot6[7];
	long			spot7[8];
	long			spot8[9];
	long			spot9[10];
	long			spot10[11];
	long			spot11[12];
	long			spot12[13];
	long			spot13[14];
	long			spot14[15];
	long			spot15[16];
	long			spot16[17];
	long			spot17[18];
	long			spot18[19];
	long			spot19[20];
	long			spot20[21];
};
extern struct RATE_TABLE_STRUCT		tbl;

struct SPECIAL_TABLE_STRUCT
{
	char			rate;
	char			name[11];
	long			price;
	long 			balls;
	long 			draw;
	long			spot20[21];
};
extern struct SPECIAL_TABLE_STRUCT	spcltbl[5];

struct WAY_COMBO_STRUCT
{
	unsigned int	combo[21];
	int				ways[256];
	unsigned int	counts[256];
	int				eagrp[21];
	int				hits[21];
	int				katch[256];
	unsigned int ocounts[256];
};

struct PRINTER_COMMAND_STRUCT
{
    unsigned char	opcode1;
	unsigned char	opcode2;
	char			params[20];
};

struct SCROLLING_CONTROL_STRUCT
{
	char *msg;
	unsigned short x;
	unsigned short y;
};

extern bool CloseGame;
extern bool Touched;			// set if screen touched
extern bool MessageUp;			// message center visible
extern bool Yahoo;
extern char *btnarray[];
extern char *image[];
extern char *messages[];
extern char *bigtkthdr[];
extern char *errors[];
extern char SpecWay[4][11];		// english special tickets
extern int State;
extern int SaveState;
extern int AT;
extern int Hilite;
extern int LeaveItOn;			// hilite button but leave it on
extern int tktways[4];
extern int tktcatch[8];
extern int SeqDraw[80];
extern int Error;
extern long dfltbetbtns[4];
extern long dfltbet;
extern long lastbet;
extern unsigned long tick;
extern int POWlines;
extern int POWpages;
extern int POWpage;
extern int POWbtn;		// MORE or BACK or both visible
extern int POWtkt;

//extern int ways[256];
//extern int katch[256];
//extern unsigned int counts[256];
extern int WaysToPlay[4][11];
extern unsigned long cycle_r64(void);
extern unsigned long RND(void);

//extern void UpdateGameState(void);

#endif

