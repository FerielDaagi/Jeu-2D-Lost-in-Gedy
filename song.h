#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
void PlayMusic(Mix_Music *musique);
Mix_Music * initMusic();
Mix_Chunk *  initSon();
void PlaySon(Mix_Chunk *son);
