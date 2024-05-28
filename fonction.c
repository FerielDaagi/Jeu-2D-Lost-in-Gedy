#include "fonction.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void generate_Clips(SDL_Rect Clips[8], int frames, int frameWidth, int clipWidth, int clipHeight)
{
    int i, w;
    for (w = 0, i = 0; i < frames; i++, w += frameWidth)
    { 
        Clips[i].x = w;
        Clips[i].y = 0;
        Clips[i].w = clipWidth;  
        Clips[i].h = clipHeight; 
    }
}
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect offset; 
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, NULL, destination, &offset);
}

void initEnnemi(Ennemi *e)
{
    e->pos.x = 600;
    e->pos.y = 500;
    e->pos.w = 300;
    e->pos.h = 484;
    e->col = 0;
    e->Animation.spriteSheet[0] = IMG_Load("leftsheet.png");
    e->Animation.spriteSheet[1] = IMG_Load("rightsheet.png");
    e->Animation.frames = 4;
    e->Animation.side = 1;
    e->Animation.clipLoaded = 0;
    generate_Clips(e->Animation.Clips, e->Animation.frames, 163, 132, 150); 
}

void afficherEnnemi(Ennemi e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.Animation.spriteSheet[e.Animation.side], &e.Animation.Clips[e.Animation.clipLoaded], screen, &e.pos);
}

void animerEnnemi(Ennemi *e)
{
    if (SDL_GetTicks() % 5 == 0)
    {
        e->Animation.clipLoaded++;                        
        if (e->Animation.clipLoaded >= e->Animation.frames) 
            e->Animation.clipLoaded = 0;                   
    }
}

void deplacer(Ennemi *e)
{
    if (e->Animation.side == 1) 
    {
        e->pos.x += 15;      
        if (e->pos.x >= 500) 
            e->Animation.side = 0;
        animerEnnemi(e);
    }
    else if (e->Animation.side == 0)
    {
        e->pos.x -= 15;            
        if (e->pos.x <= 350)      
            e->Animation.side = 1; 
        animerEnnemi(e);
    }
}

int collisionBB(SDL_Rect PosePerso, SDL_Rect PoseEnemie)
{
    if (
        PosePerso.x < PoseEnemie.x + PoseEnemie.w &&
        PosePerso.x + PosePerso.w > PoseEnemie.x &&

        PosePerso.y < PoseEnemie.y + PoseEnemie.h &&
        PosePerso.h + PosePerso.y > PoseEnemie.y)
    {
        return 1; 
    }
    else
    {
        return 0;
    }
}

void freeEnnemie(Ennemi e)
{
    SDL_FreeSurface(e.Animation.spriteSheet[0]); 
    SDL_FreeSurface(e.Animation.spriteSheet[1]);
}

void deplacerIA(Ennemi *e, SDL_Rect posPerso)
{
    int diff = e->pos.x - posPerso.x;
    if (diff > 100 && diff < 200 && e->pos.x >= 400)
    {
        e->pos.x -= 10;
        e->Animation.side = 0;
        animerEnnemi(e);
    }
    else if (diff < -200 && diff > -400 && e->pos.x <= 1200)
    {
        e->pos.x += 10;
        e->Animation.side = 1;
        animerEnnemi(e);
    }
    else if (diff >= 50 && diff <= 100)
    {
        e->Animation.clipLoaded = 0;
        return;
    }
    else if (diff <= -150 && diff >= -200)
    {
        e->Animation.clipLoaded = 0;
        return;
    }
    else
    {
        deplacer(e);
    }
}
