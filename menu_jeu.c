#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"

int menuJeu(SDL_Surface *ecran, SDL_Surface *menu_jeu)
{
    SDL_Rect dest;
    dest.x = 0;
    dest.w = 1024;
    dest.y = 576;
    dest.h = 192;

    SDL_BlitSurface(menu_jeu, NULL, ecran, &dest);

}
