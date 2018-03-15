/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Super Agent Max :)                                        */
/* Date: 01/29/2017                                                  */
/*                                                                   */
/* Piece.c: Piece Operation                                          */
/*                                                                   */
/*********************************************************************/
/* Modified by yw */
/* Add Find_Piece Max */
#include <stdlib.h>
#include "Piece.h"
#include "Constant.h"
#include "Board.h"
#include <stdio.h>
#include <assert.h>

DIRECTION Find_Piece(SQUARE board[][8], int color, int number) {
	int i, j;
	DIRECTION coordinate;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j].p!=NULL){
				if ((board[i][j].p->color == color) &&
					(board[i][j].p->number == number)) {
					coordinate.x = i;
					coordinate.y = j;
			}
		}
		}
	} /* End of i loop */

	return coordinate;
}

PIECE *Create_Piece(char name, int color, int status, int value, int number) {
	PIECE *p = malloc(sizeof(PIECE));
	assert(p);
	p->name = name;
	p->color = color;      /* 0=black, 1= white */
	p->status = status;	/* 0 =initialized, 1= moved and survived, 2= dead */
	p->validsteps = 0;	/* AI reference value */
	p->value = value;	/* Value accquired when captured */
	p->number = number; /* 0-15 */
	return p;
}


void Delete_Piece(PIECE *p){
	assert(p);
	free(p);
	p = NULL;

}

void SetPieces(SQUARE board[][8]){
	int x,y;
	PIECE *wP, *wR, *wB, *wN, *wQ, *wK, *bP, *bR, *bB, *bN, *bQ, *bK;
	
	for (x = 0; x <= 7; x++) {
	    for (y = 0; y <= 7; y++) {
		if (y == 1) {
			wP = Create_Piece('P', 1, 0, Pawnvalue, x + 8);
			board[x][y].p = wP;
		}
		else if (y == 6) {
			bP = Create_Piece('P', 0, 0, Pawnvalue, 15 - x);
			board[x][y].p = bP;
		}
		else if (y == 0) {
			if (x == 0 || x == 7) {
				wR = Create_Piece('R', 1, 0, Rookvalue, x);
				board[x][y].p = wR;
			}
			if (x == 1 || x == 6) {
				wN = Create_Piece('N', 1, 0, Knightvalue, x);
				board[x][y].p = wN;
			}
			if (x == 2 || x == 5) {
				wB = Create_Piece('B', 1, 0, Bishopvalue, x);
				board[x][y].p = wB;
			}
			if (x == 3) {
				wQ = Create_Piece('Q', 1, 0, Queenvalue, x);
				board[x][y].p = wQ;
			}
			if (x == 4) {
				wK = Create_Piece('K', 1, 0, Kingvalue, x);
				board[x][y].p = wK;
			}

		}
		else if (y == 7) {
			if (x == 0 || x == 7) {
				bR = Create_Piece('R', 0, 0, Rookvalue, 7 - x);
				board[x][y].p = bR;
			}
			if (x == 1 || x == 6) {
				bN = Create_Piece('N', 0, 0, Knightvalue, 7 - x);
				board[x][y].p = bN;
			}
			if (x == 2 || x == 5) {
				bB = Create_Piece('B', 0, 0, Bishopvalue, 7 - x);
				board[x][y].p = bB;
			}
			if (x == 3) {
				bQ = Create_Piece('Q', 0, 0, Queenvalue, x);
				board[x][y].p = bQ;
			}
			if (x == 4) {
				bK = Create_Piece('K', 0, 0, Kingvalue, x);
				board[x][y].p = bK;
			}

		}
}
}
}

/* Check if it is an available movement for a Piece */
int PieceLegalMove(SQUARE board[][8],int a, int b, int x, int y){
	PIECE *p;
	p=board[a][b].p;
	assert(p);
	int cl=p->color;
	PIECE *pmove;
	pmove=board[x][y].p;
	int mcl = 3;
  int status;
  status = p->status;
	if (pmove != NULL) {

		mcl = pmove->color;
	}


	switch(p->name){			/* 0= not available, 1= available£¬ 2= castling */
		case 'K':

		if (((x - a <= 1) && (x - a >= -1)) && ((y - b <= 1) && (y - b >= -1))) {
			return 1;
		}
/*
		else if ((x == a - 2) && (y == b) && (status == 0)) {
      Rleft=board[a-4][b].p;
			if (Rleft != NULL) {
				sleft = Rleft->status;
			}
			PIECE *lpn, *lpb, *pq;
			lpn = board[a - 3][b].p;
			lpb = board[a - 2][b].p;
			pq = board[a - 1][b].p;
			if ((lpn == NULL) && (lpb == NULL) && (pq == NULL) && (sleft == 0)) {
				return 2;
			}
			else {
				return 0;
			}
		}
		else if ((x == a + 2) && (y == b) && (status == 0)) {
      Rright=board[a+3][b].p;
			if (Rright != NULL) {
				sright = Rright->status;
			}
			PIECE *rpn, *rpb;
			rpn = board[a + 2][b].p;
			rpb = board[a + 1][b].p;
			if ((rpn == NULL) && (rpb == NULL) && (sright == 0)) {
				return 2;
			}
			else {
				return 0;
			}
		} */
		else {
			return 0;
		}

		case 'Q':
		if(((x==a)||(y==b))||((x-a==y-b)||(x-a==b-y))){
			return 1;}
		else{
			return 0;}

		case 'B':
		if((x-a==y-b)||(x-a==b-y)){
			return 1;}
		else{
			return 0;}

		case 'N':
		if((((x-a==1)||(a-x==1))&&((y-b==2)||(b-y==2)))|| (((x - a == 2) || (a - x == 2)) && ((y - b == 1) || (b - y == 1)))){
			return 1;}
		else{
			return 0;}

		case 'R':
		if((x==a)||(y==b)){
			return 1;}
		else{
			return 0;}

		case 'P':   
			if (cl == 1) {
      				if(status == 0){
        				if ((y == b+2)&&(x == a))
          					return 1;
        				if ((y == b+1)&&(x == a))
          					return 1;
					if ((y == b + 1) && ((x == a + 1) || (x == a - 1)) && (mcl == 0))
						return 1;
      				}
      				else{
					if (((y == b + 1) && (x == a)) || ((y == b + 1) && ((x == a + 1) || (x == a - 1)) && (mcl == 0)))
						{return 1;}
					else {
						return 0;
					}
        			}
			}
			else  {
      				if(status == 0){
        				if ((y == b-2)&&(x == a))
          					{return 1;}
        				if ((y == b-1)&&(x == a))
          					{return 1;}
					if ((y == b - 1) && ((x == a + 1) || (x == a - 1)) && (mcl == 1))
						{return 1;}
    				}
      				else{
			  		if (((y == b - 1) && (x == a)) || ((y == b - 1) && ((x == a + 1) || (x == a - 1)) && (mcl == 1))) 
  						{return 1;}
  					else	{return 0;}
				}
    			}
			break;
		default: return 0;

		
}
	return 0;
}
		
	
	
