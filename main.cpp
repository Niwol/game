/*
main.c
------

par Xkira07

role: fonction principale du programme
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "jeu.c"


int main(int argc, char *argv[])
{
    //déclaration des variables
    SDL_Surface *ecran = NULL, *imageDeFont = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1;

    //initialisation
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("game", NULL);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);

    imageDeFont = IMG_Load("ecran_de_titre.png");
    position.x = 0;
    position.y = 0;

    //boucle principale
    while(continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_SPACE:
                if(jouer(ecran))
                    continuer = 0;
                break;
            }
        }

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(imageDeFont, NULL, ecran, &position);

    SDL_Flip(ecran);
    }

    //libération et quiter
    SDL_FreeSurface(imageDeFont);
    SDL_Quit();

    return EXIT_SUCCESS;
}


