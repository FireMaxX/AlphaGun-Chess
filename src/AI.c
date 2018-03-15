/*********************************************************************/
/* AlphaGun ChessGame Alpha Version                                  */
/*                                                                   */
/* Authors: Xiaoyan Yang 	Yanjie Xu       	             */
/* Date: 02/02/2017                                                  */
/*         revised                                                   */
/* Computer chess player program                                     */
/*                                                                   */
/*********************************************************************/
#include "AI.h"
#include <assert.h>
VALID_STEPS SearchSteps(SQUARE board[][8], int tar_x, int tar_y){									/*search all posible moves on current position*/
	VALID_STEPS ensteps;
	DIRECTION steps[100];			/*total number of legal move*/
	int i,j;
	int capcount = 0;			/*how many capture move*/
	int count = 0;				/*how many legal move*/
	int flag;				/*legal movie flag*/
	for (i = 0; i < 8; i++ ){
		for (j = 0; j < 8; j++){
			flag = LegalMove(board, tar_x, tar_y,i, j);
			if (flag == 1 || flag == 2){
				steps[count].x = i;
				steps[count].y = j;
       				count ++;
		       		if (flag == 2)
					capcount++;
				
			}
		}
	}
	ensteps.step = steps;			/*invalid use of flexible array member*/
	ensteps.capcount = capcount;
	ensteps.count=count;
	return ensteps;
}

int FindAllLegalMove(SQUARE board[][8],int color,CURRENT_MOVE possibleMove[1000]){			/*LIST ALL POSSIBLE TO A SERIES (PAIRED LOCATION)(CURRENT AND FUTURE)*/
	int i,j,k=0;
	int count=0;
	DIRECTION temp;
 	DIRECTION piecePosition[64];
 	VALID_STEPS moveStep;
 	for(i = 0;i < 15;i++){
		temp = Find_Piece(board,color,i);
		if(temp.x>-1&&temp.x<8){
			piecePosition[i]=temp;
			count++; 
		}
	}			
	for (i=0;  i < count; i++){
		moveStep = SearchSteps(board,piecePosition[i].x,piecePosition[i].y);
		for (j=0; j<moveStep.count; j++){
				 possibleMove[k].start_pos = piecePosition[i];
				 possibleMove[k].end_pos = moveStep.step[j];
				printf("(%d,  %d)\n",possibleMove[k].end_pos.x,possibleMove[k].end_pos.y);
				 k++;
			}
	}
 return k;
}				

/*First level: supposed to return current move*/
CURRENT_MOVE AIMove(SQUARE board[][8],int color){
	CURRENT_MOVE AIFirstMove[1000];
	CURRENT_MOVE finalMove;
	SQUARE newBoard[8][8];
	int legalMoveCount = 0;
	int firstMoveValue = 0;
	int i=0,j,k=0,max,max_value=-9999;
	int index=0;
	PIECE *tempPointer;
	legalMoveCount = FindAllLegalMove(board,color,AIFirstMove);  /*first prediction, l*/
/*	printf("First step self position search done---- pass1\n");*/
	while(k<legalMoveCount){		
		printf("Toplevel move start position: (%d, %d)\n",AIFirstMove[k].end_pos.x,AIFirstMove[k].end_pos.y);
		/*-----------------------------------------*/
		for (i=0;i < 8;i++){
			for (j = 0; j<8 ; j++){
				newBoard[i][j]=board[i][j];
			} 
		}
		tempPointer = newBoard[AIFirstMove[k].start_pos.x][AIFirstMove[k].start_pos.y].p;
		newBoard[AIFirstMove[k].start_pos.x][AIFirstMove[k].start_pos.y].p = NULL;
		newBoard[AIFirstMove[k].end_pos.x][AIFirstMove[k].end_pos.y].p= tempPointer;		
	/*	printf("new Board generate successful!\n");*/
		/*---------------------------------------*/
		firstMoveValue = max_AI(board,AIFirstMove[k].start_pos,AIFirstMove[k].end_pos);
		max_value = firstMoveValue*8+user_min(newBoard,color);		
			
		/*Compare max value to output a final move*/
    		if (max<max_value){
			max = max_value;
			index = k;
    		}
		printf("Second level opponent future prediction search check----- k=%d max=%d \n",k, max);
	k++;
  }
  finalMove = AIFirstMove[index];
  printf("%d%d %d%d",finalMove.start_pos.x,finalMove.start_pos.y,finalMove.end_pos.x,finalMove.end_pos.y);
  return finalMove;
	
}
/*second level: supposed to return the max value of all user min values*/
int user_min(SQUARE board[][8],int color){
	int min_value=99999, min;
	int i=0,j;
	int user_color;
	int index=0;
	PIECE *tempPointer;
	int AISecondCount = 0;
	int userMoveCount = 0;
	int userThreatValue = 0;
	CURRENT_MOVE AISecondMove[1000];
	CURRENT_MOVE userPossibleMove[1000];
	SQUARE newBoard[8][8];
 	if (color == 0)					/*to invert the color for next prediction*/
		user_color = 1;
	else 
		user_color = 0;
	/*printf("level two, predict opponent move\n");*/
	userMoveCount = FindAllLegalMove(board,user_color,userPossibleMove);
/*	printf("userMoveCount=%d",userMoveCount);*/
	while(index<userMoveCount){
	       	userThreatValue = max_AI(board,userPossibleMove[index].start_pos,userPossibleMove[index].end_pos);	
		for (i=0;i < 8;i++){
			for (j = 0; j<8 ; j++){
				newBoard[i][j]=board[i][j];
			}
		}	
		tempPointer = newBoard[userPossibleMove[index].start_pos.x][userPossibleMove[index].start_pos.y].p;
		newBoard[userPossibleMove[index].start_pos.x][userPossibleMove[index].start_pos.y].p = NULL;
		newBoard[userPossibleMove[index].end_pos.x][userPossibleMove[index].end_pos.y].p= tempPointer;
		/*create new board for future use*/
		AISecondCount = FindAllLegalMove(newBoard,color,AISecondMove);
		if(index == 0){
			while (i<AISecondCount){																		
				min =  max_AI(newBoard,AISecondMove[i].start_pos,AISecondMove[i].end_pos);			/*enter third level */
				min = min*5-userThreatValue*150; 
				if (min<min_value)
					min_value = min;
				i++;
			}
		}
		
		else{
			while (i<AISecondCount){
				min =  max_AI(newBoard,AISecondMove[i].start_pos,AISecondMove[i].end_pos);
				min = min*5 - userThreatValue*150;
				if (min<min_value){
					index++;
					break;
				}
				i++;
			} 
			if(i==AISecondCount)
			min_value = min;   
			
		}
		index++;
	}
	return min_value;
}




int max_AI(SQUARE board[][8], DIRECTION tar_dir, DIRECTION des_dir){
	int value;
	int count;
	int i,j;	
	int capvalue=0;
	int capcount=0;
	VALID_STEPS newstep;
	PIECE *tempPointer;
	SQUARE newBoard[8][8];
	for (i=0;i < 8;i++){
		for (j = 0; j<8 ; j++){
			newBoard[i][j]=board[i][j];
		}
	}
	tempPointer = newBoard[tar_dir.x][tar_dir.y].p;
	newBoard[tar_dir.x][tar_dir.y].p = NULL;
	newBoard[des_dir.x][des_dir.y].p= tempPointer;
	newstep = SearchSteps(newBoard,des_dir.x,des_dir.y);
	count = newstep.count;
	capcount = newstep.capcount;
	if (board[des_dir.x][des_dir.y].p!=NULL)
		capvalue = board[des_dir.x][des_dir.y].p->value;
	value = count*2+ capcount*5+capvalue*20;	
	printf("touched bottom level-----value= %d \n\n",value);	
	return value;
}

