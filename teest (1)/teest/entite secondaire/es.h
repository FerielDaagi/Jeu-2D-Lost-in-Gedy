#ifndef ES
#define ES
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
    SDL_Surface *spriteSheet[3]; // 1: right 0:left
    SDL_Rect Clips[8];
    int side; // 1: right 2: left 0: dead
    int frames;
    int clipLoaded;
} animation;

typedef struct
{
    SDL_Rect pos; // position mtaa el enemie
    animation animation;
    int col; // 0: non colusion 1: colusion
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
#endif /* ES */
