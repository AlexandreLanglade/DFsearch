/**
 * @file pile.c
 * @author LANGLADE Alexandre
 * @brief Pile générique pour les descripteurs
 * @version 0.9
 * @date 2019-12-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/pile.h"

/**
 * @brief Structure d'une pile générique
 * 
 */
struct pile_s
{
    int type; /* 1texte 2image 3audio */
    Descripteur_texte dt;
    Descripteur_image di;
    /*Descripteur_audio da;*/
};

/**
 * @brief Fonction qui initialise une pile vide
 * 
 * @param type Type des descripteurs dans la pile (1:texte/2:image/3:audio)
 * @return Pile vide
 */
Pile initialiser_pile(int type)
{
    assert(type > 0 && type <= 3);
    Pile res = (Pile)malloc(sizeof(struct pile_s));
    assert(res != NULL);
    res->dt = NULL;
    res->di = NULL;
    /*res->da = NULL;*/
    res->type = type;
    return res;
}

/**
 * @brief Fonction ajoutant un descripteur à la pile
 * 
 * @param p La pile sur laquelle empiler
 * @param elt_descripteur Le descripteur à empiler
 * @param type Le type des descripteur de la pile (1:texte/2:image/3:audio)
 */
void empiler_pile(Pile p, void * elt_descripteur, int type)
{
    assert(p->type == type);
    if (p->type == 1)
    {
        if (p->dt != NULL) setDtSuiv(elt_descripteur, p->dt);
        p->dt = elt_descripteur;
    } else if (p->type == 2)
    {
        if (p->di != NULL) setDiSuiv(elt_descripteur, p->di);
        p->di = elt_descripteur;
    } else
    {
        /*if (p->da != NULL) setDaSuiv(elt_descripteur, p->da);
        p->da = elt_descripteur;*/
    }  
}

/**
 * @brief Fonction indiquant si la pile est vide ou non
 * 
 * @param p La pile à regarder
 * @return int 
 */
int estVide_pile(Pile p)
{
    return (p->dt == NULL && p->di == NULL /*&& p->da == NULL*/);
}

/**
 * @brief Fonction retirant le descripteur au sommet de la pile
 * 
 * @param p La pile que l'on souhaite dépiler
 * @param type Le type des descripteur de la pile (1:texte/2:image/3:audio)
 * @return void* Le descripteur qui était au sommet de la pile
 */
void * depiler_pile(Pile p, int type)
{
    assert(p->type == type);
    assert(!estVide_pile(p));
    void * aux;
    if (p->type == 1)
    {
        aux = p->dt;
        p->dt = p->dt->suivant;
    } else if (p->type == 2)
    {
        aux = p->di;
        p->di = p->di->desc_suiv;
    } else
    {
        /*aux = p->da;
        p->da = getDaSuiv(p->da);*/
    }
    return aux;    
}

/**
 * @brief Fonction renvoyant le descripteur au sommet de la pile
 * 
 * @param p La pile que l'on souhaite traiter
 * @param type Le type des descripteur de la pile (1:texte/2:image/3:audio) 
 * @return void* Le descripteur au sommet de la pile
 */
void * top_pile(Pile p, int type)
{
    assert(p->type == type);
    assert(!estVide_pile(p));
    if (p->type == 1)
    {
        return p->dt;
    } else if (p->type == 2)
    {
        return p->di;
    } else
    {
        /*return p->da;*/
    }  
}