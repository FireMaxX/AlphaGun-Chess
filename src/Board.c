/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Yanjie Xu and Xiaoyan Yang                                */
/* Date: 01/26/2017                                                  */
/*                                                                   */
/* Board.c: Set up chess game environment                            */
/*                                                                   */
/*********************************************************************/
#include "Type.h"
#include <stdio.h>
#include "Board.h"
#include "Piece.h"
#include <assert.h>
int Set_Board(SQUARE Board[][8]){
	int i,j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++){
			Board[i][j].p = NULL;
			if ((i + j) % 2 == 0)
				Board[i][j].color = 0;  /*0 for black and 1 for white*/
			else 
				Board[i][j].color = 1;
		}
	return 0;
}


int Delete_Board(SQUARE Board[][8]){
	int i,j;
	assert(Board);
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
      			if(Board[i][j].p != NULL){
				Delete_Piece(Board[i][j].p);
				Board[i][j].p = NULL;}
		}
	}
	return	0;
}
int Delete_Grave (PIECE *Grave[2][16]){
	int i,j;
	for (i = 0;i<2;i++){
		for(j=0;j<16;j++){
			if (Grave[i][j])
				Delete_Piece(Grave[i][j]);
			Grave[i][j]=NULL;
		
		}
	}
	return 0;
} 
