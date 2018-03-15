/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Yijian Wang                                                   */
/* Date: 01/29/2017                                                  */
/*                                                                   */
/* Piece.h: Set up piece structure                                   */
/*                                                                   */
/*********************************************************************/

#ifndef PIECE_H
#define PIECE_H

#include "Type.h"
#include "Constant.h"

/* Find a specific piece, return coordinate, return (9,9) if find nothing. */
DIRECTION Find_Piece(SQUARE board[][8], int color, int number);

PIECE *Create_Piece(char name, int color, int status, int value, int number);

void Delete_Piece(PIECE *p);

void SetPieces(SQUARE board[][8]);

/* Check if it is an available movement for a Piece */
int PieceLegalMove(SQUARE board[][8], int a, int b, int x, int y);



#endif
