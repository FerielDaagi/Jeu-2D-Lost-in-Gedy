#include <SDL/SDL_mixer.h>
#include "song.h"
Mix_Chunk *  initSon()
{
	return Mix_LoadWAV("sonbref.wav");
}
void PlaySon(Mix_Chunk *son)
{
	Mix_PlayChannel(-1,son,0);
}
