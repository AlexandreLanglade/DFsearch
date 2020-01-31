/**
 * @file entree_sortie.c
 * @author Alexandre LANGLADE
 * @brief Module de gestion des entrées et sorties du logiciel
 * @version 1.0
 * @date 2019-12-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/entree_sortie.h"

/**
 * @brief Fonction pour recevoir un entier de l'utilisateur
 * 
 * @param x Pointeur sur la variable où sauvegarder l'entrée
 * @param min Valeur minimum que peut prendre x
 * @param max Valeur maximum que peut prendre x
 * @return int : 0 en cas de mauvaise entrée, 1 sinon
 */
int lire_un_entier(int * x, int min, int max)
{
    long i;
    char entree[150];
    char * end;
    scanf("%s", entree);
    i = strtol(entree, &end, 10);
    if (end == entree) return 0;
    if (i >= min && i <= max)
    {
        *x = (int)i;
        return 1;
    }
    return 0;
}

/**
 * @brief Fonction pour recevoir un chemin de l'utilisateur
 * 
 * @param ch Pointeur sur la variable où sauvegarder l'entrée
 * @return int : 0 en cas de mauvaise entrée, 1 sinon
 */
int lire_un_chemin(char ** ch)
{
    char chemin[150];
    FILE * test = NULL;
    scanf("%s", chemin);
    *ch = (char *)malloc(sizeof(char) * (strlen(chemin) + 1));
    assert(*ch != NULL);
    *ch = strcpy(*ch, chemin);
    test = fopen(*ch, "r");
    if (test == NULL)
    {
        *ch = NULL;
        return 0;
    }
    fclose(test);
    return 1;
}

/**
 * @brief Fonction pour recevoir un char * de l'utilisateur
 * 
 * @param s Pointeur sur la variable où sauvegarder l'entrée
 * @return int : 0 en cas de mauvaise entrée, 1 sinon
 */
int lire_string(char ** s)
{
    char chemin[150];
    char * non = "AZERTYUIOPQSDFGHJKLMWXCVBN1234567890&-_à$!/:;.,?µ+";
    scanf("%s", chemin);
    *s = (char *)malloc(sizeof(char) * (strlen(chemin) + 1));
    assert(*s != NULL);
    *s = strcpy(*s, chemin);
    if (strpbrk(*s, non) != NULL)
    {
        return 0;
    }
    if ((*s)[strlen(*s)-1] == 's')
    {
        (*s)[strlen(*s)-1] = '\0';
    } 
    return 1;
}