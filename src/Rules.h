/*Rules.h*/
/*Created by Yan Zhang 1/26/2017*/

#include "Constant.h"
#include "Type.h"
#include "Board.h"
#include "Piece.h"



/*Move piece*/
/*Input 2 positions, return 0, 1, 2, 3 (or 4): 0= cannot move; 1= move to a blank square; 2= capture; 3=king captured, (4=castling)*/
int Move(SQUARE board[][8], int tar_x, int tar_y,int des_x,int des_y,PIECE *grave[][16]);

/*Input the position and the color of the King, return 1 if check, 0 if King is safe*/
int Check(SQUARE board[][8],int color, int x,int y);

/*LegalMove*/
int LegalMove(SQUARE board[][8], int tar_x,int tar_y, int des_x, int des_y);







