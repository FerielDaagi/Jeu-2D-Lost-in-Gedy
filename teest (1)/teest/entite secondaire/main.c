#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> // lib mtaa les images
#include <SDL/SDL_ttf.h>   // lib mtaa text
#include "es.h"

// gcc main.c es.c -o prog 9otlou les fichiers main w es badalhom binaire w 7othom f fichier prog  bech texecutih

void main(int argc, char const *argv[])
{
    SDL_Surface *screen;

    SDL_Event event;

    Ennemi e;

    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    // SDL SET VIDEO MODE TROD SCREEN HIYA EL ECRANS MTE3EK
    //  32 bits
    //  SDL_HWSURFACE 3ibara 9otlou tnajm testaaml el processeur
    //  SDL_DOUBLEBUF 3ibara 9otlou tnajm testaaml el carte graphique
    SDL_Surface *backgroundGame = IMG_Load("game.jpg");
    int loop = 1;
    // boucle mtaa el jeu
    SDL_Rect perso;
    // SDL-Rect rectangle
    perso.x = 0;
    perso.y = 600;
    perso.w = 100;
    perso.h = 100;
    initEnnemi(&e);
    while (loop)
    {
        apply_surface(0, 0, backgroundGame, screen);
        afficherEnnemi(e, screen);
        SDL_FillRect(screen, &perso, 0xfcba03); // 0xfcba03 el couleur mtaa el box
        if (SDL_GetTicks() % 15 == 0)
            deplacerIA(&e, perso);
        if (collisionBB(e.pos, perso) == 1)
        {
            printf("Collision detected!!\n");
        }
        if (SDL_Flip(screen) == -1)
        { // sdl flip refresh el page
            return;
        }
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0; // loup = 0 yaani yokhrej mel boucle mtaa el jeu
                break;
                // SDL Quit bech tsaker el jeu el X eli mel fou9
            case SDL_KEYDOWN:                 // kif el bouton yet9rass
                switch (event.key.keysym.sym) // ta9ra les boutons eli fel clavier fel system
                {
                case SDLK_RIGHT:
                    perso.x += 50; // el rectangle yemchi aal limin
                    break;
                case SDLK_LEFT:
                    perso.x -= 50; // el rectangle yemchi aal lisar
                    break;
                }
                break;
            }
        }
    }

    TTF_Quit();
    SDL_Quit();
    return;
}
