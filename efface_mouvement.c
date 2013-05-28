#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdarg.h>
#include <SDL/SDL_image.h>


#include "constantes.h"
#include "efface_mouvement.h"

int efface_mouvement (SDL_Surface *ecran, int direction, int active, char *fmt, ...)
{
    SDL_Surface *noir = IMG_Load("noir.png");



    va_list ap;
    static SDL_Rect *p_carte, *dest, position;
    static SDL_Rect carte[NB_TILES_HAUTEUR][NB_TILES_LARGEUR] = {0};
    SDL_Rect blit[10] = {0,0,0,0,0,0};
    char compteur = 0;
    static SDL_Surface *tileset;
    char i = 0, j = 0, ok = 0, v = 0, w = 0, boucle = 0;

    tileset = IMG_Load("wastelandtiles.png");


//partie de récupération des paramètres optionnel
    va_start(ap, fmt);


    while (*fmt)
    {
        switch (*fmt ++ )
        {
        case 'c':  //chaîne
            p_carte = va_arg (ap, SDL_Rect *);
            break;
        case 'd':  /* entier */
            dest = va_arg (ap, SDL_Rect *);
            break;
       // case 't':   /* caractère */
       //   tileset = va_arg (ap, SDL_Surface *);
          //break;
        }
    }
    va_end(ap);
    //------------------------------------------

    if(active)
    {
    //réorganisation de carte
    for(i = 0 ; i < NB_TILES_HAUTEUR ; i ++)
    {
        for(j = 0 ; j < NB_TILES_LARGEUR ; j++)
        {
            carte[i][j] = *p_carte; //(p_carte + i) * (p_carte + j);
            //p_carte++;
        }
    }


    //------------------------------------------
    //efface_mouvement

    j = dest->x / LARGEUR_TILE;
    i = dest->y / HAUTEUR_TILE;

    position.x = dest->x;
    position.y = dest->y;


    while(!ok)
    {
        if(position.x >= 32)
        {
            position.x -= 32;
            v++;
        }
        else if (position.x <= 9 && position.x != 0)
        {
            position.x = 0;
        }
        else
            ok = 1;

    }
    ok = 0;



    while(!ok)
    {
        if(position.y >= 32)
        {
            position.y -= 32;
            w++;
        }

        else if (position.y <= 9 && position.y != 0)
        {
            position.y = 0;
        }

        else
            ok = 1;

    }

//ici position est un neud de scène
position.x = (v * LARGEUR_TILE);
position.y = (w * HAUTEUR_TILE);

for(boucle = 0 ; boucle <= 9 ; boucle++)
    blit[boucle] = position;

switch(direction)
{
    case 1:


        blit[0].x += 32;
        blit[1].x += 64;
        blit[2].x += 32;
        blit[2].y += 32;
        blit[3].x += 64;
        blit[3].y += 32;
        blit[4].y += 32;
        blit[5].y += 64;
        blit[6].x += 32;
        blit[6].y += 64;
        blit[7];
        blit[8].x += 64;
        blit[8].y += 64;

        compteur = 8;

        break;

    case 5:

        blit[1].x += 32;
        blit[2].y += 32;
        blit[3].y += 32;
        blit[3].x += 32;
        blit[4].y += 64;
        blit[5].y += 64;
        blit[5].x += 32;

        compteur = 5;

        break;

    case 6:

        blit[0].x += 32;
        blit[1].y += 32;
        blit[1].x += 32;
        blit[2].y += 64;
        blit[2].x += 32;
        blit[3].x += 64;
        blit[4].x += 64;
        blit[4].y += 32;
        blit[5].x += 64;
        blit[5].y += 64;

        compteur = 5;

        break;

    case 7:

        blit[1].x += 32;
        blit[2].x += 64;
        blit[3].y += 32;
        blit[4].y += 32;
        blit[4].x += 32;
        blit[5].y += 32;
        blit[5].x += 64;

        compteur = 5;

        break;

    case 8:

        blit[0].y += 32;
        blit[1].y += 32;
        blit[1].x += 32;
        blit[2].y += 32;
        blit[2].x += 64;
        blit[3].y += 64;
        blit[4].y += 64;
        blit[4].x += 32;
        blit[5].y += 64;
        blit[5].x += 64;
        blit[6].x += 32;
        blit[7].x += 64;
        blit[8]; //reste a position

        compteur = 8;

        break;

}

for(boucle = 0 ; boucle <= compteur ; boucle++)
{
    SDL_BlitSurface(tileset, &carte[i][j], ecran, &blit[boucle]);
}

    }
}
