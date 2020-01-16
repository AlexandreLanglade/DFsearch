/**
 * @file configuration.c
 * @author LANGLADE Alexandre
 * @brief Module gérant la configuration de l'indexation à partir du fichier .config
 * @version 1.0
 * @date 2020-01-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "./indexation_texte.h"
#include "./indexation_image.h"
#include "./indexation_audio.h"
#include "./pile.h"

void afficher_config();

int getModifTexte();
int getModifImage();
int getModifAudio();

int getConfig_texte_ValeurLimite();
int getConfig_texte_Seuil();
int getConfig_image_NbBits();
int getConfig_audio_NbEchant();
int getConfig_audio_NbInterv();

void modifier_config(int param, int valeur);

void indexation(Pile t, Pile im, Pile imrgb);

#endif