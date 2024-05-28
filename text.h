#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
typedef struct
{	SDL_Rect position;
	TTF_Font *Font;
	SDL_Surface *surfaceText;
	SDL_Color textcolor;
	char Text[80];
}Text;


void initText(Text *t);
void libererText(Text A);
void displayText(Text t,SDL_Surface *screen);
void displayText2(Text t,SDL_Surface *screen);
