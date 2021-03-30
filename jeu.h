/*
jeu.h
-----

par Xkira07

role: contient les prototypes de jeu.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>

int jouer(SDL_Surface *ecran);

int gestionDesColisions(SDL_Surface *blockRouge, SDL_Rect *positionBlockRouge, SDL_Surface *tir, SDL_Rect *positionTir, SDL_Surface *sol, SDL_Rect positionSol, int *blockRougeEnJeu, int *tirEnJeu);

int colision(SDL_Surface *objet1, SDL_Rect position1, SDL_Surface *objet2, SDL_Rect position2);
