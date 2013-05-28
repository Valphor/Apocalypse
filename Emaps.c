#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "table1.h"
#include "menu_edit.h"

/*
void Emaps(SDL_Surface *ecran)
{
    int continuer = 1;
    SDL_Event event;
    SDL_Surface *tileset = NULL, *menu_edit = NULL;

    tileset = IMG_Load("wastelandtiles.png");
    menu_edit = IMG_Load("menu_edit.png");

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    tableau(ecran, tileset);
    menuEdit(ecran, menu_edit);
    SDL_Flip (ecran);


        while(continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;

            }


        }
    SDL_FreeSurface(tileset);
    SDL_FreeSurface(menu_edit);
    exit(EXIT_SUCCESS);

}*/
