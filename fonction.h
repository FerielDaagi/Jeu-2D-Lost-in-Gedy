#define SCREEN_W 1920
#define SCREEN_H 953
#ifndef ES
#define ES
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
    SDL_Surface *spriteSheet[3]; 
    SDL_Rect Clips[8];
    int side; 
    int frames;
    int clipLoaded;
}Animation;

typedef struct
{
    SDL_Rect pos; 
    Animation Animation;
    int col; 
} Ennemi;

void generate_Clips(SDL_Rect Clips[8], int frames, int frameWidth, int clipWidth, int clipHeight);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
void initEnnemi(Ennemi *e);
void afficherEnnemi(Ennemi e, SDL_Surface *screen);
void animerEnnemi(Ennemi *e);
void deplacer(Ennemi *e);
int collisionBB(SDL_Rect posp, SDL_Rect pose);
void freeEnnemie(Ennemi e);
void deplacerIA(Ennemi *e, SDL_Rect posPerso);
#endif 
