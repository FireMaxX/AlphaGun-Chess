/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Team AlphaGun                                             */
/* Date: 02/05/2017                                                  */
/*                                                                   */
/* ChessGame.c                                                       */
/*                                                                   */
/*********************************************************************/
/*Modified by YijianW */
/*Modified by Xiaoyan Yang*/
/*Modified by Yan Zhang*/
/*Please define any function here that may be used in the main loop*/

#include "Board.h"
#include "Constant.h"
#include "Piece.h"
#include "Rules.h"
#include "Type.h"
#include "UserIO.h"
#include "GUI.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Lib.h"
#include "AI.h"
void init(char *title);
void getInput();
void cleanup();
SDL_Surface *Loadgraph(char* bmpImage);
void drawImage(SDL_Surface *image, int x, int y);
void updateScreen();
void Refresh();
void Setclass(SQUARE board[][8]);
void Singlemove(int c, SQUARE board[][8],DIRECTION Direct, DIRECTION DD);
void ReplaceBlock(int c, SQUARE board[][8], DIRECTION Direct);
void Gyard(PIECE *grave[2][16]);

void PrintMenu();
void Game1player(int usercolor);
void Game2players();
void LoadGame(SQUARE newBoard[][8], PIECE *grave[][16], int color);
int AIMakesMove(int color,SQUARE newBoard[8][8],PIECE *grave[2][16]);
int MakesMove(int color,SQUARE newBoard[8][8],PIECE *grave[2][16]);

int main()
{
	/*Define variables*/
	int choice;
	int color_choice;	
	/* For Logfile List */
	lf = malloc(sizeof(LIST));
	lf->number = 0;
	lf->First = NULL;
	lf->Last = NULL;

	/*The main loop starts here*/
	while (choice != 4){

		PrintMenu();
		printf("\nPlease input your mode choice: ");
		scanf("%d", &choice);

		/*1 player mode */
		if(choice == 1){
			printf("\nPlease input  your color choice. (black:0 white:1): ");
			scanf("%d", &color_choice);
			Game1player(color_choice);	
		}
		/*2 players mode */
		else if(choice == 2){
			Game2players();
			return 0;
		}
		/*load previous game*/
		else if(choice == 3){
			int i, j, retsta;
			printf("Beta Version! Test Mode Start!\n");	/*not finish*/
			printf("Option 1: Create Save File for Test\nOption 2: Load Exist Game Log(beta)\nMake your choice:\n");
			scanf("%d", &i);
			if (i == 1) { /* Save Board */
				SQUARE newBoard[8][8];
				Set_Board(newBoard);
				SetPieces(newBoard);
				PIECE *grave[2][16];
				for (i = 0; i<2; i++) {
					for (j = 0; j<16; j++) {
						grave[i][j] = NULL;
					}
				}
				retsta = Saveboard("Save.txt", newBoard, grave, lf);
				PrintBoard(newBoard);
				PrintGrave(grave); 
				printf("Done! Return Value:=%d\n", retsta);
			}
			else { /* Load Game */
				SQUARE newBoard[8][8];
				Set_Board(newBoard);
				PIECE *grave[2][16];
				for (i = 0; i<2; i++) {
					for (j = 0; j<16; j++) {
						grave[i][j] = NULL;
					}
				}
				retsta = Loadboard("Save.txt", newBoard, grave);
				PrintBoard(newBoard);
				PrintGrave(grave);
				printf("Done! Return Value:=%d\n", retsta);
				LoadGame(newBoard, grave, retsta);
			}			
		}
		/*wrong input*/
		else if (choice==4){
			return 0;
		}
		else {
			printf("Wrong input. Please input choice again.\n");
			continue;
		}
	}
	return 0;
};

void PrintMenu()
{
	printf("Welcome to the chess game terminal!!\n\n\n");
	printf("     Present By Team Alpha Gun\n\n\n\n");
	printf("		ii		\n");
	printf("	       i  i		\n");
	printf("	      i A  i		\n");
	printf("	      i  G i		\n");
	printf("	       i  i		\n");
	printf("		ii		\n\n\n");
	printf("1. Start as Player vs. Computer\n");
	printf("2. Start as Player vs. Player\n");
	printf("3. load previous saved game\n");
	printf("4. Exit\n");

}

void Game2players(){ 
  	int live = 1;/* 2 to exit current game without saving;0 not live, 1 live; 3 save current game*/
  	int color = 1;
	int i,j,result;
	int ret;
	int check_condition;
	DIRECTION king_position;

  	SQUARE newBoard[8][8];
  	Set_Board(newBoard);
	SetPieces(newBoard);
   	PIECE *grave[2][16];

	char* name;
	SDL_Surface *image;
	init("AlphaGun Chess");
	
	atexit(cleanup);

	name = "../src/Board.bmp";


 	for (i=0;i<2;i++){
		for (j=0;j<16;j++){
			grave[i][j]=NULL;
		}
	}

	image=Loadgraph(name);

	/*updateScreen(image);*/
	Setclass(newBoard);
	SDL_Delay(2);

  	while(live != 0){
    		king_position = Find_Piece(newBoard,1-color,4);
 
		check_condition = Check(newBoard,king_position.x,king_position.y,1-color);
    		if (check_condition == 1){
    			printf("\nCheck!\n");
    		} 

  		PrintBoard(newBoard);
		PrintGrave(grave); 
		/*Makes a move*/
  		live = MakesMove(color,newBoard,grave);
       		if (live == 2){
			printf("\nExit Game");
			live=0;
			continue;
		}
		else if (live ==3){
		/*saveboard*/
			ret = Saveboard("Save.txt", newBoard, grave, lf);
			if (ret == 0) {
				printf("\nGame Saved!");
			}
			live=1;
			continue;
		}
		else if (live == 4) {
			result = Undo(lf, newBoard, grave);
			printf("%d\n", result);
			result = Undo(lf, newBoard, grave); /* Undo two steps everytime, one for each side */
			printf("%d\n", result);
			printf("Undo Done!\n");

			image = Loadgraph(name);
			Setclass(newBoard);
			live = 1;
			continue;
		}
		else if (live == 5) {
			Reset(newBoard, grave, lf);
			SetPieces(newBoard);
			printf("Reset Done\n");
			PrintBoard(newBoard);
			PrintGrave(grave);
			image = Loadgraph(name);
			Setclass(newBoard);
			color = 1;
			continue;
		}
		PrintBoard(newBoard);
		PrintGrave(grave); 

  		if (live == 0){
			if (color == 0) {
				printf("\nKing Captured! Black wins!");
			}
			else
			{
				printf("\nKing Captured! White wins!");
			}
  			continue;
  		}
		color = 1 - color;
	}
  Delete_Board(newBoard);
  Delete_Grave(grave);
  return;
  }
 
void LoadGame(SQUARE newBoard[][8], PIECE *grave[][16], int color) {
	int live = 1;
	int ret;
	int result;

	char* name;
	SDL_Surface *image;
	init("AlphaGun Chess");

	atexit(cleanup);

	name = "../src/Board.bmp";

	image = Loadgraph(name);

	/*updateScreen(image);*/
	Setclass(newBoard);
	SDL_Delay(2);

	while (live != 0) {
		PrintBoard(newBoard);
		PrintGrave(grave); 
		/*Makes a move*/
		live = MakesMove(color, newBoard, grave);
		if (live == 2) {
			printf("\nExit Game");
			live=0;
			continue;
		}
		else if (live == 3) {
			/*saveboard*/
			ret = Saveboard("Save.txt", newBoard, grave, lf);
			if (ret == 0) {
				printf("\nGame Saved!");
			}
			live=1;
			continue;
		}
		else if (live == 4) {
			result=Undo(lf,newBoard,grave);
			printf("%d\n",result);
			result=Undo(lf,newBoard,grave);
			printf("%d\n",result);
			image = Loadgraph(name);
			Setclass(newBoard);
			live = 1;
			continue;
		}
		else if (live == 5) {
			Reset(newBoard, grave, lf);
			SetPieces(newBoard);
			printf("Reset Done\n");
			PrintBoard(newBoard);
			PrintGrave(grave);
			image = Loadgraph(name);
			Setclass(newBoard);
			color = 1;
			continue;
		}
		PrintBoard(newBoard);
		PrintGrave(grave); 


		if (live == 0) {
			if (color == 0) {
				printf("\nKing Captured! Black wins!");
			}
			else
			{
				printf("\nKing Captured! White wins!");
			}
			continue;
		}
		color = 1 - color;
	}
	Delete_Board(newBoard);
	Delete_Grave(grave);
	return;
}
 

int AIMakesMove(int color,SQUARE newBoard[8][8],PIECE *grave[2][16]){
	CURRENT_MOVE current_move;
    	int color_n;
	int x;
    	int live = 1;
    	int move_condition = 0;
    	DIRECTION start_d;
	DIRECTION end_d;
    	char c[32];
	if(color==0){
    		color_n =1;
   		strcpy(c ,"BLACK");
	}
    	else if(color == 1){
    		color_n=0;
   		strcpy(c ,"WHITE");
    	}
    	
    	/*move, cannot move or capture condition*/
	while(move_condition==0){
		printf("\n%s makes a move.\n",c);
		current_move = AIMove(newBoard,color);
		start_d = current_move.start_pos;
		end_d = current_move.end_pos;

		if ((newBoard[start_d.x][start_d.y].p==NULL)||(newBoard[start_d.x][start_d.y].p->color!=color)){
			move_condition=0;
		}
		else {
    			move_condition=LegalMove(newBoard, start_d.x,start_d.y,end_d.x,end_d.y);
		}
		if (move_condition==1){
			assert(newBoard[start_d.x][start_d.y].p);
			NewLogFile(start_d, end_d, newBoard[start_d.x][start_d.y].p->status, lf);
			x=Move(newBoard,start_d.x,start_d.y,end_d.x,end_d.y,grave);
			ReplaceBlock(color,newBoard, start_d);
			Singlemove(color, newBoard,end_d,start_d);
			Gyard(grave);

			break;
		}
    		if (move_condition == 0){
    			printf("\nIlegal target position. Choose your target position again!");
			continue;
    		}
		if (move_condition==2){
			assert(newBoard[start_d.x][start_d.y].p);
			assert(newBoard[end_d.x][end_d.y].p);
			if (newBoard[start_d.x][start_d.y].p->status == 0) { 
				if (newBoard[end_d.x][end_d.y].p->status == 0) {
					NewLogFile(start_d, end_d, 5, lf);	/* A inital status piece captured a initial piece */
				}
				else {
					NewLogFile(start_d, end_d, 4, lf);	/* A inital status piece captured a non-initial piece */
				}
			}
			else
			{
				if (newBoard[end_d.x][end_d.y].p->status == 0) {
					NewLogFile(start_d, end_d, 3, lf);	/* A non-inital status piece captured a initial piece */
				}
				else {
					NewLogFile(start_d, end_d, 2, lf); 	/* A non-inital status piece captured a non-initial piece */
				}
			}
			x=Move(newBoard,start_d.x,start_d.y,end_d.x,end_d.y,grave);
			ReplaceBlock(color,newBoard, start_d);
			Singlemove(color, newBoard,end_d,start_d);
			Gyard(grave);

			if (x==3){
				live=0;
				break;
			}
		}	
	}
    	return live;
}

int MakesMove(int color,SQUARE newBoard[][8],PIECE *grave[][16]){
	SDL_Event event;
/*	SDL_Surface *image;
	char* name;
	name = "../src/Board.bmp";*/

	int Running;
	int result;
    	int color_n;
	int x;
    	int live = 1;
/*   	char exit[4]; */
    	int move_condition = 0;
    	DIRECTION start_d;
	DIRECTION end_d;
    	char c[32];
    	if (color == 0){
    		color_n =1;
   		strcpy(c ,"BLACK");
	}
    	else if(color == 1){
    		color_n=0;
   		strcpy(c ,"WHITE");
    	}
    	
    	/*move, cannot move or capture condition*/
	while(move_condition==0){
		Running=1;
    		printf("\n%s makes a move\n",c);
		while (Running && SDL_WaitEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:{
					if (event.button.button==1){
					printf("Oh! Mouse button %d pressed!\n",event.button.button);
					printf("Position is x=%d, y=%d.\n",event.button.x, event.button.y);
					if (event.button.x>=800 && event.button.x<=870 && event.button.y>=0 && event.button.y<150){
						if (lf->number >= 2) {
							live = 4;
							Running=0;
							break;
						}
						else
						{
							printf("Cannot undo at this point!\n");
							Running=0;
							live=1;
							break;
						}		
					}else if (event.button.x>=800 && event.button.x<=870 && event.button.y>=150 && event.button.y<300){
						live=2;
						Running=0;
						break;							
					}else if (event.button.x>=800 && event.button.x<=870 && event.button.y>=300 && event.button.y<450){
						live=3;
						Running=0;
						break;
						
					}else if (event.button.x>=800 && event.button.x<=870 && event.button.y>=450 && event.button.y<600){
						live=5;
						Running=0;
						break;

					}
					else{
						start_d.x=(int)((event.button.x+47)/75-1);
						start_d.y=(int)(7-event.button.y/75);
						printf("clicked on %d,%d\n",start_d.x,start_d.y);
						Running=0;
						break;
					}
					}
				}
				default:{continue;}
			}
		}
		if (live==2 || live==3 || live==4 || live==5){break;}
		else{
			Running=1;
    			printf("\nEnter target position: ");
			while (Running && SDL_WaitEvent(&event)){
				switch(event.type){
					case SDL_MOUSEBUTTONDOWN:{
						if (event.button.button==1){
						printf("Oh! Mouse button %d pressed!\n",event.button.button);
						printf("Position is x=%d, y=%d.\n",event.button.x, event.button.y);
						if (event.button.x>=800 && event.button.x<=870 && event.button.y>=0 && event.button.y<150){
							if (lf->number >= 2) {
								result = Undo(lf, newBoard, grave);
								printf("%d\n", result);
								result = Undo(lf, newBoard, grave); /* Undo two steps everytime, one for each side */
								printf("%d\n", result);
								printf("Undo Done!\n");
								live = 4;
								break;
							}
							else
							{
								printf("Cannot undo at this point!\n");
							}		
						}else if (event.button.x>=800 && event.button.x<=870 && event.button.y>=150 && event.button.y<300){
							live=2;
							Running=0;
							break;							
						}else if (event.button.x>=800 && event.button.x<=870 && event.button.y>=300 && event.button.y<450){
							live=3;
							Running=0;
							break;
						
						}else if (event.button.x>=800 && event.button.x<=870 && event.button.y>=450 && event.button.y<600){
							live=5;
							Running=0;
							break;

						}

						else{

							end_d.x=(int)((event.button.x+47)/75-1);
							end_d.y=(int)(7-event.button.y/75);
							printf("clicked on %d,%d\n",end_d.x,end_d.y);
							Running=0;
							break;
						}
						}
					}
					default:{continue;}
				}
			}
		}
		if (live==2 || live==3 || live==4 || live==5){break;}

		if ((newBoard[start_d.x][start_d.y].p==NULL)||(newBoard[start_d.x][start_d.y].p->color!=color)){
			move_condition=0;
		}
		else {
    			move_condition=LegalMove(newBoard, start_d.x,start_d.y,end_d.x,end_d.y);
		}
		if (move_condition==1){
			assert(newBoard[start_d.x][start_d.y].p);
			NewLogFile(start_d, end_d, newBoard[start_d.x][start_d.y].p->status, lf);
			x=Move(newBoard,start_d.x,start_d.y,end_d.x,end_d.y,grave);
			ReplaceBlock(color,newBoard, start_d);
			Singlemove(color, newBoard,end_d,start_d); 
	/*		image=Loadgraph(name);
			Setclass(newBoard);*/
			Gyard(grave);

			break;
		}
    		if (move_condition == 0){
    			printf("\nIlegal target position. Choose your target position again!");
			continue;
    		}
		if (move_condition==2){
			assert(newBoard[start_d.x][start_d.y].p);
			assert(newBoard[end_d.x][end_d.y].p);
			if (newBoard[start_d.x][start_d.y].p->status == 0) { 
				if (newBoard[end_d.x][end_d.y].p->status == 0) {
					NewLogFile(start_d, end_d, 5, lf);	/* A inital status piece captured a initial piece */
				}
				else {
					NewLogFile(start_d, end_d, 4, lf);	/* A inital status piece captured a non-initial piece */
				}
			}
			else
			{
				if (newBoard[end_d.x][end_d.y].p->status == 0) {
					NewLogFile(start_d, end_d, 3, lf);	/* A non-inital status piece captured a initial piece */
				}
				else {
					NewLogFile(start_d, end_d, 2, lf); 	/* A non-inital status piece captured a non-initial piece */
				}
			}
			x=Move(newBoard,start_d.x,start_d.y,end_d.x,end_d.y,grave);
			ReplaceBlock(color,newBoard, start_d);
			Singlemove(color, newBoard,end_d,start_d); 
	/*		image=Loadgraph(name);
			Setclass(newBoard); */
			Gyard(grave);

			if (x==3){
				live=0;
				break;
			}
		}	
	} 
    	return live;
}

void Game1player(int usercolor){
  	int live = 1;/* 2 to exit current game without saving;0 not live, 1 live; 3 save current game*/
  	int color = 1-usercolor;
	int current_color = 1;
	int i,j;
	int ret;
	int firstmove = 0;
  	SQUARE newBoard[8][8];
  	Set_Board(newBoard);
	SetPieces(newBoard);
   	PIECE *grave[2][16];

	char* name;
	SDL_Surface *image;
	init("AlphaGun Chess");
	
	atexit(cleanup);

	name = "../src/Board.bmp";


 	for (i=0;i<2;i++){
		for (j=0;j<16;j++){
			grave[i][j]=NULL;
}}
	image=Loadgraph(name);

	/*updateScreen(image);*/
	Setclass(newBoard);
	SDL_Delay(2);
  	while(live == 1){
		PrintBoard(newBoard);
		PrintGrave(grave);
		printf("pass1\n");
		/*Makes a move*/
		if(usercolor == current_color){
			firstmove = 1;
			live = MakesMove(usercolor,newBoard,grave);
			}
		else{
			if(firstmove == 0){
			live = AIMakesMove(color,newBoard,grave);
			firstmove=1;
		}
  			else{	
			live = AIMakesMove(color,newBoard,grave);
			
	}
	}

       		if (live == 2){
			printf("\nExit Game");
			continue;
		}
		else if (live ==3){
			ret = Saveboard("Save.txt", newBoard, grave,lf);
			if (ret == 0) {
				printf("\nGame Saved!");
			}
			continue;
		}
		else if (live == 4) {
			image = Loadgraph(name);
			Setclass(newBoard);
			live = 1;
			continue;
		}
  		PrintBoard(newBoard);
		PrintGrave(grave);


  		if (live == 0){
			if (color == 0) {
				printf("\nKing Captured! Black wins!");
			}
			else
			{
				printf("\nKing Captured! White wins!");
			}
  			continue;
  		}
	current_color = 1-current_color;
	}
  Delete_Board(newBoard);
  Delete_Grave(grave);
  return;	
} 
 

