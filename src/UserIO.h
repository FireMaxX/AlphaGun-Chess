/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Xiaoyan Yang                                              */
/* Date: 01/26/2017                                                  */
/*                                                                   */
/* UserIO.h: Set up structure for I/O                                */
/*                                                                   */
/*********************************************************************/

#ifndef USERIO_H
#define USERIO_H

#include "Constant.h"
#include "Type.h"

/* Save & Load Function*/
int Saveboard(char outFileName[32], SQUARE board[][8], PIECE *grave[2][16], LIST *lf); /* 0=Success 1=Error */
int Loadboard(char inFileName[32], SQUARE board[][8], PIECE *grave[2][16]);

/* Log File, record every move */
int NewLogFile(DIRECTION tar, DIRECTION des, int condition, LIST *lf);
int Undo(LIST *lf, SQUARE board[][8], PIECE *grave[][16]);
int DelLogFile(LIST *lf);

/* Translate user's move instruction into digitalized coordinate */
DIRECTION getPosition(char userinput[32]);

/* Create a new game */
void Reset(SQUARE board[][8], PIECE *grave[][16], LIST *lf);

#endif
