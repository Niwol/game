/*
jeu.c
-----

par Xkira07

role: contient les fonctions servant à jouer
*/

#include "constantes.h"
#include "jeu.h"

int jouer(SDL_Surface *ecran)
{
    //déclaration des variables
    SDL_Surface *sol = NULL, *canon[2] = {NULL}, *tir[100] = {NULL}, *blockRouge[100] = {NULL};
    SDL_Rect positionSol, positionCanon[2], positionTir[100], positionBlockRouge[100];
    SDL_Event event;

    int i = 0, j = 0, k = 0, l = 0;
    int quit = 0, continuer = 1, blockRougeEnJeu[100] = {0}, tirEnJeu[100] = {0};
    int apuiEspace = 0, apuiGauche = 0, apuiDroite = 0;
    int tempsActulAparition = 0, tempsPrecedentAparition = 0, tempsActulTir[2] = {0}, tempsPrecedentTir[2] = {0}, tempsDecenteActuel = 0, tempsDecentePrecedent = 0;

    srand(time(NULL));

    //initialisation des surfaces
    sol = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_SOL_L, TAILLE_SOL_H, 32, 0, 0, 0, 0);
    SDL_FillRect(sol, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
    positionSol.x = 0;
    positionSol.y = TAILLE_FENETRE_H - sol->h;

    canon[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CANON1_L, TAILLE_CANON1_H, 32, 0, 0, 0, 0);
    SDL_FillRect(canon[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
    positionCanon[0].x = TAILLE_FENETRE_L / 2 - canon[0]->w / 2;
    positionCanon[0].y = TAILLE_FENETRE_H - TAILLE_SOL_H - TAILLE_CANON1_H;

    canon[1] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CANON2_L, TAILLE_CANON2_H, 32, 0, 0, 0, 0);
    SDL_FillRect(canon[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
    positionCanon[1].x = TAILLE_FENETRE_L / 2 - canon[1]->w / 2;
    positionCanon[1].y = TAILLE_FENETRE_H - TAILLE_SOL_H - TAILLE_CANON1_H - TAILLE_CANON2_H;

    for(j = 0; j < 100; j++)
    {
        tir[j] = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 4, 32, 0, 0, 0, 0);
        SDL_FillRect(tir[j], NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
        positionTir[j].x = 1000;
        positionTir[j].y = 0;

        blockRouge[j] = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                             rand() % (TAILLE_BLOCK_MAX - TAILLE_BLOCK_MIN) + TAILLE_BLOCK_MIN,
                                             rand() % (TAILLE_BLOCK_MAX - TAILLE_BLOCK_MIN) + TAILLE_BLOCK_MIN,
                                             32, 0, 0, 0, 0);
        SDL_FillRect(blockRouge[i], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));

        positionBlockRouge[j].x = 2000;

    }

    //boucle principale du jeu
    while(continuer)
    {
        SDL_PollEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            quit = 1;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_LEFT:
                apuiGauche = 1;
                break;
            case SDLK_RIGHT:
                apuiDroite = 1;
                break;

            case SDLK_SPACE:
                apuiEspace = 1;
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT:
                apuiGauche = 0;
                break;
            case SDLK_RIGHT:
                apuiDroite = 0;
                break;
            case SDLK_SPACE:
                apuiEspace = 0;
                break;
            }
            break;
        }

        //apui touche
        if(apuiDroite)
        {
            if(positionCanon[0].x < ecran->w - canon[0]->w)
            {
                positionCanon[0].x++;
                positionCanon[1].x++;
            }
        }
        else if(apuiGauche)
        {

            if(positionCanon[1].x > TAILLE_CANON1_L / 2 - TAILLE_CANON2_L / 2)
            {
                positionCanon[1].x--;
                positionCanon[0].x--;
            }
        }

        //tir
        tempsActulTir[0] = SDL_GetTicks();
        if(tempsActulTir[0] - tempsPrecedentTir[0] > 100)
        {
            if(apuiEspace)
            {
                positionTir[k].x = positionCanon[1].x;
                positionTir[k].y = positionCanon[1].y - tir[k]->h;
                tirEnJeu[k] = 1;
                k++;
            }
            tempsPrecedentTir[0] = tempsActulTir[0];
        }

        tempsActulTir[1] = SDL_GetTicks();
        if(tempsActulTir[1] - tempsPrecedentTir[1] > 5)
        {
            for(j = 0; j < 100; j++)
            {
                positionTir[j].y -= 3;

            if(positionTir[j].y <= 0)
                positionTir[j].x = 1000;
            }
            tempsPrecedentTir[1] = tempsActulTir[1];
        }

        //creation d'un block rouge
        tempsActulAparition = SDL_GetTicks();
        if(tempsActulAparition - tempsPrecedentAparition > 3000)
        {
            blockRouge[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                                 rand() % (TAILLE_BLOCK_MAX - TAILLE_BLOCK_MIN) + TAILLE_BLOCK_MIN,
                                                 rand() % (TAILLE_BLOCK_MAX - TAILLE_BLOCK_MIN) + TAILLE_BLOCK_MIN,
                                                 32, 0, 0, 0, 0);

            SDL_FillRect(blockRouge[i], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
            positionBlockRouge[i].x = rand() % ecran->w - blockRouge[i]->w;
            positionBlockRouge[i].y = 0;
            blockRougeEnJeu[i] = 1;
            i++;
            tempsPrecedentAparition = tempsActulAparition;
        }

        //décente des blocks
        tempsDecenteActuel = SDL_GetTicks();
        if(tempsDecenteActuel - tempsDecentePrecedent > 100)
        {
            for(j = 0; j < 100; j++)
            {
                positionBlockRouge[j].y += 6;
            }
            tempsDecentePrecedent = tempsDecenteActuel;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        SDL_BlitSurface(sol, NULL, ecran, &positionSol);
        SDL_BlitSurface(canon[0], NULL, ecran, &positionCanon[0]);
        SDL_BlitSurface(canon[1], NULL, ecran, &positionCanon[1]);
        for(j = 0; j < 100; j++)
        {
            SDL_BlitSurface(blockRouge[j], NULL, ecran, &positionBlockRouge[j]);
        }
        for(j = 0; j < 100; j++)
        {
            SDL_BlitSurface(tir[j], NULL, ecran, &positionTir[j]);
        }

        SDL_Flip(ecran);

        for(j = 0; j < 100; j++)
        {
            if(blockRougeEnJeu[j])
            {
                for(l = 0; l < 100; l++)
                {
                    if(tirEnJeu[l])
                    {
                        if(gestionDesColisions(blockRouge[j], &positionBlockRouge[j], tir[l], &positionTir[l], sol, positionSol, &blockRougeEnJeu[j], &tirEnJeu[l]))
                            continuer = 0;
                    }
                }
            }
        }

        if(i > 99)
            i = 0;
        if(k > 99)
            k = 0;
    }

    SDL_FreeSurface(sol);
    SDL_FreeSurface(canon[0]);
    SDL_FreeSurface(canon[1]);
    for(j = 0; j < 100; j++)
    {
        SDL_FreeSurface(tir[j]);
        SDL_FreeSurface(blockRouge[j]);
    }

    return quit;
}


int gestionDesColisions(SDL_Surface *blockRouge, SDL_Rect *positionBlockRouge, SDL_Surface *tir, SDL_Rect *positionTir, SDL_Surface *sol, SDL_Rect positionSol, int *blockRougeEnJeu, int *tirEnJeu)
{
    SDL_Rect positionBlockRouge1;
    positionBlockRouge1.x = positionBlockRouge->x;
    positionBlockRouge1.y = positionBlockRouge->y;

    SDL_Rect positionTir1;
    positionTir1.x = positionTir->x;
    positionTir1.y = positionTir->y;

    int gameOver = 0;

    if(colision(blockRouge, positionBlockRouge1, tir, positionTir1))
    {
        positionBlockRouge->x = 2000;
        positionBlockRouge->y = 0;
        positionTir->x = 1000;
        *blockRougeEnJeu = 0;
        *tirEnJeu = 0;
    }

    if(colision(blockRouge, positionBlockRouge1, sol, positionSol))
        gameOver = 1;

    return gameOver;
}


int colision(SDL_Surface *objet1, SDL_Rect position1, SDL_Surface *objet2, SDL_Rect position2)
{
    int colisionTest = 0;

    if((((position1.x + objet1->w) >= (position2.x + 1) && (position1.x + objet1->w) <= (position2.x + objet2->w - 1)) ||
        ((position1.x) >= (position2.x) && (position1.x) <= (position2.x + objet2->w - 1))) &&
        (((position1.y + objet1->h) >= (position2.y + 1) && (position1.y + objet1->h) <= (position2.y + objet2->h - 1)) ||
        ((position1.y) >= (position2.y) && (position1.y) <= (position2.y + objet2->h - 1)))
       ||
       (((position2.x + objet2->w) >= (position1.x + 1) && (position2.x + objet2->w) <= (position1.x + objet1->w - 1)) ||
        ((position2.x) >= (position1.x) && (position2.x) <= (position1.x + objet1->w - 1))) &&
        (((position2.y + objet2->h) >= (position1.y + 1) && (position2.y + objet2->h) <= (position1.y + objet1->h - 1)) ||
        ((position2.y) >= (position1.y) && (position2.y) <= (position1.y + objet1->h - 1))))
            colisionTest = 1;

    return colisionTest;
}



