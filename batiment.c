#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int batiment(int ok, SDL_Event event, int continuer, SDL_Rect *p_base, SDL_Surface *base, SDL_Surface *ecran)
{
    ok = 1;
    while(ok)
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
                if(event.button.button == SDL_BUTTON_LEFT
                   &&event.button.y <= 575)
                {
                    p_base->x = event.button.x - 64;
                    p_base->y = event.button.y - 70;

                    SDL_BlitSurface(base, NULL, ecran, p_base);
                    SDL_Flip(ecran);
                    ok = 0;
                }

                else
                {
                    ok = 0;
                }
                break;
        }
    }
    return continuer;
}
