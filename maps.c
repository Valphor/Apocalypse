#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "table1.h"
#include "menu_jeu.h"

int maps(SDL_Surface *ecran, int premiere_fois)
{

    SDL_Surface *tileset, *menu_jeu;
    SDL_Rect recup [NB_TILES_HAUTEUR] [NB_TILES_LARGEUR] = {0};
    SDL_Rect carte[NB_TILES_HAUTEUR][NB_TILES_LARGEUR] = {0};

    tileset = IMG_Load("wastelandtiles.png");
    menu_jeu = IMG_Load("menu_jeu.png");

    if (premiere_fois)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    }


    tableau(ecran, tileset);
    menuJeu(ecran, menu_jeu);
    SDL_Flip (ecran);


    SDL_FreeSurface(tileset);
    SDL_FreeSurface(menu_jeu);

    return 0;
}
