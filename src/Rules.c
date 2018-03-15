/*Rules.c*/
/*Created by Yan Zhang 1/26/2017*/

#include "Rules.h"
#include <stdio.h>
#include <assert.h>

/*Move piece*/
/*Input 2 positions, return 0, 1, 2, 3 (or 4): 0= cannot move; 1= move to a blank square; 2= capture; 3=king captured; (4=castling)*/
int Move(SQUARE board[][8], int tar_x,int tar_y,int des_x,int des_y, PIECE *grave[][16]){
	SQUARE tar;
	tar = board[tar_x][tar_y];
	assert(tar.p);
	SQUARE des;
	des = board[des_x][des_y];
	int i;
	int result=LegalMove(board,tar_x,tar_y,des_x,des_y);
	switch (result){
		case 0: return 0;
		case 1: board[des_x][des_y].p=board[tar_x][tar_y].p;
			board[tar_x][tar_y].p=NULL;
			if (board[des_x][des_y].p->status==0){
				board[des_x][des_y].p->status=1;
			}
			return 1;
		case 2: {if ((board[des_x][des_y].p->name) == 'K'){
				for (i=0; i<=15; i++){
					if (grave[board[des_x][des_y].p->color][i]==NULL){
						grave[board[des_x][des_y].p->color][i]=board[des_x][des_y].p;
						board[des_x][des_y].p->status=2;
						board[des_x][des_y].p=board[tar_x][tar_y].p;
						board[tar_x][tar_y].p=NULL;
						break;
					}
					else {
						continue;
					}		
				}
				return 3;
			}
			else {
				for (i=0; i<=15; i++){
					if (grave[board[des_x][des_y].p->color][i]==NULL){
						grave[board[des_x][des_y].p->color][i]=board[des_x][des_y].p;
						board[des_x][des_y].p->status=2;
						board[des_x][des_y].p=board[tar_x][tar_y].p;
						board[tar_x][tar_y].p=NULL;
						break;
					}
					else {
						continue;
					}		
				}
				return 2;
			}}
		default:printf("Wrong output of LegalMove!");
			return 0;
	}
}

/*Input the position and the color of the King, return 1 if checked, 0 if King is safe*/
int Check(SQUARE board[][8], int color, int x, int y){	
	int i,j;
	for (i=0;i<=7;i++){
		for (j=0;j<=7;j++){
			if (board[i][j].p==NULL){
				continue;
			}
			else{
		 		if ((board[i][j].p->color)!=color){
					if (LegalMove(board,i,j,x,y)==2){
						return 1;
					}
					else{
						continue;
					}	
				}
				else {
					continue;
				}
			}	
		}
	}
	return 0;	
}

/*LegalMove: return 0 for cannot move; 1 for move to empty; 2 for capture*/
int LegalMove(SQUARE board[][8], int tar_x, int tar_y, int des_x, int des_y){
	int legal;
	int i,j;
	SQUARE tar;
	tar=board[tar_x][tar_y];
	assert(tar.p);
	SQUARE des;
	des=board[des_x][des_y];
	legal=PieceLegalMove(board,tar_x,tar_y,des_x,des_y);
	if (legal==1){
		switch (board[tar_x][tar_y].p->name){
			case 'P':if (board[tar_x][tar_y].p->color==1){
					if ((des_x==tar_x)&&(board[tar_x][tar_y+1].p!=NULL)){
						return 0;
					}
				}	
				else {
					if ((des_x==tar_x)&&(board[tar_x][tar_y-1].p!=NULL)){
						return 0;
					}
				}
				break;
			case 'B':if (tar_x<des_x && tar_y<des_y){
					for (i=tar_x+1;i<des_x;i++){
						for (j=tar_y+1;j<des_y;j++){
							if ((i-tar_x==j-tar_y)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}
		
				if (tar_x<des_x && tar_y>des_y){
					for (i=tar_x+1;i<des_x;i++){
						for (j=tar_y-1;j>des_y;j--){
							if ((i-tar_x==tar_y-j)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}

				if (tar_x>des_x && tar_y<des_y){
					for (i=tar_x-1;i>des_x;i--){
						for (j=tar_y+1;j<des_y;j++){
							if ((tar_x-i==j-tar_y)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}
				if (tar_x>des_x && tar_y>des_y){
					for (i=tar_x-1;i>des_x;i--){
						for (j=tar_y-1;j>des_y;j--){
							if ((tar_x-i==tar_y-j)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}
				break;


				
			case 'Q':if (tar_x<des_x && tar_y==des_y){
				 	for (i=tar_x;i<des_x;i++){
						if ((i!=tar_x)&&(board[i][tar_y].p!=NULL)){
							return 0;
						}
						else {continue;}
					}
				 }
				 if (tar_x>des_x && tar_y==des_y){

					for (i=tar_x;i>des_x;i--){
						if ((i!=tar_x)&&(board[i][tar_y].p!=NULL)){
							return 0;
						}
						else {continue;}
					}			
				 }
		
				 if (tar_x==des_x && tar_y<des_y){
					for (j=tar_y;j<des_y;j++){
						if (( j!=tar_y)&&(board[tar_x][j].p!=NULL)){
							return 0;
						}
						else {continue;}
					}					 	
				 }
				
				 if (tar_x==des_x && tar_y>des_y){
					for (j=tar_y;j>des_y;j--){
						if ((j!=tar_y)&&(board[tar_x][j].p!=NULL)){
							return 0;
						}
						else {continue;}
					}					 	
				 }

				 if (tar_x<des_x && tar_y<des_y){
					for (i=tar_x+1;i<des_x;i++){
						for (j=tar_y+1;j<des_y;j++){
							if ((i-tar_x==j-tar_y)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}
		
				if (tar_x<des_x && tar_y>des_y){
					for (i=tar_x+1;i<des_x;i++){
						for (j=tar_y-1;j>des_y;j--){
							if ((i-tar_x==tar_y-j)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}

				if (tar_x>des_x && tar_y<des_y){
					for (i=tar_x-1;i>des_x;i--){
						for (j=tar_y+1;j<des_y;j++){
							if ((tar_x-i==j-tar_y)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}
				if (tar_x>des_x && tar_y>des_y){
					for (i=tar_x-1;i>des_x;i--){
						for (j=tar_y-1;j>des_y;j--){
							if ((tar_x-i==tar_y-j)&&(board[i][j].p!=NULL)){
								return 0;
							}
							else{	continue;}
						}
					}
				}
				break;

			case 'N':break;
			case 'K':break;
			case 'R':if (tar_x<des_x && tar_y==des_y){
				 	for (i=tar_x+1;i<des_x;i++){
						if (board[i][tar_y].p!=NULL){
							return 0;
						}
						else {continue;}
					}
				 }
				 if (tar_x>des_x && tar_y==des_y){

					for (i=tar_x-1;i>des_x;i--){
						if ((i!=tar_x)&&(board[i][tar_y].p!=NULL)){
							return 0;
						}
						else {continue;}
					}		
				 }
		
				 if (tar_x==des_x && tar_y<des_y){
					for (j=tar_y+1;j<des_y;j++){
						if (( j!=tar_y)&&(board[tar_x][j].p!=NULL)){
							return 0;
						}
						else {continue;}
					}					 	
				 }
				
				 if (tar_x==des_x && tar_y>des_y){
					for (j=tar_y-1;j>des_y;j--){
						if ((j!=tar_y)&&(board[tar_x][j].p!=NULL)){
							return 0;
						}
						else {continue;}
					}					 	
				 }
				break;
			
			default:break;

		}
		if (board[des_x][des_y].p==NULL){
			return 1;
		}
		else {
			if (board[des_x][des_y].p->color==board[tar_x][tar_y].p->color){
				return 0;
			}
			else if ((board[tar_x][tar_y].p->name =='P') && (tar_x == des_x)) {
				return 0;
			}
			else
				return 2;
		} 
	}
	else {
		return 0;
	}

}







