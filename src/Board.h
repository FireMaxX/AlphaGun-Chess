/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Yanjie Xu :p                                              */
/* Date: 01/26/2017                                                  */
/*                                                                   */
/* Type.h: Set up data structure                                     */
/*                                                                   */
/*********************************************************************/
/* Change BOARD -> SQUARE ,Max*/

#ifndef BOARD_H
#define BOARD_H

#include "Type.h"
#include "Piece.h"

int Set_Board(SQUARE Board[][8]);
int Delete_Board(SQUARE Board[][8]);
int Delete_Grave(PIECE *Grave[][16]);

#endif 
