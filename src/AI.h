#ifndef AI_H
#define AI_H

#include <stdio.h>
#include "Piece.h"
#include "Rules.h"
#include "Type.h"
#include "GUI.h"
typedef struct{
	int capcount;
	int count;
	DIRECTION *step;/* all possible moves*/
}VALID_STEPS;

typedef struct{
	DIRECTION start_pos;
	DIRECTION end_pos;
}CURRENT_MOVE;
VALID_STEPS SearchSteps(SQUARE board[][8], int tar_x, int tar_y);

int FindAllLegalMove(SQUARE board[][8],int color,CURRENT_MOVE possibleMove[1000]);

CURRENT_MOVE AIMove(SQUARE board[][8],int color);

int user_min(SQUARE board[][8],int color);

int max_AI(SQUARE board[][8],DIRECTION tar_dir, DIRECTION des_dir);

#endif
