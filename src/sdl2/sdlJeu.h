/**
@brief Module gérant la partie SDL

Coeur de la version graphique du jeu, ce module contient les images utilisées, les couleurs, les polices d'écriture ou encore la fenêtre du jeu.
sdlJeu appelle tpit

@file : sdlJeu.h
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/

#ifndef SDLJEU_H
#define SDLJEU_H
#include "Jeu.h"
#include "Image.h"
#include "fenetreJeu.h"
#include <iostream>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#elif __linux__
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif


class sdlJeu
{
public:
    sdlJeu(unsigned int tailleX, unsigned int tailleY, Couleur couleur1, Couleur couleur2);
    ~sdlJeu();
    void sdlBoucle();    

private:
    bool gameRunning;
    Jeu jeu;
    FenetreJeu fenetreJeu;
    Image imageTitreJeu;
    Image imageDroiteJeu;
    Image imQuitterPresse;
    Image imQuitter;
    Image imRecommencerPresse;
    Image imRecommencer;
    Image imTeteSerpent[6];
    TTF_Font * font24;
    TTF_Font * font32;
    TTF_Font * font48;
    TTF_Font * font64;
    SDL_Color blanc;
    SDL_Color grisEcriture;
    SDL_Window * window;
    SDL_Renderer * renderer;
    void sdlAff(bool boutonRecommencer, bool boutonQuitter);
    bool isIn(int x, int y, int w, int h, int souris_x, int souris_y);
    void afficherTeteSerpent(SDL_Renderer* renderer, Serpent S);
    void renderCenterText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void surfaceToTexture();
    void sdlActionsAutomatiques();
    void recommencerPartie();
};


#endif