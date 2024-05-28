#include "perso.h"
#include <stdio.h>
#include <stdlib.h>
#include "background.h"
#include "fonction.h"
#include "song.h"
#include "text.h"
#include "enigme.h"


int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
    atexit(SDL_Quit);
   Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) ;
  
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        exit(1);
    }
         Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1000) ;
 
    Mix_Music *music = Mix_LoadMUS("images/soound/mm.mp3");
 
   Mix_PlayMusic(music, 1); 
    int done = 0;
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(1000, 645, 32, SDL_HWSURFACE | SDL_RESIZABLE);
    if (!screen)
    {
        printf("unable to set 1200x645 video: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Event event;
    Uint32 t_prev1, t_prev2,t_prev3;
    
    
    Personne player1;
    initPerso(&player1);
    initlise_matrice(&player1);
    
    Personne player2;
   initPerso(&player2);
    initlise_matrice(&player2);
   
    int multiplayer=1;
    
   
     player1.newscore = 300;
     player1.bonus = 1;
    player1.malus = 0;
      player2.newscore = 200;
     player2.bonus = 1;
    player2.malus = 0;   
    initilisation_newscore(&player1.scoreimg);
    initilisation_newscore(&player2.scoreimg);
    //
    player1.action=0;
    player2.action=0;
	//bg
    background b,b1;
    initBack(&b);
    initBack(&b1);
    ScoreInfo t[10];
    ScoreInfo s;
    s.score = 0;
    s.playerName[0] = '\0';
    int startTime = SDL_GetTicks() / 1000,temps;
    SDL_Rect firePos;
    firePos.y = 50;
    firePos.x = 200;
    //entite
	Mix_Chunk *son;
	int colli=0;
	Ennemi e;
	//Text tt;
    son=initSon();
    initEnnemi(&e);
    //initText(&tt);
    
	
if (Mix_PlayingMusic() == 0)
        {
            if (Mix_PlayMusic(music, -1) == -1)
            {
                return 0;
            }
        }
    while (!done)
    {

        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            done = 1;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                player1.direction = 0;
                player1.action = 1;
		scrolling(&b, 1, 1);
                if (firePos.x > 0)
                    firePos.x -= 10;

                if (b.camera.x > 6000)
                {
                    b.camera.x = 0;
                    b.camera.y = 0;
		}
                break;
            case SDLK_LEFT:
                player1.direction = 1;
                player1.action = 1;
		scrolling(&b, 2, 1);

                if (firePos.x < 600)
                    firePos.x += 10;
                break;
            case SDLK_UP:
                player1.saut = 1;
                break;
                         if(multiplayer==1){
            case SDLK_d:
                player2.direction = 0;
                player2.action = 1;

                break;
            case SDLK_q:
                player2.direction = 1;
                player2.action = 1;
                break;
            case SDLK_z:
                player2.saut = 1;
                break;}
            case SDLK_b:
                bestScore("best.txt", t);
                // tableau trier
                showBestScore(t, screen, &done);
                break;
            case SDLK_s:
                s.temps = temps;
                choseName(s.playerName, screen, &done);
                saveScore(s, "best.txt");
                done = 0;
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                player1.action = 0;

                break;
            case SDLK_LEFT:
                player1.action = 0;

                break;
            case SDLK_UP:
                player1.saut = 0;
                break;
                         if(multiplayer==1){
            case SDLK_d:
                player2.action = 0;

                break;
            case SDLK_q:
                player2.action = 0;

                break;
            case SDLK_z:
                player2.saut = 0;
                break;   }             
            }
            break;
        }
        
			//bg
		temps = (SDL_GetTicks() / 1000) - startTime;
        if (SDL_GetTicks() - t_prev1 > 20)
        {
                    if (SDL_GetTicks() % 5 == 0) // 5
        {
            if (b.animation.clipLoaded < b.animation.frames)
            {
                b.animation.clipLoaded++;
            }
            else
                b.animation.clipLoaded = 0;
        }
        if (SDL_GetTicks() % 5 == 0)
        {
            b.rain.clipLoaded++;
            if (b.rain.clipLoaded >= b.rain.frames)
                b.rain.clipLoaded = 0;
        }
          if (SDL_GetTicks() % 5 == 0) // 5
        {
            if (b1.animation.clipLoaded < b1.animation.frames)
            {
                b1.animation.clipLoaded++;
            }
            else
                b1.animation.clipLoaded = 0;
        } 
        if (SDL_GetTicks() % 5 == 0)
        {
            b1.rain.clipLoaded++;
            if (b1.rain.clipLoaded >= b1.rain.frames)
                b1.rain.clipLoaded = 0;
        }
        
        	afficherback(b, screen);
        	SDL_BlitSurface(b.animation.spriteSheet, &b.animation.Clips[b.animation.clipLoaded], screen, &firePos);
        	partageEcran(b1,screen);
        	//entite
        //	afficherObjet(o,screen);
        	if(colli<4){
        	afficherEnnemi(e,screen);
        	deplacerIA(&e,player1.perso.posinscreen);
			animerEnnemi(&e);
			/*if(collisionBB(e.pos,player1.perso.posinscreen)==1)
			{ 
			//displayText(tt,screen);
			//SDL_Flip(screen);
			//SDL_Delay(50);
			//PlaySon(son);
			e.pos.x=800;
			colli++;
			player1.perso.posinscreen.x=50;
			if(enigme6(screen)==1)
			player1.score+=300*colli;
			screen = SDL_SetVideoMode(1000, 645, 32, SDL_HWSURFACE | SDL_RESIZABLE);
			}*/
			if(collisionBB(e.pos,player2.perso.posinscreen)==1)
			{ 
			//displayText(tt,screen);
			SDL_Flip(screen);
			SDL_Delay(50);
			PlaySon(son);
			e.pos.x=1000;
			colli++;
			player2.perso.posinscreen.x=10;
			if(colli==1)
			{
			if(enigme6(screen)==1)
			player2.score+=300*colli;
			screen = SDL_SetVideoMode(1000, 645, 32, SDL_HWSURFACE | SDL_RESIZABLE);
			}
			if(colli==2)
			{
			if(enigme5_tache(screen)==1)
			{
			player2.score+=300*colli;
			player2.perso.posinscreen.x=10;
			}
			screen = SDL_SetVideoMode(1000, 645, 32, SDL_HWSURFACE | SDL_RESIZABLE);
			}
			}
			}
            //perso
            saut(&player1);
            MovePerso(&player1);
            animerPerso(&player1);
             afficher_perso(player1, screen);
                    afficher_newscore(player1.score, screen, player1.scoreimg,168);
            if(multiplayer==1){
            saut(&player2);
            MovePerso(&player2);
            animerPerso(&player2);
            afficher_perso(player2, screen);
            player2.scoreimg.posinscreen.x=710;
             afficher_newscore(player2.score, screen, player2.scoreimg,710+168);

            }
            t_prev1 = SDL_GetTicks();
  
        }
        
        if (SDL_GetTicks() - t_prev2 > 20)
        {
            if (player1.bonus == 1 && player1.score != player1.newscore)
            {
                player1.score++;
            }
            if (player1.malus == 1 && player1.score != player1.newscore)
            {
                player1.score--;
            }

            t_prev2 = SDL_GetTicks();
        }
        if(multiplayer){
        if (SDL_GetTicks() - t_prev3 > 20)
        {
            if (player2.bonus == 1 && player2.score != player2.newscore)
            {
                player2.score++;
            }
            if (player2.malus == 1 && player2.score != player2.newscore)
            {
                player2.score--;
            }

            t_prev3 = SDL_GetTicks();
        }


        }
        

        SDL_Flip(screen); 
    }
freeEnnemie(e);
Mix_FreeChunk(son);
SDL_Quit();
}


