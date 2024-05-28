#ifndef ENIGME
#define ENIGME

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
//lot6//
typedef struct
{
    SDL_Surface *SpriteSheet;
    SDL_Rect pos;
    SDL_Rect Clips[5];
    int frames;
    int ClipLoaded;
} animationn;

typedef struct
{
    int b;
    int c;
    int reponseCorrect;
    int tableauChoix[3];
} air;

typedef struct
{
    int r;
    int reponseCorrect;
    int tableauChoix[3];
} circle;

typedef struct
{
    SDL_Surface *img;
    SDL_Rect p;
    int reponse;
    int selectedEnigme;
    air triangle;
    air rectangle;
    circle circle;
    animationn animationn;
} enigme;

typedef struct{
int joueur;//1:homme 2:femme
int input;//1:manette 2:clavier 
}choix_menu;

/**lot5**/
typedef struct
{
    SDL_Surface *SpriteSheet;
    SDL_Rect pos;
    SDL_Rect Clips[5];
    int frames;
    int ClipLoaded;
} animation5;
typedef struct
{
    SDL_Surface *ImageResulta;
    SDL_Surface *question;
    SDL_Rect PosQuestion;

    SDL_Surface *background;
    TTF_Font *font;

    SDL_Surface *reponses[4];

    SDL_Rect PosReponse[4];

    int reponse;

    animation5 animation;
} enigme5;

/**lot5**/
int enigme5_tache(SDL_Surface *screen1);
void init_enigme5(enigme5 *e);
void generate_afficher5(SDL_Surface *screen, enigme5 *e, int *alea);
int resolution5(SDL_Surface *screen, enigme5 e, int *loop, int startTime);
void afficher_resultat5(SDL_Surface *screen, int r, enigme5 *en);
void showText5(SDL_Surface *surface, TTF_Font *font, SDL_Color color, char *text, int x, int y);


/**lot6**/

choix_menu choix(SDL_Surface *screen1);
void init_enigme(enigme *e);
void generate_afficher(SDL_Surface *screen, enigme *e, int *alea);
int resolution(SDL_Surface *screen, enigme e, int *loop, int startTime);
void afficher_resultat(SDL_Surface *screen, int r, enigme *en);
void renderText(SDL_Surface *surface, TTF_Font *font, SDL_Color color, char *text, int x, int y);
int enigme6(SDL_Surface *screen);
//void sauvegarder6 (perso p,int stage,  char * nomfichier) ;


#endif /* ENIGME */
