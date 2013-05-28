#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "maps.h"
#include "efface_mouvement.h"

int mouvement(int continuer, int ok, SDL_Surface *ecran, SDL_Surface *grunt, SDL_Rect *dest)
{
    SDL_Rect curseur, encien_p;
    SDL_Event event;
    int active = 1;
    int direction = 0;


    ok = 1;
    while (ok)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                ok = 0;
                continuer = 0;
                exit(EXIT_SUCCESS);
                break;

            case SDL_MOUSEBUTTONDOWN:
                curseur.x = event.button.x - 16;
                curseur.y = event.button.y - 16;

                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    ok = 0;
                }

                else if(event.button.button == SDL_BUTTON_RIGHT)
                    {
                        ok = 1;
                        while(ok)
                        {
                            encien_p = *dest;

                            if (dest->x > curseur.x
                                && dest->y > curseur.y)
                            {
                                dest->x--;
                                dest->y--;
                                direction = 1;
                            }

                            else if (dest->x < curseur.x
                                && dest->y > curseur.y)
                            {
                                dest->x++;
                                dest->y--;
                                direction = 1;
                            }

                            else if (dest->x > curseur.x
                                && dest->y < curseur.y)
                            {
                                dest->x--;
                                dest->y++;
                                direction = 1;
                            }

                            else if (dest->x < curseur.x
                                    && dest->y < curseur.y)
                            {
                                dest->x++;
                                dest->y++;
                                direction = 1;
                            }

                            else if (dest->x > curseur.x)
                            {
                                dest->x--;
                                direction = 6;
                            }

                            else if (dest->x < curseur.x)
                            {
                                dest->x++;
                                direction = 5;
                            }

                            else if (dest->y > curseur.y)
                            {
                                dest->y--;
                                direction = 8;
                            }

                            else if (dest->y < curseur.y)
                            {
                                dest->y++;
                                direction = 7;
                            }

                            else if (dest->x == curseur.x
                                    &&dest->y == curseur.y)
                            {
                                ok = 0;
                            }

        /*thread ici*/  efface_mouvement(ecran, direction, active, "d", dest);
                        SDL_BlitSurface(grunt, NULL, ecran, dest);
                        SDL_Flip(ecran);

                        }
                    }
                break;
            }
    }
    return continuer;
}
