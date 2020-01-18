/**
 * @file pile.h
 * @author LANGLADE Alexandre
 * @brief Pile générique pour les descripteurs
 * @version 0.9
 * @date 2019-12-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef H_PILE
#define H_PILE

#include "./descripteur_texte.h"
#include "./descripteur_image.h"
/*#include "include/descripteur_audio.h"*/

typedef struct pile_s * Pile;

Pile initialiser_pile(int type);
void empiler_pile(Pile p, void * elt_descripteur, int type);
int estVide_pile(Pile p);
void * depiler_pile(Pile p, int type);
void * top_pile(Pile p, int type);

#endif