/**
@brief Implémentation de la classe jeu


@file Terrain.cpp
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/

#include "Jeu.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

Jeu::Jeu() {}

Jeu::Jeu(int tailleX, int tailleY) {
    t = Terrain(tailleX, tailleY);
    s1 = Serpent(10,10);
    s2 = Serpent(t.getTailleX() - 10, t.getTailleY() - 10);
    s1.setDirection(0);
    s2.setDirection(180);
    cout<<"Construction Jeu : Check"<<endl;
}

Jeu::~Jeu() {}

Serpent& Jeu::getS1() {return s1;}

Serpent& Jeu::getS2() {return s2;}

const Serpent& Jeu::getConstS1() const {return s1;}

const Serpent& Jeu::getConstS2() const {return s2;}


void Jeu::actionsAutomatiquesTXT() {
    s1.avancerTXT(t);
    s2.avancerTXT(t);
    if(s1.VerifColision(t))
    {
        s1.setVivant(false);
    }
    if(s2.VerifColision(t))
    {
        s2.setVivant(false);
    }

}

void Jeu::actionsAutomatiquesSDL() {
    s1.avancerSDL(t);
    s2.avancerSDL(t);
    if(s1.VerifColision(t))
    {
        s1.setVivant(false);
    }
    if(s2.VerifColision(t))
    {
        s2.setVivant(false);
    }

}

void Jeu::actionClavierTXT(const char touche) {
    //Serpent 1 utilise q et d
    //Serpent 2 utilise k et m
    /*
    switch (touche)
    {
    case 'q':
        s1.setDirection((s1.getDirection() + 90 ) % 360);
        break;
    case 'd':
        s1.setDirection((s1.getDirection() + 270 ) % 360);
        break;
    case 'k':
        s2.setDirection((s2.getDirection() + 90 ) % 360);
        break;
    case 'm':
        s2.setDirection((s2.getDirection() + 270 ) % 360);    
    }*/
}

void Jeu::actionClavierSDL(bool J1GaucheAppuye, bool J1DroiteAppuye, bool J2GaucheAppuye, bool J2DroiteAppuye)
{
    //Serpent 1 utilise q et d
    //Serpent 2 utilise k et m
    int forceVirage = 10;
    if (J1GaucheAppuye) s1.setDirection(fmod(s1.getDirection() + 360 - forceVirage, 360));
    if (J1DroiteAppuye) s1.setDirection(fmod(s1.getDirection() + forceVirage, 360));
    if (J2GaucheAppuye) s2.setDirection(fmod(s2.getDirection() + 360 - forceVirage, 360));
    if (J2DroiteAppuye) s2.setDirection(fmod(s2.getDirection() + forceVirage, 360));
    
    /*
    switch (touche)
    {
    case 'q':
        s1.setDirection(fmod(s1.getDirection() + 340,360));
        break;
    case 'd':
        s1.setDirection(fmod(s1.getDirection() + 20,360));
        break;
    case 'k':
        s2.setDirection(fmod(s2.getDirection() + 340,360));
        break;
    case 'm':
        s2.setDirection(fmod(s2.getDirection() + 20,360));
        break;
    }*/
}

