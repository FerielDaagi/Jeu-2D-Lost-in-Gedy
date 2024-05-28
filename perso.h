#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_mixer.h>


typedef struct Image
{
	SDL_Rect posfromimg;  
	SDL_Rect posinscreen; 
	SDL_Surface *img;	 
} Image;

typedef struct Personne
{
	int nombredevie;
	int direction;

	int action;
	int saut;
	int deplacerhaut;
	int acceleration;
	int score;
	Image scoreimg;
	int bonus;
	int malus;
	int newscore;
	SDL_Surface *images[4][15]; 
	Image perso; 
    int i,j;
} Personne;
 





void animerPerso(Personne *p);
void MovePerso(Personne *p);
void saut(Personne *p);
void afficher_perso(Personne p, SDL_Surface *screen);
void afficher_newscore(int score, SDL_Surface *screen, Image c,int x) ;

void afficherr(Image p, SDL_Surface *screen);
void initilisation_newscore(Image *c);
void initlise_matrice(Personne* p);
void initPerso(Personne *p);
