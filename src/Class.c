#include "Class.h"
#include "assert.h"



void Setclass(SQUARE board[][8])
{

	SDL_Surface *image;
	DIRECTION coordinate;

	int V=75;

	int i = 0, j = 0;
	char* setchar[8][8];
	const char B[2] = "B";
	const char W[2] = "W";
	char tail[4];
	char CB[2], CW[2],WD[20],BD[20];
	char* N;

	strcpy(tail,".bmp");



	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8; i++) {
			if (board[i][j].p) {
				N = &board[i][j].p->name;


				strcpy(WD,"../src/White/");
				strcpy(BD,"../src/Black/"); 
				if (board[i][j].p->color == 0) {

					strcpy(CB, B);

					strcat(CB, N);

					strcat(CB,tail);
	
					setchar[i][j] = malloc(sizeof(BD));
					assert(setchar[i][j]);
					strcat(BD,CB);
					strcpy(setchar[i][j], BD);

					image= SDL_LoadBMP(setchar[i][j]);

					coordinate.x=i*V+47;
					coordinate.y=(7-j)*V;
					drawImage(image, coordinate);
					updateScreen(image);	
					free(setchar[i][j]);
				}
				else {
				
					strcpy(CW, W);
				
					strcat(CW, N);
				
					strcat(CW,tail);
			
					setchar[i][j] = malloc(sizeof(WD));
					assert(setchar[i][j]);
					strcat(WD, CW);
			
					strcpy(setchar[i][j], WD);

					image= SDL_LoadBMP(setchar[i][j]);

					coordinate.x=i*V+47;
					coordinate.y=(7-j)*V;

					drawImage(image, coordinate);
					updateScreen(image);
					free(setchar[i][j]);
					}
				}
			}
		}
}

void Singlemove(int c,SQUARE board[][8],DIRECTION Direct,DIRECTION DD)
{
	int i,j;
	SDL_Surface *image;
	DIRECTION coordinate;
	int V=75;
	char* setchar[8][8];
	const char B[2] = "B";
	const char W[2] = "W";
	char tail[4];
	char CB[2], CW[2],WD[20],BD[20];
	char* N;
	int x,y;
	
	x=DD.x;
	y=DD.y;
	i=Direct.x;
	j=Direct.y;


	strcpy(tail,".bmp");
	strcpy(WD,"../src/White/");
	strcpy(BD,"../src/Black/"); 
		
		
		N = &board[i][j].p->name;
		if(board[i][j].p->color == 0)
		{	 
			strcpy(CB, B);
			strcat(CB, N);
			strcat(CB,tail);
			setchar[i][j] = malloc(sizeof(BD));
			assert(setchar[i][j]);
			strcat(BD,CB);
			strcpy(setchar[i][j], BD);

			image= SDL_LoadBMP(setchar[i][j]);



			coordinate.x=i*V+47;
			coordinate.y=(7-j)*V;
			drawImage(image, coordinate);
			updateScreen(image);
		}
		else
		{
			strcpy(CW, W);
				
			strcat(CW, N);
				
			strcat(CW,tail);
			
			setchar[i][j] = malloc(sizeof(WD));
			assert(setchar[i][j]);
			strcat(WD, CW);
			
			strcpy(setchar[i][j], WD);
			
				


					/*strcat(WD,CW);
					class=WD;*/




			image= SDL_LoadBMP(setchar[i][j]);

			coordinate.x=i*V+47;
			/*printf("%d\n",coordinate.x);*/
			coordinate.y=(7-j)*V;
			/*printf("%d\n",coordinate.y);*/
			drawImage(image, coordinate);
			updateScreen(image);


		}
		
		if(board[i][j].p != NULL && board[x][y].p != NULL)
		{
		N = &board[x][y].p->name;
		i=x;
		j=y;
		if( board[i][j].p->color == 0 )
		{	
			strcpy(CB, B);
			strcat(CB, N);
			strcat(CB,tail);
			setchar[i][j] = malloc(sizeof(BD));
			assert(setchar[i][j]);
			strcat(BD,CB);
			strcpy(setchar[i][j], BD);

			image= SDL_LoadBMP(setchar[i][j]);
			/*printf("%s\n",setchar[i][j]);*/



			coordinate.x=i*V+47;
			coordinate.y=(7-j)*V;
			drawImage(image, coordinate);
			updateScreen(image);
		}
		else
		{
			strcpy(CW, W);
				
			strcat(CW, N);
				
			strcat(CW,tail);
			
			setchar[i][j] = malloc(sizeof(WD));
			assert(setchar[i][j]);
			strcat(WD, CW);
			
			strcpy(setchar[i][j], WD);
			
				


					/*strcat(WD,CW);
					class=WD;*/




			image= SDL_LoadBMP(setchar[i][j]);

			coordinate.x=i*V+47;
			/*printf("%d\n",coordinate.x);*/
			coordinate.y=(7-j)*V;
			/*printf("%d\n",coordinate.y);*/
			drawImage(image, coordinate);
			updateScreen(image);


		}


		}
		
		




}

void ReplaceBlock(int c, SQUARE board[][8],DIRECTION Direct)
{
	int sum;
	char wtw[40];
	char btb[40];
	SDL_Surface *image;
	int V=75;
	DIRECTION coordinate;
	coordinate.x=Direct.x;
	coordinate.y=Direct.y;
	
	strcpy(wtw,"../src/Block/WtW.bmp");
	strcpy(btb,"../src/Block/BtB.bmp");	

	sum = Direct.x + Direct.y;
	if(sum%2 == 0)
	{
		image=SDL_LoadBMP(btb);
		coordinate.x=coordinate.x*V+48;
		coordinate.y=(7-coordinate.y)*V+1;
		drawImage(image, coordinate);
		updateScreen(image);
	}
	else
	{
		image=SDL_LoadBMP(wtw);
		coordinate.x=coordinate.x*V+48;
		coordinate.y=(7-coordinate.y)*V+1;
		drawImage(image, coordinate);
		updateScreen(image);
	}




}

void Gyard(PIECE *grave[2][16])
{
	int i,j;
	int x1=0,x2=0,y1=0,y2=0;
	char WD[60];
	char BD[60];
	SDL_Surface *image;
	int V=35;
	DIRECTION coordinate;

	char* setchar[2][16];
	const char B[2] = "B";
	const char W[2] = "W";
	char tail[4];
	char CB[2], CW[2];
	char* N;

	strcpy(tail,".bmp");


	for(i=0;i<2;i++){
		for(j=0;j<16;j++){
		
			
			strcpy(BD,"../src/Block/DBlack/");
			strcpy(WD,"../src/Block/DWhite/");
			if(grave[i][j] == NULL)
			{
				continue;
			}
			else if(i==0)
			{
				N = &grave[i][j]->name;

				strcpy(CB, B);
				
				strcat(CB, N);
				
				strcat(CB,tail);

				
				coordinate.x=647;
				coordinate.y=0;
				setchar[i][j] = malloc(sizeof(BD));
				assert(setchar[i][j]);
				strcat(BD, CB);
				strcpy(setchar[i][j], BD);




				image=SDL_LoadBMP(setchar[i][j]);
				coordinate.x=coordinate.x+V*x1;
				coordinate.y=coordinate.y+V*y1;
				drawImage(image, coordinate);
				updateScreen(image);
				x1++;
				if(x1 == 4 || x1 == 8 || x1 == 12 || x1 == 16)
				{
					y1++;
					x1=0;
				}
			}
			else if(i==1)
			{	
				N = &grave[i][j]->name;

				strcpy(CW, W);
				strcat(CW, N);
				strcat(CW,tail);
				
				coordinate.x=647;
				coordinate.y=450;
				setchar[i][j] = malloc(sizeof(WD));
				assert(setchar[i][j]);
				strcat(WD,CW);
				strcpy(setchar[i][j], WD);

				image=SDL_LoadBMP(setchar[i][j]);
				coordinate.x=coordinate.x+V*x2;
				coordinate.y=coordinate.y+V*y2;
				drawImage(image, coordinate);
				updateScreen(image);
				x2++;
				if(x2 == 4 || x2 == 8 || x2 == 12 || x2 == 16)
				{
					y2++;
					x2=0;
				}
			}
				
		}


	}	







}
