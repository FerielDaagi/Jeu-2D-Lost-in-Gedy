#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "text.h"
#include <SDL/SDL_ttf.h>


void initText(Text *A)
{
	//position
	A->position.x=340;
	A->position.y=50;
	//couleur jeune
	A->textcolor.r=225;
	A->textcolor.g=255;
	A->textcolor.b=0;
	A->Font=TTF_OpenFont("test.ttf",50);
}
void libererText(Text A)
{	
	SDL_FreeSurface(A.surfaceText);
	TTF_CloseFont(A.Font);
}

void displayText(Text t,SDL_Surface *screen)
{
	t.surfaceText=TTF_RenderText_Solid(t.Font,"---------!Collision---------",t.textcolor);
	SDL_BlitSurface(t.surfaceText,NULL,screen,&t.position);
}


