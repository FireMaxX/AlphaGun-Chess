/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Super Agent Max :)                                        */
/* Date: 01/26/2017                                                  */
/*                                                                   */
/* Type.h: Set up data structure                                     */
/*                                                                   */
/*********************************************************************/
#ifndef TYPE_H
#define TYPE_H

typedef struct {
	int color;		/* piece color, 0=black, 1=white  */
	int status;		/* 0=initial position, 1=moved,  2=captured */
	char name;		/* piece name */
	int validsteps; /* AI reference value */
	int value;		/* Value accquired when captured */
	int number;		/* Pieces Index */
} PIECE;

typedef struct{ 
	int color;		/* 0=black, 1=white */
	PIECE *p;		/* pointer to single piece */
} SQUARE;


typedef struct {
	int x;				/* x coordinate */
	int y;				/* y coordinate */
} DIRECTION;

/* For Logfile */
typedef struct LogList LIST;
typedef struct LogEntry ENTRY;
struct LogList {
	int number;
	ENTRY *First;
	ENTRY *Last;
};
struct LogEntry{
	int index;
	ENTRY *Prev;
	ENTRY *Next;
	DIRECTION Tar;
	DIRECTION Des;
	int condition;
} ;

LIST *lf;				/* Pointer to Logfile List */
SQUARE board[8][8];		/* 8x8 array to represent the board */
PIECE pie[32];			/* 32 pieces */
PIECE *grave[2][16];		/* A set of pointers to captured pieces */
/*DIRECTION legalmove[64];	 A coordinate array to save all possible */

#endif
