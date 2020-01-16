/**
 * @file entree_sortie.c
 * @author Alexandre LANGLADE
 * @brief Module de gestion des entrées et sorties du logiciel
 * @version 0.1
 * @date 2019-12-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ENTRESORTIE_H
#define ENTRESORTIE_H

int lire_un_entier(int * x, int min, int max);
int lire_un_chemin(char ** ch);
int lire_string(char ** s); 

#endif