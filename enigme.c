#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "SDL_rotozoom.h"
#include <time.h>
#include "enigme.h"

void renderText(SDL_Surface *screen, TTF_Font *font, SDL_Color color, char *text, int x, int y)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color);

    SDL_BlitSurface(textSurface, NULL, screen, &pos);
SDL_FreeSurface(textSurface);
textSurface=NULL;
}
void init_enigme(enigme *e)
{
    int i, w;

    e->p.x = 0;
    e->p.y = 0;
    e->img = NULL;

    e->animationn.SpriteSheet = IMG_Load("enigme/anime.png");
    e->animationn.ClipLoaded = 0;
    e->animationn.pos.x = 700;
    e->animationn.pos.y = 200;
    e->animationn.frames = 5;

    for (i = 0, w = 0; i < e->animationn.frames; i++, w = w + 137)
    {
        e->animationn.Clips[i].w = 100;
        e->animationn.Clips[i].h = 301;
        e->animationn.Clips[i].x = w;
        e->animationn.Clips[i].y = 0;
    }
}

void generate_afficher(SDL_Surface *screen, enigme *e, int *alea)
{
    int test = *alea;

    int a, b, c, ans1, ans2, r;
    srand(time(NULL));
    FILE *f;
    f = fopen("enigme.txt", "r");

    do
    {
        *alea = rand() % 3;
    } while (*alea == test);

    int i = 0;
    char image[30];

    while (fscanf(f, "%s %d\n", image, &e->selectedEnigme) != EOF && i != *alea)
        i++;

    switch (e->selectedEnigme)
    {
    case 1:

        b = rand() % 20 + 1;
        c = rand() % 20 + 1;

        a = sqrt(pow(b, 2) + pow(c, 2));

        ans1 = a + rand() % 10 + 1;
        ans2 = a - rand() % 10 - 1;

        e->triangle.tableauChoix[0] = a;
        e->triangle.tableauChoix[1] = ans1;
        e->triangle.tableauChoix[2] = ans2;

        for (int i = 2; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int temp = e->triangle.tableauChoix[i];
            e->triangle.tableauChoix[i] = e->triangle.tableauChoix[j];
            e->triangle.tableauChoix[j] = temp;
        }

        e->triangle.reponseCorrect = a;
        e->triangle.b = b;
        e->triangle.c = c;
        break;
    case 2:
        b = rand() % 20 + 1;
        c = rand() % 20 + 1;

        a = b * c;

        ans1 = a + rand() % 10 + 1;
        ans2 = a - rand() % 10 - 1;

        e->rectangle.tableauChoix[0] = a;
        e->rectangle.tableauChoix[1] = ans1;
        e->rectangle.tableauChoix[2] = ans2;

        for (int i = 2; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int temp = e->rectangle.tableauChoix[i];
            e->rectangle.tableauChoix[i] = e->rectangle.tableauChoix[j];
            e->rectangle.tableauChoix[j] = temp;
        }

        e->rectangle.reponseCorrect = a;
        e->rectangle.b = b;
        e->rectangle.c = c;
        break;
    case 3:
        r = rand() % 20 + 1;

        a = (pow(r, 2) / 4) * 3.14;

        ans1 = a + rand() % 10 + 1;
        ans2 = a - rand() % 10 - 1;

        e->circle.tableauChoix[0] = a;
        e->circle.tableauChoix[1] = ans1;
        e->circle.tableauChoix[2] = ans2;

        for (int i = 2; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int temp = e->circle.tableauChoix[i];
            e->circle.tableauChoix[i] = e->circle.tableauChoix[j];
            e->circle.tableauChoix[j] = temp;
        }

        e->circle.reponseCorrect = a;
        e->circle.r = r;
        break;
    }

    e->img = IMG_Load(image);
}

int resolution(SDL_Surface *screen, enigme e, int *loop, int startTime)
{

    TTF_Font *font = NULL;
    font = TTF_OpenFont("Retro.ttf", 40);

    SDL_Color textColor = {255, 255, 255};
    SDL_Color questionColor = {0, 0, 0};

    SDL_Event event;
    int r = -1;
    int run = 1;
    int i;
    while (run)
    {
        int time = (SDL_GetTicks() / 1000) - startTime;

        switch (time)
        {
        case 3:
            e.animationn.ClipLoaded = 1;
            break;
        case 6:
            e.animationn.ClipLoaded = 2;
            break;
        case 9:
            e.animationn.ClipLoaded = 3;
            break;
        case 12:
            e.animationn.ClipLoaded = 4;
            break;
        case 15:
            return r;
            break;
        }

        SDL_FillRect(screen, NULL, 0x00000);
        SDL_BlitSurface(e.img, NULL, screen, &e.p);
        SDL_BlitSurface(e.animationn.SpriteSheet, &e.animationn.Clips[e.animationn.ClipLoaded], screen, &e.animationn.pos);

        char timeToText[20];

        sprintf(timeToText, "%d", time);

        renderText(screen, font, textColor, timeToText, 750, 320);

        char variableB[20];
        char variableC[20];
        char reponseA[20];
        char reponseB[20];
        char reponseC[20];

        switch (e.selectedEnigme)
        {
        case 1:
            sprintf(variableB, "%d", e.triangle.b);
            sprintf(variableC, "%d", e.triangle.c);
            renderText(screen, font, questionColor, variableB, 300, 300);
            renderText(screen, font, questionColor, variableC, 100, 300);

            sprintf(reponseA, "A:%d", e.triangle.tableauChoix[0]);
            sprintf(reponseB, "B:%d", e.triangle.tableauChoix[1]);
            sprintf(reponseC, "C:%d", e.triangle.tableauChoix[2]);

            renderText(screen, font, questionColor, reponseA, 50, 350);
            renderText(screen, font, questionColor, reponseB, 50, 400);
            renderText(screen, font, questionColor, reponseC, 50, 450);
            break;
        case 2:
            sprintf(variableB, "%d", e.rectangle.b);
            sprintf(variableC, "%d", e.rectangle.c);
            renderText(screen, font, questionColor, variableB, 320, 220);
            renderText(screen, font, questionColor, variableC, 150, 170);

            sprintf(reponseA, "A:%d", e.rectangle.tableauChoix[0]);
            sprintf(reponseB, "B:%d", e.rectangle.tableauChoix[1]);
            sprintf(reponseC, "C:%d", e.rectangle.tableauChoix[2]);

            renderText(screen, font, questionColor, reponseA, 50, 350);
            renderText(screen, font, questionColor, reponseB, 50, 400);
            renderText(screen, font, questionColor, reponseC, 50, 450);
            break;
        case 3:
            sprintf(variableB, "%d", e.circle.r);
            renderText(screen, font, questionColor, variableB, 200, 190);

            sprintf(reponseA, "A:%d", e.circle.tableauChoix[0]);
            sprintf(reponseB, "B:%d", e.circle.tableauChoix[1]);
            sprintf(reponseC, "C:%d", e.circle.tableauChoix[2]);

            renderText(screen, font, questionColor, reponseA, 50, 350);
            renderText(screen, font, questionColor, reponseB, 50, 400);
            renderText(screen, font, questionColor, reponseC, 50, 450);
            break;

        default:
            break;
        }
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            *loop = 0;
            run = 0;
            r = -1;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                r = 0;
                run = 0;
                break;
            case SDLK_b:
                r = 1;
                run = 0;
                break;
            case SDLK_c:
                r = 2;
                run = 0;
                break;
            }
            break;
        }
    }

    return r;
}

void afficher_resultat(SDL_Surface *screen, int r, enigme *en)
{
    TTF_Font *font = NULL;
    font = TTF_OpenFont("Retro.ttf", 30);

    SDL_Color textColor = {255, 255, 255};

    SDL_Surface *text = NULL;

    int angle = 0;
    int zoom = 1;
    SDL_Event event;

    int loop = 1;
    while (loop)
    {

        SDL_FillRect(screen, NULL, 0x00000);

        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            loop = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                loop = 0;
                break;
            }
            break;
        }
        if (r == 1)
        {
            text = TTF_RenderText_Blended(font, "Good", textColor);
            en->img = rotozoomSurface(text, 0, zoom, 1);
        }
        else
        {

            text = TTF_RenderText_Blended(font, "Hard Luck", textColor);
            en->img = rotozoomSurface(text, angle, 1, 1);
        }
        SDL_BlitSurface(en->img, NULL, screen, &(en->p));

        if (SDL_GetTicks() % 300 == 0)
        {

            zoom += 1;
            if (zoom > 10)
                zoom = 1;

            angle += 30;
            if (angle >= 360)
                angle = 0;
        }
        renderText(screen, font, textColor, "Press q to quit", 0, 200);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(text);
    TTF_CloseFont(font);
}

int enigme6(SDL_Surface *screen1)
{
    SDL_Surface *screen;

    SDL_Event event;

    enigme e;

    SDL_Init(SDL_INIT_EVERYTHING);
	choix_menu monchoix=choix(screen);
    screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    TTF_Init();

    int loop = 1;

    int alea;
    int startTime;

    init_enigme(&e);

    TTF_Font *font = NULL;
    font = TTF_OpenFont("Retro.ttf", 30);

    SDL_Color textColor = {255, 255, 255};

    while (loop)
    {
        SDL_FillRect(screen, NULL, 0x00000);
        renderText(screen, font, textColor, "Press 'N' for the enigme", 0, 0);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_n:

                    startTime = SDL_GetTicks() / 1000;
                    generate_afficher(screen, &e, &alea);

                    int answer = resolution(screen, e, &loop, startTime);

                    if (answer != -1)
                    {    
                        switch (e.selectedEnigme)
                        {
                        case 1:
                            if (e.triangle.tableauChoix[answer] == e.triangle.reponseCorrect)
                               { afficher_resultat(screen, 1, &e);
                                return 1;
                                }
                            else
                            {
                                afficher_resultat(screen, -1, &e);
                                return 0;}
                            break;
                        case 2:
                            if (e.rectangle.tableauChoix[answer] == e.reponse)
                                {afficher_resultat(screen, 1, &e);
                                 return 1;}
                            else
                               { afficher_resultat(screen, -1, &e);
                                 return 0;}
                            break;
                        case 3:
                            if (e.circle.tableauChoix[answer] == e.reponse)
                               { afficher_resultat(screen, 1, &e);
                                 return 1;}
                            else
                                {afficher_resultat(screen, -1, &e);
                                 return 0;}
                            break;
                        }
                    }
                    break;
                }
            }

            SDL_Flip(screen);
        }
    }

    TTF_Quit();
    SDL_Quit();
    return 0;
}


choix_menu choix(SDL_Surface *screen)
{
screen = SDL_SetVideoMode(750, 450, 32, SDL_SWSURFACE);
SDL_Surface* bg1=IMG_Load("choix_perso.png");
SDL_Surface* bg2=IMG_Load("choix_input.png");
SDL_Surface* c1=IMG_Load("rajel.png");
SDL_Surface* c2=IMG_Load("mra.png");
SDL_Surface* c3=IMG_Load("manette.png");
SDL_Surface* c4=IMG_Load("clavier.png");
choix_menu monchoix; 
int loop=0,ch=-1;
SDL_Event event;
SDL_BlitSurface(bg1,NULL,screen,NULL);SDL_Flip(screen);
while(ch==-1)
{	SDL_PollEvent(&event);
        if(event.type==SDL_KEYDOWN)
{if(event.key.keysym.sym==257)//num 1
ch=1;
if(event.key.keysym.sym==258)//num 2
ch=2;
}
}
monchoix.joueur=ch;
if(ch==1)
SDL_BlitSurface(c1,NULL,screen,NULL);
else
SDL_BlitSurface(c2,NULL,screen,NULL);
SDL_Flip(screen);
SDL_Delay(2000);
ch=-1;
SDL_BlitSurface(bg2,NULL,screen,NULL);SDL_Flip(screen);
while(ch==-1)
{	SDL_PollEvent(&event);
        if(event.type==SDL_KEYDOWN)
{if(event.key.keysym.sym==257)
ch=1;
if(event.key.keysym.sym==258)
ch=2;
}
}
monchoix.input=ch;
if(ch==1)
SDL_BlitSurface(c3,NULL,screen,NULL);
else
SDL_BlitSurface(c4,NULL,screen,NULL);
SDL_Flip(screen);
SDL_Delay(2000);
printf("choix1:%d\nchoix2:%d\n",monchoix.joueur,monchoix.input);
return monchoix;
}


/**lot5**/

void showText5(SDL_Surface *screen, TTF_Font *font, SDL_Color color, char *text, int x, int y)
{   SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color);

    SDL_BlitSurface(textSurface, NULL, screen, &pos);
    SDL_FreeSurface(textSurface);
}
void init_enigme5(enigme5 *e)
{
    int i, w;

    e->font = TTF_OpenFont("Retro.ttf", 20);
    e->PosQuestion.x = 80;
    e->PosQuestion.y = 100;
    e->PosReponse[0].x = 80;
    e->PosReponse[0].y = 300;
    e->PosReponse[1].x = 80;
    e->PosReponse[1].y = 400;
    e->PosReponse[2].x = 80;
    e->PosReponse[2].y = 500;
    e->ImageResulta = NULL;
    e->background = IMG_Load("lot5/page.png");
    e->animation.SpriteSheet = IMG_Load("lot5/animer.png");
    e->animation.pos.x = 600;
    e->animation.pos.y = 50;

    e->animation.frames = 5;
    e->animation.ClipLoaded = 0;
    for (i = 0, w = 0; i < e->animation.frames; i++, w += 265)
    {
        e->animation.Clips[i].w = 250;
        e->animation.Clips[i].h = 400;
        e->animation.Clips[i].x = w;
        e->animation.Clips[i].y = 0;
    }
}
void generate_afficher5(SDL_Surface *screen, enigme5 *e, int *alea)
{

    SDL_Color textColor = {0, 0, 0};



    int test = *alea;
    FILE *f;
    f = fopen("lot5.txt", "r");

    do
    {
        *alea = rand() % 3;
    } while (*alea == test);
    int i = 0;
    char enigmeFull[200];

    for (i = 0; i <= *alea; i++)
        fgets(enigmeFull, 200, f);
 char *partieDuString = strtok(enigmeFull, ":"); 
    int j = 0;

    while (partieDuString != NULL)    {
        if (j == 0)
            e->question = TTF_RenderText_Solid(e->font, partieDuString, textColor);
        else if (j == 4)
            e->reponse = atoi(partieDuString);
        else
            // j=2-1 =1
            e->reponses[j - 1] = TTF_RenderText_Solid(e->font, partieDuString, textColor);
        partieDuString = strtok(NULL, ":"); 
        j++;
    }
    fclose(f);
}
int resolution5(SDL_Surface *screen, enigme5 e, int *loop, int startTime)
{

    SDL_Color textColor = {255, 255, 255};
    SDL_Event event;
    int r = 0;
    int run = 1;
    while (run)
    {
        int time = (SDL_GetTicks() / 1000) - startTime;
        switch (time)
        {
        case 3:
            e.animation.ClipLoaded = 1;
            break;
        case 6:
            e.animation.ClipLoaded = 2;
            break;
        case 9:
            e.animation.ClipLoaded = 3;
            break;
        case 12:
            e.animation.ClipLoaded = 4;
            break;
        case 15:
            return -1;
            break;
        }

        SDL_FillRect(screen, NULL, 0x00000);
        SDL_BlitSurface(e.background, NULL, screen, NULL);
        SDL_BlitSurface(e.question, NULL, screen, &e.PosQuestion);
        SDL_BlitSurface(e.reponses[0], NULL, screen, &e.PosReponse[0]);
        SDL_BlitSurface(e.reponses[1], NULL, screen, &e.PosReponse[1]);
        SDL_BlitSurface(e.reponses[2], NULL, screen, &e.PosReponse[2]);
SDL_BlitSurface(e.animation.SpriteSheet,&e.animation.Clips[e.animation.ClipLoaded], screen, &e.animation.pos);
        char timeToText[20];
        sprintf(timeToText, "%d", time);
        showText5(screen, e.font, textColor, timeToText, 700, 500);
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            *loop = 0;
            run = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                r = 1;
                run = 0;
                break;
            case SDLK_b:
                r = 2;
                run = 0;
                break;
            case SDLK_c:
                r = 3;
                run = 0;
                break;
            }
            break;
        }
    }
    return r;
}
void afficher_resultat5(SDL_Surface *screen, int juste, enigme5 *en)
{

    SDL_Color textColor = {255, 255, 255};
    SDL_FillRect(screen, NULL, 0x00000);
    if (juste == 1)
    {
        en->ImageResulta = IMG_Load("win.png");
        SDL_BlitSurface(en->ImageResulta, NULL, screen, NULL);
    }
    else
    {
        en->ImageResulta = IMG_Load("lose.png");
        SDL_BlitSurface(en->ImageResulta, NULL, screen, NULL);
    }
    showText5(screen, en->font, textColor, "Press T to try again!", 0, 180);
    SDL_Flip(screen);
}



int enigme5_tache(SDL_Surface *screen1)
{
    SDL_Surface *screen;
    SDL_Event event;
    enigme5 e;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    TTF_Init();
    int loop = 1;
    int alea;
    int startTime;
    init_enigme5(&e);
    SDL_Color textColor = {255, 255, 255};
    showText5(screen, e.font, textColor, "Press T for the enigme", 0, 0);
    while (loop)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            loop = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_t:
                startTime = SDL_GetTicks() / 1000;
                generate_afficher5(screen, &e, &alea);
                int answer = resolution5(screen, e, &loop, startTime); 
                  if (answer == e.reponse){
                    afficher_resultat5(screen,1,&e);
                    return 1;}
                else{
                    afficher_resultat5(screen,-1, &e);
                    return 0;}
                    break;			               
            }
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(e.background);
    SDL_FreeSurface(e.question);
    SDL_FreeSurface(e.reponses[0]);
    SDL_FreeSurface(e.reponses[1]);
    SDL_FreeSurface(e.reponses[2]);
    TTF_CloseFont(e.font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
/*
void sauvegarder6 (perso p,int stage,  char * nomfichier) 
{

    FILE* sauv=fopen(nomfichier,"w");
    if (sauv==NULL)
    {
        printf("\n erreur fichier");
    }

    fprintf(sauv,"%d %d %d",p.position.x,p.position.y,stage); 

}

*/

