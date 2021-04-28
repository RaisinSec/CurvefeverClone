#ifndef SDLJEU_H
#define SDLJEU_H
#include "Jeu.h"
#include "fenetreJeu.h"
#include <iostream>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#elif __linux__
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:
    Image () ;
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};

class sdlJeu
{
public:
    sdlJeu(unsigned int tailleX, unsigned int tailleY);
    ~sdlJeu();
    void sdlAff(); //private ?
    void sdlBoucle();    
    bool gameRunning; //private ?

private:
    fenetreJeu fenetreJeu;
    Jeu jeu;
    SDL_Window * window;
    SDL_Renderer * renderer;
    void surfaceToTexture();
    void sdlActionsAutomatiques();
};


#endif