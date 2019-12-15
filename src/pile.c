/**
 * @file pile.c
 * @author LANGLADE Alexandre
 * @brief Pile générique pour les descripteurs
 * @version 0.1
 * @date 2019-12-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "include/pile.h"

struct pile_s
{
    int texte;
    int image;
    int audio;
    Descripteur_texte dt;
    Descripteur_image di;
    Descripteur_audio da;
};
