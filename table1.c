#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "efface_mouvement.h"

int tableau(SDL_Surface *ecran, SDL_Surface *tileset)
{
    SDL_Rect source; //choix du tile dans tileset
    SDL_Rect dest; //choix de la position du tile dans la map
    source.w = LARGEUR_TILE;
    source.h = HAUTEUR_TILE;

    int i,j;
    int b,c; //b est égal au numero du tile en x * taille du tile
    int d,e,f,g,h;
    int numero;
    int active = 0;
    int direction = 0;

    int table[][21] = {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

               SDL_Rect tiles[20][21] = {0}; //contien ,es positions des tiles dans tileset
        static SDL_Rect carte[NB_TILES_HAUTEUR][NB_TILES_LARGEUR] = {0}; //contien les positions des tiles dans la map
        int Scarte[NB_TILES_HAUTEUR][NB_TILES_LARGEUR] = {0}; //contien les numero des tiles
        int *pointer = &carte[0][0];

    FILE *fichier = fopen("niveau1.txt", "r");
    if (fichier)
    {
        int i = 0;
        int j = 0;

        for ( i = 0; i < NB_TILES_HAUTEUR; i++)
        {
            for (j = 0; j < NB_TILES_LARGEUR; j++)
                {
                    fscanf(fichier, "%d,", &Scarte[i][j]);
                }
        }
    }
    close (fichier);



        for (i = 0 ; i < 20 ; i++)
        {
            for (j = 0 ; j < 21 ; j++)
            {
                source.x = table[j][i] * LARGEUR_TILE + (i*ESPACE_TILE + 1); //fonction de repérage de tiles
                source.y = table[i][j] * HAUTEUR_TILE + (j*ESPACE_TILE + 1);

                tiles[i][j] = source; //plente si inversement

            }
        }



for (i = 0 ; i < NB_TILES_HAUTEUR ; i++) //fonction de repère de tile dans Scarte
    {
        for (j = 0 ; j < NB_TILES_LARGEUR ; j++)
        {


//algorithme pour trouver le bon nombre de ligne du tile en se référent au numéro renvoyer par la collission lors du choix du tile

                    b = 0; //conteneur de ligne
                    c = 0; //conteneur de collone

                    d = 19 + 1;
                    e = 19;
                    f = 0;
                    g = e * f;
                    h = d + g;

                    numero = Scarte[i][j];//recherche du numero de tile dans le tableau shéma carte


                    for (b = 0 ; b < numero -g ; f++)
                    {



                    d = 19 + 1;
                    e = 19;
                    g = e * f;
                    h = d + g;


                        if (numero < h) //si... alors il n'y a pas eu retour a la ligne
                        {
                            b = numero  -g;
                            c = f + 1;
                        }

                        else if (numero > 380)
                        {
                           // erreur(retour au début de la procédure)
                           // il n'y a que 380 tile disponible
                           break;
                        }

                        else
                        {

                        }


                    }


                        b--;
                        c--;
                        carte[i][j] = tiles[b][c]; //trensfert des tiles dans la carte pour info de blit

                        dest.x = j * LARGEUR_TILE;
                        dest.y = i * HAUTEUR_TILE;//si l'on inverse i j cela tourne la map


                        SDL_BlitSurface(tileset, &carte[i][j], ecran, &dest); //ici blitage du tile dans a la position dest



        }
    }


    //efface_mouvement (ecran, active, "t", tileset);
    efface_mouvement(ecran, direction, active, "c", pointer);
}
