/*********************************************************************/
/* AlphaGun ChessGame Beta Version                                   */
/*                                                                   */
/* Author: Super Agent Max :)                                        */
/* Date: 01/26/2017                                                  */
/*                                                                   */
/* UserIO.c: Handle operations related to input/output               */
/*                                                                   */
/*********************************************************************/
/* Version 1.0: Focus on getPosition function -Max */

#include "UserIO.h"
#include "Piece.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int Saveboard(char outFileName[32], SQUARE board[][8], PIECE *grave[2][16], LIST *lf)
{
	int i, j;
	int typ = 0;
	int col = 0;
	int ret = 0;
	int number = 0;
	char *out;
	FILE *pFile;
	ENTRY *p;
	
	out = &outFileName[0];
	pFile = fopen(out, "w");
	if (pFile == NULL) {
		printf("Cannot open file!\n");
		return 1;
	}
	else { /* File Open Successfully */
		/* Save Board */
		for (j = 7; j >= 0; j--) {
			for (i = 0; i < 8; i++) {
				if (board[i][j].p == NULL) {
					typ = 0; /* Empty */
				}
				else {
					switch (board[i][j].p->name)
					{
					case 'P': {
						typ = Pawn;
						break;
					}
					case 'N': {
						typ = Knight;
						break;
					}
					case 'B': {
						typ = Bishop;
						break;
					}
					case 'R': {
						typ = Rook;
						break;
					}
					case 'Q': {
						typ = Queen;
						break;
					}
					case 'K': {
						typ = King;
						break;
					}
					}

					if (board[i][j].p->color == 0) {
						col = -1; /* Black */
					}
					else {
						col = White;
					}
				}
				ret = col * typ; /* 1=King 2=Queen 3=Rook 4=Bishop 5=Knight 6=Pawn */
				fprintf(pFile, "%d ", ret);
				if (board[i][j].p == NULL) {
					fprintf(pFile, "%d %d ", 1, 16); /* Empty Square */
				}
				else {
					fprintf(pFile, "%d %d ", board[i][j].p->status, board[i][j].p->number);
				}
			} /* End of i for loop */
		} /* End of j for loop */

		/* Save Grave */
		typ = 0;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 16; j++) {
				printf("%d,%d\n", i, j);
				if (grave[i][j] == NULL) {
					typ = 0; /* Empty */
					number = 0;
				}
				else {
					switch (grave[i][j]->name)
					{
					case 'P': {
						typ = Pawn;
						number = grave[i][j]->number;
						break;
					}
					case 'N': {
						typ = Knight;
						number = grave[i][j]->number;
						break;
					}
					case 'B': {
						typ = Bishop;
						number = grave[i][j]->number;
						break;
					}
					case 'R': {
						typ = Rook;
						number = grave[i][j]->number;
						break;
					}
					case 'Q': {
						typ = Queen;
						number = grave[i][j]->number;
						break;
					}
					case 'K': {
						typ = King;
						number = grave[i][j]->number;
						break;
					}
					default:
						return 2; /* No match */
					}
				}
				fprintf(pFile, "%d %d ", typ, number);
			} /* End of i for loop */
		} /* End of j for loop */

		/* Save Logfile */
		assert(lf->number);
		i = lf->number;
		fprintf(pFile, "%d ", i);
		p = lf->First;
		assert(p);
		for (j = 0; j < i; j++) {
			fprintf(pFile, "%d %d %d %d %d ", p->Tar.x, p->Tar.y, p->Des.x, p->Des.y, p->condition);
			p = p->Next;
		}
		fclose(pFile);
	}
	return 0;
}

int Loadboard(char inFileName[32], SQUARE board[][8], PIECE *grave[2][16])
{
	int i, j;
	int fetch; /* Get ID */
	int fetch2; /* Get Status */
	int fetch3; /* Get number(index) */
	int bonus; /* For calculating Pawn's value */
	int n, Tar_x, Tar_y, Des_x, Des_y, condition; 
	DIRECTION Tar, Des;/* For Logfile */
	char *in;

	in = &inFileName[0];
	FILE *pFile;
	pFile = fopen(in, "r");
	if (pFile == NULL) {
		printf("Cannot open file!\n");
		return 1;
	}
	else  /* File Open Successfully */
	{
		/* Load Board */
		for (j = 7; j >= 0; j--) {
			for (i = 0; i < 8; i++) {
				fscanf(pFile, "%d", &fetch);
				fscanf(pFile, "%d", &fetch2);
				fscanf(pFile, "%d", &fetch3);
				printf("%d,%d,%d -- %d,%d\n", fetch, fetch2, fetch3, i, j);
				switch (fetch)
				{
				case 0: { /* Empty Square*/
						board[i][j].p = NULL;
						break;
					}
				case 1: { /* White King */
						board[i][j].p = Create_Piece('K', White, fetch2, Kingvalue, fetch3);
						break;
					}
				case -1: { /* Black King */
						board[i][j].p = Create_Piece('K', Black, fetch2, Kingvalue, fetch3);
						break;
					}
				case 2: { /* White Queen */
						board[i][j].p = Create_Piece('Q', White, fetch2, Queenvalue, fetch3);
						break;
					}
				case -2: { /* Black Queen */
						board[i][j].p = Create_Piece('Q', Black, fetch2, Queenvalue, fetch3);
						break;
					}
				case 3: { /* White Rook */
						board[i][j].p = Create_Piece('R', White, fetch2, Rookvalue, fetch3);
						break;
					}
				case -3: { /* Black Rook */
						board[i][j].p = Create_Piece('R', Black, fetch2, Rookvalue, fetch3);
						break;
						}
				case 4: { /* White Bishop */
						board[i][j].p = Create_Piece('B', White, fetch2, Bishopvalue, fetch3);
						break;
						}
				case -4: { /* Black Bishop */
						board[i][j].p = Create_Piece('B', Black, fetch2, Bishopvalue, fetch3);
						break;
						}
				case 5: { /* White Knight */
						board[i][j].p = Create_Piece('N', White, fetch2, Knightvalue, fetch3);
						break;
					}
				case -5: { /* Black Knight */
						board[i][j].p = Create_Piece('N', Black, fetch2, Knightvalue, fetch3);
						break;
						}
				case 6: { /* White Pawn */
						bonus = j - 1;
						board[i][j].p = Create_Piece('P', White, fetch2, Pawnvalue, fetch3 + bonus);
						break;
						}
				case -6: { /* Black Pawn */
						bonus = 6 - j;
						board[i][j].p = Create_Piece('P', Black, fetch2, Pawnvalue, fetch3 + bonus);
						break;
						}
				default:
					return 3; /* No match, Error */
				} /* End of Switch */
			} /* End of i for loop */
		} /* End of j for loop */

		/* Load Grave */
		i = 0;
		j = 0;
		printf("Load Gave Start!\n");
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 16; j++) {
				fscanf(pFile, "%d", &fetch);
				fscanf(pFile, "%d", &fetch3);
				printf("%d\n", fetch);
				switch (fetch)
				{
				case 0: { /* Empty Square*/
					grave[i][j] = NULL;
					break;
				}
				/* i=0 Black, i=1 White*/
				case 2: { /* Queen */
					grave[i][j] = Create_Piece('Q', i, 2, Queenvalue, fetch3);
					break;
				}
				case 3: { /* Rook */
					grave[i][j] = Create_Piece('R', i, 2, Rookvalue, fetch3);
					break;
				}
				case 4: { /* Bishop */
					grave[i][j] = Create_Piece('B', i, 2, Bishopvalue, fetch3);
					break;
				}
				case 5: { /* Knight */
					grave[i][j] = Create_Piece('N', i, 2, Knightvalue, fetch3);
					break;
				}
				case 6: { /* Pawn */
					grave[i][j] = Create_Piece('B', i, 2, Pawnvalue , fetch3);
					break;
				}
				default:
					return 4; /* No match, Error */
				} /* End of Switch */
			} /* End of i for loop */
		} /* End of j for loop */

		/* Load Logfile */
		fscanf(pFile, "%d", &n);
		for (i = 0; i < n; i++) {
			fscanf(pFile, "%d %d %d %d %d", &Tar_x, &Tar_y, &Des_x, &Des_y, &condition);
			Tar.x = Tar_x;
			Tar.y = Tar_y;
			Des.x = Des_x;
			Des.y = Des_y;
			NewLogFile(Tar, Des, condition, lf);
		}
		fclose(pFile);
		if (i % 2 == 1) {
			return 0;
		}
	} /* End of else */

	return 1;
}

int NewLogFile(DIRECTION tar, DIRECTION des, int condition, LIST *lf) {
	ENTRY *en;

	assert(lf);
	en = malloc(sizeof(ENTRY));
	assert(en);
	en->Tar = tar;
	en->Des = des;
	en->condition = condition;
	if (lf->number == 0) { /* First Entry */
		en->Prev = NULL;
		en->Next = NULL;
		lf->number = 1;
		lf->First = en;
		lf->Last = en;
		en->index = 0;
		return 1;
	}
	else {
		assert(lf->Last);
		en->Prev = lf->Last;
		en->Next = NULL;
		lf->Last->Next = en;
		assert(lf->number);
		en->index = lf->number + 1;
		lf->Last = en;
		lf->number++;
	}

	return 1;
}

int Undo(LIST *lf, SQUARE board[][8], PIECE *grave[][16]) {
	int des_x, des_y, tar_x, tar_y;
	int condition;
	int color;
	int i = 0;
	ENTRY *p;
	assert(lf);
	if (lf->number == 0) {
		return 9; /* No Steps record available */
	}
	else {
		des_x = lf->Last->Tar.x;
		des_y = lf->Last->Tar.y;
		tar_x = lf->Last->Des.x;
		tar_y = lf->Last->Des.y;
		condition = lf->Last->condition;
		/* Undo Movement */
		switch (condition)
		{
		case 0: {	/* 0= move to a blank square, piece status changed*/
			assert(board[tar_x][tar_y].p);
			board[des_x][des_y].p = board[tar_x][tar_y].p;
			board[tar_x][tar_y].p = NULL;
			board[des_x][des_y].p->status = 0;
			break;
		}
		case 1: {	/* 1= move to a blank square, piece status no change */
			assert(board[tar_x][tar_y].p);
			board[des_x][des_y].p = board[tar_x][tar_y].p;
			board[tar_x][tar_y].p = NULL;
			board[des_x][des_y].p->status = 1;
			break;
		}
		case 2: {	/* A non-inital status piece captured a non-initial piece */
			assert(board[tar_x][tar_y].p);
			board[des_x][des_y].p = board[tar_x][tar_y].p;
			board[tar_x][tar_y].p = NULL;
			/* Find the captured piece in grave and revive it */
			color = 1 - board[des_x][des_y].p->color;
			while (grave[color][i] != NULL) {
				i++;
			}
			i--;
			board[tar_x][tar_y].p = grave[color][i];
			grave[color][i] = NULL;
			board[tar_x][tar_y].p->status = 1;
			board[tar_x][tar_y].p->status = 1;
			break;
		}
		case 3: {	/* A non-inital status piece captured a initial piece */
			assert(board[tar_x][tar_y].p);
			board[des_x][des_y].p = board[tar_x][tar_y].p;
			board[tar_x][tar_y].p = NULL;
			/* Find the captured piece in grave and revive it */
			color = 1 - board[des_x][des_y].p->color;
			while (grave[color][i] != NULL) {
				i++;
			}
			i--;
			board[tar_x][tar_y].p = grave[color][i];
			grave[color][i] = NULL;
			board[tar_x][tar_y].p->status = 0;
			board[tar_x][tar_y].p->status = 1;
			break;
		}
		case 4: {	/* A inital status piece captured a non-initial piece */
			assert(board[tar_x][tar_y].p);
			board[des_x][des_y].p = board[tar_x][tar_y].p;
			board[tar_x][tar_y].p = NULL;
			/* Find the captured piece in grave and revive it */
			color = 1 - board[des_x][des_y].p->color;
			while (grave[color][i] != NULL) {
				i++;
			}
			i--;
			board[tar_x][tar_y].p = grave[color][i];
			grave[color][i] = NULL;
			board[tar_x][tar_y].p->status = 1;
			board[tar_x][tar_y].p->status = 0;
			break;
		}
		case 5: {	/* A inital status piece captured a initial piece */
			assert(board[tar_x][tar_y].p);
			board[des_x][des_y].p = board[tar_x][tar_y].p;
			board[tar_x][tar_y].p = NULL;
			/* Find the captured piece in grave and revive it */
			color = 1 - board[des_x][des_y].p->color;
			while (grave[color][i] != NULL) {
				i++;
			}
			i--;
			board[tar_x][tar_y].p = grave[color][i];
			grave[color][i] = NULL;
			board[tar_x][tar_y].p->status = 0;
			board[tar_x][tar_y].p->status = 0;
			break;
		}
		default:
			break;
		}

		printf("Undo Movement Success!\n");
		/* Delete Logfile Entry */
		if (lf->number == 1) {
			assert(lf->Last);
			assert(lf->First);
			assert(lf->number);
			p = lf->Last;
			lf->Last = NULL;
			lf->First = NULL;
			lf->number = 0;
			free(p);
		}
		else {
			assert(lf->Last);
			p = lf->Last;
			assert(p->Prev);
			lf->Last = p->Prev;
			lf->number--;
			assert(p->Prev->Next);
			p->Prev->Next = NULL;
			p->Next = NULL;
			p->Prev = NULL;
			free(p);
		}
	}

	return 1;
}

int DelLogFile(LIST *lf) {
	int n, i;
	ENTRY *p;
	
	if (lf->number == 0) {
		return 0;
	}
	if (lf->number == 1) {
		printf("1");
		assert(lf->Last);
		assert(lf->First);
		assert(lf->number);
		p = lf->Last;
		lf->Last = NULL;
		lf->First = NULL;
		lf->number = 0;
		free(p);
	}
	else {
		n = lf->number;
		for (i = 1; i < n; i++) {
			printf("%d ", i);
			assert(lf->Last);
			p = lf->Last;
			assert(p->Prev);
			lf->Last = p->Prev;
			lf->number--;
			assert(p->Prev->Next);
			p->Prev->Next = NULL;
			p->Next = NULL;
			p->Prev = NULL;
			free(p);
		}
		assert(lf->Last);
		assert(lf->First);
		assert(lf->number);
		p = lf->Last;
		lf->Last = NULL;
		lf->First = NULL;
		lf->number = 0;
		free(p);
	}
	return 1;
}

DIRECTION getPosition(char userinput[32]) 
{
	int x, y;
	DIRECTION coordinate;

	/* Get Y coordinate */
	if (userinput[0] > 96) {
		x = userinput[0] - 97; /* upper case */
	}
	else
	{
		x = userinput[0] - 65; /* lower case */
	}

	/* Get X coordinate */
	y = userinput[1] - 49; /* number */
	assert(x < 8);
	assert(y < 8);
	assert(x>=0);
	assert(y>=0);

	coordinate.x = x;
	coordinate.y = y;
	return coordinate;
}

void Reset(SQUARE board[][8], PIECE *grave[][16], LIST *lf) {
	int i, j;
	PIECE *p;

	/* Delete Pieces on board */
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j].p != NULL) {
				p = board[i][j].p;
				assert(p);
				free(p);
				board[i][j].p = NULL;
			}
		}
	}

	/* Delete Pieces in grave */
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 16; j++) {
			if (grave[i][j] != NULL) {
				p = grave[i][j];
				assert(p);
				free(p);
				grave[i][j] = NULL;
			}
		}
	}

	/* Delete Logfile Record */
	DelLogFile(lf);
}
