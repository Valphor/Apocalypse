#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "faction.h"
#include "jeu.h"
#include "editeur.h"

const SDL_Surface *ecran;

int main (int argc, char *argv[])
{
    SDL_Surface *fond, *button1, *button_e;
    SDL_Rect positionMenu, positionButton, positionButton_e, curseur;
    SDL_Event event;
    int continuer = 1;

    SDL_Init (SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("icone.jpg"),  NULL);

    ecran = SDL_SetVideoMode(1280, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //a configurer pour le plein écran et les timers
    SDL_WM_SetCaption("A-P-O-C-A-L-Y-P-S-E", NULL);

    button1 = IMG_Load("button.png");
    button_e = IMG_Load("button_e.png");

    fond = IMG_Load("fond.jpg");
    positionMenu.x = 0;
    positionMenu.y = 0;

    curseur.x = 0;
    curseur.y = 0;

    positionButton.x = 1024;
    positionButton.y = 40;
    positionButton.w = 233;
    positionButton.h = 40;

    positionButton_e.x = 23;
    positionButton_e.y = 40;
    positionButton_e.w = 233;
    positionButton_e.h = 40;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(fond, NULL, ecran, &positionMenu);
    SDL_BlitSurface(button1, NULL, ecran, &positionButton);//appel fonction affiche_button
    SDL_BlitSurface(button_e, NULL, ecran, &positionButton_e);
    SDL_Flip(ecran);


    while (continuer)
    {
        SDL_WaitEvent (&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            exit(EXIT_SUCCESS);
            break;

        case SDL_MOUSEBUTTONDOWN:
            curseur.x = event.button.x;
            curseur.y = event.button.y;


    if (curseur.x >= positionButton.x
        && curseur.x <= positionButton.x + positionButton.w
        && curseur.y >= positionButton.y
        && curseur.y <= positionButton.y + positionButton.h)
            {
                faction(ecran, curseur, &continuer);
            }


        if (curseur.x >= positionButton_e.x
        && curseur.x <= positionButton_e.x + positionButton_e.w
        && curseur.y >= positionButton_e.y
        && curseur.y <= positionButton_e.y + positionButton_e.h)
            {
                edit(ecran, curseur, &continuer);
            }
        }
    }

SDL_FreeSurface(fond);
SDL_FreeSurface(button1);
SDL_FreeSurface(button_e);
SDL_Quit();

return 0;
}
