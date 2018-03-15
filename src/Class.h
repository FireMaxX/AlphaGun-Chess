#ifndef CLASS_H
#define CLASS_H

#include "Lib.h"
#include "Disgraph.h"


void Setclass(SQUARE board[][8]);
void Singlemove(int c, SQUARE board[][8],DIRECTION Direct, DIRECTION DD);
void ReplaceBlock(int c, SQUARE board[][8], DIRECTION Direct);
void Gyard(PIECE *grave[2][16]);

#endif 
