#ifndef BACK
#define BACK
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
     int score;
     int temps;
     char playerName[20];
} ScoreInfo;

typedef struct
{
     SDL_Surface *spriteSheet;
     SDL_Rect Clips[8];
     int frames;
     int clipLoaded;
} animation;

typedef struct
{
     SDL_Surface *image[3];
     int stageLoaded;
     SDL_Rect camera;
     animation animation;
     animation rain;
} background;

void initBack(background *b);
void afficherback(background b, SDL_Surface *screen);
void scrolling(background *b, int direction, int pasAvancement);
void saveScore(ScoreInfo s, char nomfichier[]);
void bestScore(char *filename, ScoreInfo t[]);
void choseName(char playerName[], SDL_Surface *screen, int *continuer);
void showBestScore(ScoreInfo t[], SDL_Surface *screen, int *continuer);
void partageEcran(background b, SDL_Surface *screen);
#endif /* BACK */
