#include "perso.h"
void initPerso(Personne *p)

{
     p->nombredevie = 3;
    p->perso.posinscreen.x = 10;
    p->perso.posinscreen.y = 505;
    p->perso.posinscreen.w = 100;
    p->perso.posinscreen.h = 100;

 p->deplacerhaut=0;  
p->i=0;
p->j=0;
p->saut=0;
p->score=100;
    p->direction = 0; 
}
void afficherr(Image p, SDL_Surface *screen)
{
    SDL_BlitSurface(p.img, &p.posfromimg, screen, &p.posinscreen);
}
void afficher_perso(Personne p, SDL_Surface *screen)
{
    SDL_BlitSurface(p.images[p.i][p.j], NULL, screen, &p.perso.posinscreen);
}
void animerPerso(Personne *p){
     
if(p->action==1){ //kena fama action ma3neha deplacement
 p->i=p->direction;//p->i bech te5o ye 1 ye 0 suivant howa ween mechi ymin wela ysar
    if ( p->j  > 13)  p->j = -1;//kena swolet le5er sprite n3awed m lowel
    p->j+=1; }//kena mawsoltech lele5er n9adem

else if (p->action==0) {//kena mafamech action
 p->acceleration=0;//aceeleration raj3ha 0
  p->i=p->direction+2;//bech net3ad lel partie thenya mta3 l matrice ween how wa9ef
 
     if ( p->j > 13)  p->j = -1;
     p->j += 1; 
}
}
void MovePerso(Personne *p){

if(p->action){

if(p->perso.posinscreen.x<1100&&p->direction==0){ //medemni mawsoltech le5er lecran nejem n9adem
p->perso.posinscreen.x+=(10+p->acceleration);//n9adem bel acceleration
if(p->acceleration<10) p->acceleration+=1;//kol menzeed n9adem kol mata9wa l acceleration
}
else   
if(p->perso.posinscreen.x>0&&p->direction==1){ //mdemni mawsoltech lel le5er w n7eb narja3 nejem ama rjoo3 mla8er acceleration
p->perso.posinscreen.x-=15;
 
}
 

}}
void saut(Personne* p) {
 if(p->saut&&p->perso.posinscreen.y==505){///keni ena fel 9a3a w n7eb nagez
    p->deplacerhaut=1;}//na3ti l acces l saut
if(p->deplacerhaut==1){p->perso.posinscreen.y-=10;}//nemchi w na9aslo fel y kol mara mdemni 93ed nagez
if(p->perso.posinscreen.y<390-(p->acceleration*6)){p->deplacerhaut=0;}//ki noosel lel maxe nwa9ef tangez
if(p->deplacerhaut==0&&p->perso.posinscreen.y<505){//tawa ba3ed makamel nagez nraje3 l y leblsaetha bech yerja3 l niveaux mta3 l9a3a
   p->perso.posinscreen.y+=10; 
} 


}
void initilisation_newscore(Image *c)
{
    c->img = IMG_Load("images/new score.png");
    if (c->img == NULL)
    {
        fprintf(stderr, "error loding won img %s\n", TTF_GetError());
        return;
    }

    c->posinscreen.h = c->img->h;
    c->posinscreen.w = c->img->w;
    c->posinscreen.x = 0;
    c->posinscreen.y = 10;
};
void afficher_newscore(int score, SDL_Surface *screen, Image c,int x) {

 
    char scoreStr[10];
  

    // Load a font and set the text color
    TTF_Font *font = TTF_OpenFont("SIXTY.TTF", 28);
        if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit(1);
    }
    SDL_Color color = { 99, 175, 95 };//color font
 // Convert the score to a string
    SDL_snprintf(scoreStr, sizeof(scoreStr), "%d", score);
    // Create a surface for the time text
    SDL_Surface *scoresurface = TTF_RenderText_Solid(font, scoreStr, color);

    // Blit the time surface onto the screen surface
    SDL_Rect destRect = { x, 57, 0, 0 };

 
 
 // Blit the black surface to the screen
    SDL_BlitSurface(c.img, NULL, screen, &c.posinscreen);
     SDL_BlitSurface(scoresurface, NULL, screen, &destRect);

    // Free the time surface and font
    SDL_FreeSurface(scoresurface);
    TTF_CloseFont(font);

}

void initlise_matrice(Personne* p){
    // Initialize surface images
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i <= 14; i++) {
            char filename[50];
            sprintf(filename, "images/personnage/sprite%d_%d.png", j, i);
       
            p->images[j][i] = IMG_Load(filename);
            if (p->images[j][i] == NULL) {
                printf("Error loading image: %s\n", SDL_GetError());
            }
        }
    }
}
