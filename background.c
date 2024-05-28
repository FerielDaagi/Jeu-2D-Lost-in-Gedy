#include "background.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

void showText(SDL_Surface *surface, TTF_Font *font, SDL_Color color, char *text, int x, int y)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color);

    SDL_BlitSurface(textSurface, NULL, surface, &pos);
}

void choseName(char playerName[], SDL_Surface *screen, int *continuer)
{

    TTF_Font *font = NULL;
    font = TTF_OpenFont("Retro.ttf", 24);

    SDL_Color textColor = {255, 255, 255};

    SDL_Event event;

    int loop = 1;
    while (loop)
    {

        SDL_FillRect(screen, NULL, 0x000000);
        showText(screen, font, textColor, "Choose a name: ", 10, 10);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0;
                *continuer = 0;
                break;

            case SDL_KEYDOWN:
                if (strlen(playerName) < 20)
                {
                    if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) // ecandrement de a jusqu'a z
                    {
                        // SDL_GetKeyName(SDLK_1) = 1
                        strncat(playerName, SDL_GetKeyName(event.key.keysym.sym), 1);
                    }
                }
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(playerName) > 0)
                {
                    // asma asma[4] = '\0'
                    playerName[strlen(playerName) - 1] = '\0';
                }
                if (event.key.keysym.sym == SDLK_RETURN && strlen(playerName) > 0)
                {
                    loop = 0;
                }
                break;
            }
        }

        showText(screen, font, textColor, playerName, 200, 50);

        SDL_Flip(screen);
    }
    TTF_CloseFont(font);
}
void initBack(background *b)
{
    int i, w;

    b->image[0] = IMG_Load("image/stage1.png");
    b->image[1] = IMG_Load("image/stage2.png");

    b->stageLoaded = 0;

    b->camera.x = 0;
    b->camera.y = 0;
    b->camera.h = 800;
    b->camera.w = 1000;

    b->animation.spriteSheet = IMG_Load("image/fire.png");
    b->animation.frames = 8;
    b->animation.clipLoaded = 0;

    for (i = 0, w = 0; i < b->animation.frames; i++, w += 185)
    {
        b->animation.Clips[i].w = 86;
        b->animation.Clips[i].h = 300;
        b->animation.Clips[i].x = w;
        b->animation.Clips[i].y = 0;
    }

    b->rain.spriteSheet = IMG_Load("image/rain_spritesheet.png");
    b->rain.frames = 8;
    b->rain.clipLoaded = 0;

    for (i = 0, w = 0; i < b->rain.frames; i++, w += 1000)
    {
        b->rain.Clips[i].w = 1000;
        b->rain.Clips[i].h = 800;
        b->rain.Clips[i].x = w;
        b->rain.Clips[i].y = 0;
    }
}
void afficherback(background b, SDL_Surface *screen)
{
    SDL_BlitSurface(b.image[b.stageLoaded], &b.camera, screen, NULL);
    SDL_BlitSurface(b.rain.spriteSheet, &b.rain.Clips[b.rain.clipLoaded], screen, NULL);
}
void scrolling(background *b, int direction, int pasAvancement)
{
    switch (direction)
    {
    case 1: // right
        b->camera.x += pasAvancement;
        break;

    case 2: // left
        if (b->camera.x > 0)
            b->camera.x -= pasAvancement;
        break;
    case 3: // up
        if (b->camera.y > 0)
            b->camera.y -= pasAvancement;
        break;

    case 4: // down
        b->camera.y += pasAvancement;
        break;
    }
}

void saveScore(ScoreInfo s, char nomfichier[])
{
    FILE *f;

    f = fopen(nomfichier, "a");
    if (f != NULL)
        fprintf(f, "%s %d %d\n", s.playerName, s.score, s.temps);
    fclose(f);
}

void bestScore(char *filename, ScoreInfo t[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return;
    }

    int n = 0;
    while (fscanf(fp, "%s %d %d", t[n].playerName, &t[n].score, &t[n].temps) != EOF)
    {
        n++;
    }

    fclose(fp);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (t[i].score < t[j].score || (t[i].score == t[j].score && t[i].temps > t[j].temps))
            {
                ScoreInfo tmp = t[i];
                t[i] = t[j];
                t[j] = tmp;
            }
        }
    }
}

void showBestScore(ScoreInfo t[], SDL_Surface *screen, int *continuer)
{
    TTF_Font *font = NULL;
    font = TTF_OpenFont("Retro.ttf", 12);

    SDL_Color textColor = {0, 0, 0};

    SDL_Surface *best;
    best = IMG_Load("image/best.png");

    SDL_Rect bestPos;
    bestPos.x = 200;
    bestPos.y = 0;

    SDL_BlitSurface(best, NULL, screen, &bestPos);

    int y = 200;

    // 0 1 2
    for (int i = 0; i < 3; i++)
    {
        char nom[100];
        char info[100];

        sprintf(nom, "Nom: %s", t[i].playerName);
        sprintf(info, "Score: %d, Time: %d", t[i].score, t[i].temps);

        showText(screen, font, textColor, nom, 450, y);
        showText(screen, font, textColor, info, 450, y + 50);
        y += 130;
    }
    SDL_Flip(screen);
    int loop = 1;

    SDL_Event event;
    while (loop)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0;
                *continuer = 0;
                break;
            }
        }
    }
}
void partageEcran(background b, SDL_Surface *screen)
{
	SDL_Rect pos;pos.x=screen->w/2;pos.y=0;
    SDL_BlitSurface(b.image[b.stageLoaded], &b.camera, screen, &pos);
    SDL_BlitSurface(b.rain.spriteSheet, &b.rain.Clips[b.rain.clipLoaded], screen, &pos);
}
