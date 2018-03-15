#ifndef DISGRAPH_H
#define DISGRAPH_H

#include "Lib.h"


SDL_Surface *Loadgraph(char* bmpImage);
void drawImage(SDL_Surface *image, DIRECTION coordinate);
void updateScreen();
void Refresh();
DIRECTION convert(DIRECTION coordinate);




#endif
