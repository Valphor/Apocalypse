#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "Emaps.h"

int edit(SDL_Surface *ecran, SDL_Rect curseur, int *continuer)
{
        SDL_Surface *tileset = NULL;
        SDL_Event event;
        SDL_Rect AABB_ecran, AABB_menu, dest;
       // Emaps(ecran);

        AABB_ecran.x = 0;
        AABB_ecran.w = 1280;
        AABB_ecran.y = 0;
        AABB_ecran.h = 576;

        AABB_menu.x = 0;
        AABB_menu.w = 1280;
        AABB_menu.y = 577;
        AABB_menu.h = 192;

        tileset = IMG_Load("wastelandtiles");


    while(continuer)
    {

        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                *continuer = 0;
                break;

            case SDL_MOUSEBUTTONDOWN:
                curseur.x = event.button.x;
                curseur.y = event.button.y;

                if (event.button.button == SDL_BUTTON_LEFT
                    && curseur.y <= AABB_ecran.y)
                {
                    //blitage de tile sélectionner sur ecran



                }

                if (event.button.button == SDL_BUTTON_LEFT
                    && curseur.y > AABB_ecran.y)
                {
                    //enregistrement du tile sélectionner si collision avec un tile
                }


                break;
        }
    }

}

