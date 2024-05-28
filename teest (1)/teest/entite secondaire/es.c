#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "es.h"

void generate_Clips(SDL_Rect Clips[8], int frames, int frameWidth, int clipWidth, int clipHeight)
{
    int i, w;
    for (w = 0, i = 0; i < frames; i++, w += frameWidth)
    { // boucle pour bech kol mara n7el taswira mel 4
        Clips[i].x = w;
        Clips[i].y = 0;
        Clips[i].w = clipWidth;  // 3ordh el taswira
        Clips[i].h = clipHeight; // toul el taswira
    }
}
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect offset; // to create a rectangle
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, NULL, destination, &offset);
}

void initEnnemi(Ennemi *e)
{
    e->pos.x = 400;
    e->pos.y = 600;
    e->pos.w = 300;
    e->pos.h = 484;
    e->col = 0;
    e->animation.spriteSheet[0] = IMG_Load("spritesheet/leftsheet.png");
    e->animation.spriteSheet[1] = IMG_Load("spritesheet/rightsheet.png");
    e->animation.frames = 4;
    e->animation.side = 1;
    e->animation.clipLoaded = 0;
    generate_Clips(e->animation.Clips, e->animation.frames, 163, 132, 150); // 132 3ordh taswiret el ennemie 150 howa el toul
}

void afficherEnnemi(Ennemi e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.animation.spriteSheet[e.animation.side], &e.animation.Clips[e.animation.clipLoaded], screen, &e.pos);
    // blitsurface hiya tatbaa taswira aala el rcrans
    // parametre lowla hiya mnin el tloadi fel taswira
    // parametre thenya el taswira el loaditha eli hiya taswira lowla mel 4
    // parametre thelya win bech tatba3ha el hiya aal ecrans
    // parametre el rab3a el blassa fin
}

void animerEnnemi(Ennemi *e)
{
    if (SDL_GetTicks() % 5 == 0)
    {
        e->animation.clipLoaded++;                          //  el animation 9a3da t9adem
        if (e->animation.clipLoaded >= e->animation.frames) // kif tfout 3dad el tsawer
            e->animation.clipLoaded = 0;                    // traj3ou lel taswira lowla
    }
}

void deplacer(Ennemi *e)
{
    if (e->animation.side == 1) // kan howa mechi aal limin
    {
        e->pos.x += 50;      // tzid fel x 50
        if (e->pos.x >= 800) // kan yokhrej mel map traj3ou lel blassa lowla
            e->animation.side = 0;
        animerEnnemi(e);
    }
    else if (e->animation.side == 0)
    {
        e->pos.x -= 50;            // tna9ess 50 khater mechi aal lisar
        if (e->pos.x <= 200)       // kif youssel el point 0
            e->animation.side = 1; // bech yarjaa yemchi aal limin
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
        return 1; // 1 kan les deux carro massou fi baadhhom
    }
    else
    {
        return 0; // kan mamasouch fi baadhhom
    }
}

void freeEnnemie(Ennemi e)
{
    SDL_FreeSurface(e.animation.spriteSheet[0]); // el taswira na7itha mel ram
    SDL_FreeSurface(e.animation.spriteSheet[1]);
}

void deplacerIA(Ennemi *e, SDL_Rect posPerso)
{
    int diff = e->pos.x - posPerso.x;
    if (diff > 100 && diff < 200 && e->pos.x >= 400)
    {
        e->pos.x -= 15;
        e->animation.side = 0;
        animerEnnemi(e);
    }
    else if (diff < -200 && diff > -400 && e->pos.x <= 1200)
    {
        e->pos.x += 15;
        e->animation.side = 1;
        animerEnnemi(e);
    }
    else if (diff >= 50 && diff <= 100)
    {
        e->animation.clipLoaded = 0;
        return;
    }
    else if (diff <= -150 && diff >= -200)
    {
        e->animation.clipLoaded = 0;
        return;
    }
    else
    {
        deplacer(e);
    }
}