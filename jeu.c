#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "maps.h"
#include "mouvement.h"
#include "batiment.h"
#include "structure.h"

//BIG BUG apres un certain nombre de deplacement le programme saute et les traine ne s'effacent plus
//DESCRIPTION chaque appel a mouvement (puis a efface_mouvement) utilise plus de processeur mais ne libere pas cette espace (visible dans le gestionnaire des taches windows)
//SOLUTION la fonction efface_mouvement sera remplacer par affiche_global, on vera si le problème se résoud a ce moment la
//le problème est bien efface_mouvement puisque c'est vraiment cette fonction qui saute et non mouvement

//BUG REPERER LIGNE 206 SUSPECTE
//DESCRIPTION DU BUG quand on crée plusieurs grunt puis que l'on fais déplacer le premier tout les clics droit qui suivent font bouger les grunts suiivants (sans les avoirs selectionner)

//bug il faut 2 clic pour que button_grunt s'efface, lié a l'organisation des collision = 0; (une correction de bug en ammene un autre -.^)

void jeu(SDL_Surface *ecran, int clan)
{

    char continuer = 1;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    maps(ecran); //calcule enregistre et affiche map

    SDL_Surface *base, *button_base, *button_grunt, *grunt; //les images du jeux (seront déclarer et affecter dans une fonction indépendente qui communiquera les données /!\ on sépare batiments boutton et uunité)
    SDL_Rect dest, p_base, p_button_base, p_button_grunt; //les positions des images (pareil que en haut)
    SDL_Event event;
    int ok = 1, collision = 0; //ok = bolléen de boucle et collision test si il y a eu une collision

    Unite unite[100] = {0};//bloc unite sera envoyer a la structure global
    int c_unite = 0; //des compteur
    int nb_unite = 0;

    Building building[100] = {0};//bloc batiment sera envoyer a la structure global
    int c_building = 0;
    int nb_building = 0;



    if (!clan) //si ally charger pour (a regrouper dans une fonction)
    {
    base = IMG_Load("base.png");
    button_base = IMG_Load("button_base.png");
    button_grunt = IMG_Load("button_grunt.png");
    grunt = IMG_Load("grunt.png");
    SDL_SetColorKey(grunt, SDL_SRCCOLORKEY, SDL_MapRGB(grunt->format, 255, 255, 255));
    }

    else if (clan) //si orc charger pour (a regrouper dans une fonction)
    {
    base = IMG_Load("base.png");
    button_base = IMG_Load("button_base.png");
    button_grunt = IMG_Load("button_grunt.png");
    grunt = IMG_Load("grunt.png");
    SDL_SetColorKey(grunt, SDL_SRCCOLORKEY, SDL_MapRGB(grunt->format, 255, 255, 255));
    }

    SDL_SetColorKey(base, SDL_SRCCOLORKEY, SDL_MapRGB(base->format, 255, 255, 255));//pour supprimer le blanc derriere l'image (a mettre dans la fonction, voir plus haut)

    p_button_base.x = 617; //a mettre dans une fonction (une pour chaque type)qui fera les initialisation puis qui les placeras dans une structure (a construire)
    p_button_base.w = 46;
    p_button_base.y = 668;
    p_button_base.h = 38;

    p_base.w = 129;
    p_base.h = 141;
    p_base.x = 0;
    p_base.y = 0;


    p_button_grunt.x = 550;
    p_button_grunt.w = 46;
    p_button_grunt.y = 668;
    p_button_grunt.h = 38;



    while(continuer)
    {
        SDL_BlitSurface(button_base, NULL, ecran, &p_button_base); //pour le moment le bouton base est toujours afficher (pour le futur seul un clic sur un poéon et sur le bouton construction batiment l'affichera)
        SDL_Flip(ecran); //il y a beaucoup trop de flip dans le code voire a les réduire (ca prend bc trop de temps d'exécution)

/*thread ici*/SDL_WaitEvent(&event); //futur fonction threader
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0; //on vas retirer tout les bolléen continuer pas pratique pour de gros projet
                    exit(EXIT_SUCCESS); //on vas les remplacer par ca (je dois encore me documenter sur le fonctionnement interne de cette fonction)
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (!collision) //si auparavent l'on a pas cliquer sur un batiment ou sur le bouton_grunt l'effacer (EX: si clic sur la map) /!\ cette fonction est beaucoup trop présente mais c'est la seul solutions que j'ai trouver (rapide) pour remplir toute les conditions
                        {
                            SDL_FillRect(ecran, &p_button_grunt, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_Flip(ecran);
                            ok = 0; // on n'entre pas non plus dans la boucle de création d'unité
                        }





                        if(event.button.x >= p_button_base.x //si clic sur button_base et qu'il n'y a pas plus de 100 batiment sur la map
                               &&event.button.x <= p_button_base.x + p_button_base.w
                               &&event.button.y >= p_button_base.y
                               &&event.button.y <= p_button_base.y + p_button_base.h
                               &&c_building <= 100)
                               {
                                    batiment(ok, event, continuer, &p_base, base, ecran); //appeler la fonction batiment (un clic droit ou sur le menu de jeu brun nous en fait sortir)
                                    building[c_building].position = p_base; //enregistrer les coordonnées dans un tableau de structure
                                    c_building++; //préparer la prochaine case
                               }

                            for (nb_building = 0; nb_building < 100; nb_building++) //ya t'il eu un clic sur un batiments?
                        {
                                    building[nb_building].position.w = 129 ; //j'en profite pour définir h et w (je suis un flemard^^)
                                    building[nb_building].position.h = 141 ;

                            if(event.button.x >= building[nb_building].position.x
                               &&event.button.x <= building[nb_building].position.x + building[nb_building].position.w
                               &&event.button.y >= building[nb_building].position.y
                               &&event.button.y <= building[nb_building].position.y + building[nb_building].position.h)
                               {
                                    dest.x = building[nb_building].position.x + 64 ; //position du futur grunt a sa création
                                    dest.y = building[nb_building].position.y + 140 ;

                                    SDL_BlitSurface(button_grunt, NULL, ecran, &p_button_grunt); //si oui afficher button_grunt
                                    SDL_Flip(ecran);

                                   ok = 1;
                                    while (ok) //ici on boucle pour etre bien sur de tester un evenement clic (sinon quand on relache le clic button_grunt s'efface, car il n'y a pas eu collision)
                                    {
                    /*thread ici*/      SDL_WaitEvent(&event);
                                        switch(event.type)
                                        {

                                            case SDL_QUIT:
                                                ok = 0;
                                                continuer = 0;
                                                exit(EXIT_SUCCESS);
                                                break;

                                            case SDL_MOUSEBUTTONDOWN:

                                                    if(event.button.x >= p_button_grunt.x //si collision avec button_grunt
                                                        &&event.button.x <= p_button_grunt.x + p_button_grunt.w
                                                        &&event.button.y >= p_button_grunt.y
                                                        &&event.button.y <= p_button_grunt.y + p_button_grunt.h)
                                                        {
                                                            //créer un grunt
                                                                ok = 0;
                                                                unite[c_unite].position = dest;
                                                                unite[c_unite].position.h = 42;
                                                                unite[c_unite].position.w = 45;
                                                                SDL_BlitSurface(grunt, NULL, ecran, &unite[c_unite].position);//le 1 er et le 2 ème argument sera a changer par la suite (on pompera directement dans le tileset)
                                                                SDL_Flip(ecran);
                                                                c_unite++;

                                                                unite[c_unite].carac.vie = 800;
                                                                unite[c_unite].carac.armure = 100;
                                                                unite[c_unite].carac.puissance = 150;
                                                                unite[c_unite].type = 1;

                                                                collision = 1;
                                                        }

                                                    //effacer button grunt si pas de collision
                                                   if (!collision)
                                                        {
                                                            SDL_FillRect(ecran, &p_button_grunt, SDL_MapRGB(ecran->format, 0, 0, 0));
                                                            SDL_Flip(ecran);
                                                            ok = 0;
                                                        }





                                                        break;
                                        }
                                    }
                               }
                        }



                                    if(event.button.x >= p_button_grunt.x //si collision avec bouton grunt
                                        &&event.button.x <= p_button_grunt.x + p_button_grunt.w
                                        &&event.button.y >= p_button_grunt.y
                                        &&event.button.y <= p_button_grunt.y + p_button_grunt.h
                                        &&collision == 1)
                                        {
                                            //afficher grunt
                                                ok = 0;
                                                unite[c_unite].position = dest;
                                                SDL_BlitSurface(grunt, NULL, ecran, &dest);
                                                SDL_Flip(ecran);
                                                c_unite++;

                                                unite[c_unite].carac.vie = 800;
                                                unite[c_unite].carac.armure = 100;
                                                unite[c_unite].carac.puissance = 150;
                                                unite[c_unite].type = 1;

                                                collision = 1;
                                        }

                                       else //sinon l'effacer
                                        collision = 0;



                                    for (nb_unite = 0; nb_unite <= 100; nb_unite++) //a on cliquer sur un grunt?
                                    {
                                        if (event.button.x >= unite[nb_unite].position.x //si c'est celui la
                                            && event.button.x <= unite[nb_unite].position.x + unite[nb_unite].position.w
                                            && event.button.y >= unite[nb_unite].position.y
                                            && event.button.y <= unite[nb_unite].position.y + unite[nb_unite].position.h)
                                        {
                                            dest = unite[nb_unite].position; //on donne sa position a dest
                            /*thread ici*/  mouvement(continuer, ok, ecran, grunt, &dest); //appeler la fonction mouvement (clic gauche nous en fait sortir et droit déplace le grunt)
                                            unite[nb_unite].position = dest; //on recupere sa position qui a changer (defaut on doit cliquer la ou grunt finirais sa course pour lui redire de se deplacer, et il finira dabord sa course (pas lui faire chier!!! lol) solution envoyen directement unite comme POINTEUR (donc envoyer son adresse))
                                        }
                                  }
                    }
                    break;
            }
    }

    return continuer;
    exit(EXIT_SUCCESS);
}
