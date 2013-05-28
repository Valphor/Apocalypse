#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "jeu.h"

void faction (SDL_Surface *ecran ,SDL_Rect curseur,int *continuer)
{
    SDL_Surface *blason_orc, *blason_humain, *fond;
    SDL_Rect p_blason_orc, p_blason_humain, p_fond;
    SDL_Event event;
    SDL_Thread *thread;

    int clan = 0;

    blason_orc = IMG_Load("blason_orc.jpg"); //chargement image
    blason_humain = IMG_Load("blason_humain.jpg");

    p_blason_orc.x = 850; //coordonnée
    p_blason_orc.w = 150;
    p_blason_orc.y = 300 ;
    p_blason_orc.h = 120;

    p_blason_humain.x = 250;
    p_blason_humain.w = 150;
    p_blason_humain.y = 300;
    p_blason_humain.h = 174;

    p_fond.x = 0;
    p_fond.y = 0;

    fond = IMG_Load("images.jpg");

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); //effacement blitage et actualisation ecran
    SDL_BlitSurface(fond, NULL, ecran, &p_fond);
    SDL_BlitSurface(blason_orc, NULL, ecran, &p_blason_orc);
    SDL_BlitSurface(blason_humain, NULL, ecran, &p_blason_humain);
    SDL_Flip(ecran);


    while (continuer) //boucle infinie sur bolléen
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                exit(EXIT_SUCCESS);
                break;

            case SDL_MOUSEBUTTONDOWN:
                curseur.x = event.button.x;
                curseur.y = event.button.y;

                if (curseur.x >= p_blason_humain.x //collision curseur sur blason humain
                    && curseur.x <= p_blason_humain.x + p_blason_humain.w
                    && curseur.y >= p_blason_humain.y
                    && curseur.y <= p_blason_humain.y + p_blason_humain.h)
                    {
                        clan = 0;
        /*thread ici*/  jeu(ecran, clan);
        /*thread ici*/ //jeu_ordi();
                    }

                else if (curseur.x >= p_blason_orc.x //collision sur blason orc
                    && curseur.x <= p_blason_orc.x + p_blason_orc.w
                    && curseur.y >= p_blason_orc.y
                    && curseur.y <= p_blason_orc.y + p_blason_orc.h)
                    {
                        clan = 1;
        /*thread ici*/  jeu(ecran, clan);
        /*thread ici*/ //jeu_ordi();
                    }
                break;
        }
    }
SDL_FreeSurface(blason_orc);
SDL_FreeSurface(blason_humain);
SDL_FreeSurface(fond);

exit(EXIT_SUCCESS);
}
