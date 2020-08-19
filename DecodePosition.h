//----------------------------------------------------------------------------------------------
//
// DecodePosition.h : Global Defines for the DecodePosition Methods of the Elite Keno Slot 
// Machine Application.
//
// Desc: This application source file is protected under the copyright laws of the  
//       United States, and is intended for the exclusive use of the EliteKeno Slot
//		 Machine Application.
//
// Copyright (c) 2002 Keno Products Group, & Advanced Games Technology, Inc. All rights reserved.
//
//----------------------------------------------------------------------------------------------
#ifndef DECODEPOSITION_H
#define DECODEPOSITION_H


#include "main.h"

//---------------------------------------------------------------------------

HRESULT DecodePosition(int xPos, int yPos, int nState);
extern long CkTkt(int tx, int ty);
extern bool CkVer(int tx, int ty);
extern bool CkAddCredits(int tx, int ty);
extern long CkTktFunc(int tx, int ty);
extern long CkBigTktFunc(int tx, int ty);
extern long CkQP(int tx, int ty);
extern long CkStraightStatus(int tx, int ty);
extern long CkStatus(int tx, int ty);
extern long CkWay(int tx, int ty);
extern long CkSP(int tx, int ty);
extern long CkHouse(int tx, int ty);
extern bool CkMore(int tx, int ty);
extern bool CkBack(int tx, int ty);
extern long CkPOWbtns(int tx, int ty);
extern long GetBigSpot(int tx, int ty);
extern long CkWon(int tx, int ty);


#endif // DECODEPOSITION_H
