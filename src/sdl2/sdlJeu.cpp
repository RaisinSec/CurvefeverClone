#include "sdlJeu.h"
#include <cassert>

#define fps 60
const int TAILLE_SPRITE = 10;

//commencer avec une fenetre avec terrain vide et mettre des points à la main dans le main.

// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}

// ============= CLASS SDLJEU =============== //

sdlJeu::sdlJeu(unsigned int tailleX, unsigned int tailleY):jeu(tailleX, tailleY)
{
    //Initialisation de la sdl : 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG)) || (!(IMG_Init(IMG_INIT_JPG)))) {
        cout << "SDL_image could not initialize! SDL_image Error: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //creation de la fenetre : 
    window = SDL_CreateWindow("Curvefever !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 720, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //creation du rendu : 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //chargement de l'image du jeu
    surfaceJeu = SDL_GetWindowSurface(window);
    textureJeu = NULL;
    gameRunning = true;
}

sdlJeu::~sdlJeu()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surfaceJeu);
    surfaceJeu = NULL;
    textureJeu = NULL;
    SDL_Quit();
}

void sdlJeu::setPixel(SDL_Surface *screen, int x, int y, Couleur color)
{
    Uint32 couleur = SDL_MapRGB(screen->format, color.getRouge(), color.getBleu(), color.getVert());
    
    SDL_Rect pixel;
    pixel.w = TAILLE_SPRITE, pixel.h = TAILLE_SPRITE;
    pixel.x = x * TAILLE_SPRITE, pixel.y = y* TAILLE_SPRITE; 
    SDL_FillRect(screen, &pixel, couleur);
}

void sdlJeu::sdlActionsAutomatiques()
{
    jeu.actionsAutomatiquesSDL();
    setPixel(surfaceJeu, jeu.getConstS1().getTeteX(), jeu.getConstS1().getTeteY(), jeu.getConstS1().getCouleur());
    setPixel(surfaceJeu, jeu.getConstS2().getTeteX(), jeu.getConstS2().getTeteY(), jeu.getConstS2().getCouleur());
    SDL_UpdateWindowSurface(window);


}

void sdlJeu::sdlAff()
{
    //Remplir l'écran de noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    //convertir notre surface représentant notre jeu en texture affichable et l'afficher
    int ok;
    surfaceJeu = SDL_ConvertSurfaceFormat(surfaceJeu, SDL_PIXELFORMAT_ARGB8888, 0);
    ok = SDL_UpdateTexture(textureJeu,NULL,surfaceJeu->pixels,surfaceJeu->pitch);
    assert(ok == 0);
    ok = SDL_RenderCopy(renderer,textureJeu,NULL,NULL);
    assert(ok == 0);
}

void sdlJeu::sdlBoucle()
{
    Uint32 starting_ticks = SDL_GetTicks(), ticks;
    SDL_Event events;
    while(gameRunning && jeu.getConstS1().getVivant() && jeu.getConstS2().getVivant())
    {
        ticks = SDL_GetTicks();
        if (ticks - starting_ticks > 1000 / fps)
        {
            sdlActionsAutomatiques();
            starting_ticks = ticks;
        }

        while(SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT) gameRunning = false;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
				switch (events.key.keysym.sym) {
				case SDLK_q:
					jeu.actionClavierSDL('q');
                    break;
				case SDLK_d:
					jeu.actionClavierSDL('d');    
					break;
				case SDLK_k:
					jeu.actionClavierSDL('k');
					break;
				case SDLK_m:
					jeu.actionClavierSDL('m');
					break;
                case SDLK_ESCAPE:
                    gameRunning = false;
				default: break;
                }
            }
        }
        //sdlAff();
        //SDL_RenderPresent(renderer);

    }
}