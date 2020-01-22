#ifndef MENU_H
#define MENU_H

#include "pile.h"
#include "wait.h"
#include "entree_sortie.h"
#include "configuration.h"

int menu_texte(Pile t, Pile im, Pile imrgb);
int menu_image(Pile t, Pile im, Pile imrgb);
int menu_audio(Pile t, Pile im, Pile imrgb);
int menu_utilisateur(Pile t, Pile im, Pile imrgb);
int menu_administrateur(Pile t, Pile im, Pile imrgb);
int mdp();
int menu_ouverture(Pile t, Pile im, Pile imrgb);

#endif