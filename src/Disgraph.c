#include "Disgraph.h"


SDL_Surface *Loadgraph(char* bmpImage)
{
	SDL_Surface *temp;
	
	/*Load the bmpImage into the surface*/

	temp= SDL_LoadBMP(bmpImage);
	
	if(temp ==NULL)
	{
		fprintf(stderr, "Couldn't load %s: %s\n", bmpImage, SDL_GetError());


	}


	if(SDL_BlitSurface(temp, NULL, screen, NULL)<0)
	{
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
		
	}




	if (temp == NULL)
	{
		printf("Failed to convert image %s to native format\n", bmpImage);
		
	}
	


	return temp;

}

void drawImage(SDL_Surface *image, DIRECTION coordinate)
{
	SDL_Rect dest;
	
	/* Set the blitting rectangle to the size of the src image */
	
	dest.x = coordinate.x;
	dest.y = coordinate.y;
	dest.w = image->w;
	dest.h = image->h;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	
	SDL_BlitSurface(image, NULL, screen, &dest);

}

void updateScreen(SDL_Surface *image)
{
	SDL_UpdateRect(screen, 0, 0, image->w, image->h);

	
	/* Swap the image buffers */
	
	SDL_Flip(screen);
}

void Refresh()
{
	SDL_FillRect(screen, NULL, 0);
	SDL_Flip(screen);
}

DIRECTION convert(DIRECTION coordinate)
{
	/*This function is for converting the coordinate from ASCII 2x2 array to pixiel coordinate*/
	DIRECTION position;
	int x,y;
	int V=75;
	
	x=coordinate.x;
	y=coordinate.y;

	x=x*V+47;
	y=y*V;

	return position;

}
