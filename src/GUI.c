#include "GUI.h"
#include "Type.h"
#include "Board.h"
#include "Piece.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int PrintBoard(SQUARE board[][8])
{
	int i = 0, j = 0;
	char* setchar[8][8];
	const char B[2] = "B";
	const char W[2] = "W";
	char CB[2], CW[2];
	char* N;

	/*charactor needs to be moved*/
	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8; i++) {
			if (board[i][j].p) {
				N = &board[i][j].p->name;
				if (board[i][j].p->color == 0) {
					strcpy(CB, B);
					strcat(CB, N);
					setchar[i][j] = malloc(sizeof(CB));
					assert(setchar[i][j]);
					strcpy(setchar[i][j], CB);
				}
				else {
					strcpy(CW, W);
					strcat(CW, N);
					setchar[i][j] = malloc(sizeof(CW));
					assert(setchar[i][j]);
					strcpy(setchar[i][j], CW);
				}
			}
			else {
				if (board[i][j].color == 0) {
					setchar[i][j] = malloc(sizeof("--"));
					assert(setchar[i][j]);
					strcpy(setchar[i][j], "--");
				}
				else {
					setchar[i][j] = malloc(sizeof("++"));
					assert(setchar[i][j]);
					strcpy(setchar[i][j], "++");
				}	
			}
	/*		printf("%s,(%d,%d)\n", setchar[i][j], i, j); */
			
		}
	}

	i = 0;
	j = 0;

	for (j = 8; j > 0; j--) {
		printf("   -----   -----   -----   -----   -----   -----   -----   ----- \n");
		printf(" %d", j);
		for (i = 0; i < 8; i++) {
			printf(" | %s  |", setchar[i][j - 1]);
		}
		printf("\n");
	}
	printf("   -----   -----   -----   -----   -----   -----   -----   ----- \n");
	printf("     A	     B	     C	     D       E       F       G       H   \n");
	
	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8; i++) {
			assert(setchar[i][j]);
			free(setchar[i][j]);
		}
	}

	return 0;
}

int PrintGrave(PIECE *grave[2][16]) {

	int i = 0;
	printf("Grave\n");
	printf("Black: \n");
	for (i = 0; i<16; i++) {
		if (grave[0][i] == NULL)
			printf("X ");
		else
			printf("%c ", grave[0][i]->name);
	}
	printf("\nWhite:\n");
	for (i = 0; i<16; i++) {
		if (grave[1][i] == NULL)
			printf("X ");
		else
			printf("%c ", grave[1][i]->name);
	}
	printf("\n");
	return 0;
}



