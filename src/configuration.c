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

#include "../include/configuration.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * @brief Fonction ouvrant le fichier .config
 * 
 * @return FILE* correspondant au fichier .config
 */
FILE * open()
{
    FILE* f = NULL;
    f = fopen("../.config", "r+");
    assert(f != NULL);
    return f;
}

/**
 * @brief Fonction fermant le fichier .config
 * 
 * @param f le fichier à fermer
 */
void close(FILE * f)
{
    fclose(f);
}

/**
 * @brief Affiche la configuration actuelle
 * 
 */
void afficher_config()
{
    int tab[8];
    FILE * f = open();
    fscanf(f, "%d %d %d %d %d %d %d %d", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5], &tab[6], &tab[7]);
    close(f);
    printf("*** Config texte : ***\n");
    printf("(1) Valeur limite: %d mots les plus présents.\n", tab[3]);
    printf("(2) Seuil : mot qui apparaissent plus de %d fois.\n", tab[4]);
    printf("*** Config image : ***\n");
    printf("(3) Nombre de bits : %d.\n", tab[5]);
    printf("*** Config audio : ***\n");
    printf("(4) Nombre d'échantillons : %d dans une fenetre d'analyse.\n", tab[6]);
    printf("(5) Nombre d'intervalles : %d.\n", tab[7]);
}

/**
 * @brief Fonction interne à configuration.c pour lire le fichier config
 * 
 * @param x le paramètre que l'on souhaite lire
 * @return int la valeur du paramètre
 */
int get(int x)
{
    FILE * f;
    int tab[8];
    assert(x > 0 && x <= 8);
    f = open();
    fscanf(f, "%d %d %d %d %d %d %d %d", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5], &tab[6], &tab[7]);
    close(f);
    return tab[x-1];
}

/**
 * @brief Surveille la modification des parametres pour les textes
 * 
 * @return int 0 si non modifiés, 1 autrement
 */
int getModifTexte()
{
    return get(1);
}

/**
 * @brief Surveille la modification des parametres pour les images
 * 
 * @return int 0 si non modifiés, 1 autrement
 */
int getModifImage()
{
    return get(2);
}

/**
 * @brief Surveille la modification des parametres pour les audios
 * 
 * @return int 0 si non modifiés, 1 autrement
 */
int getModifAudio()
{
    return get(3);
}

/**
 * @brief Renvoie le paramètre Valeur Limite pour les textes
 * 
 * @return int la valeur du paramètre
 */
int getConfig_texte_ValeurLimite()
{
    return get(4);
}

/**
 * @brief Renvoie le paramètre Seuil pour les textes
 * 
 * @return int la valeur du paramètre
 */
int getConfig_texte_Seuil()
{
    return get(5);
}

/**
 * @brief Renvoie le paramètre Nombre de Bits pour les images
 * 
 * @return int la valeur du paramètre
 */
int getConfig_image_NbBits()
{
    return get(6);
}

/**
 * @brief Renvoie le paramètre Nombre d'échantillons pour les audios
 * 
 * @return int la valeur du paramètre
 */
int getConfig_audio_NbEchant()
{
    return get(7);
}

/**
 * @brief Renvoie le paramètre Nombre d'intervalles pour les audios
 * 
 * @return int la valeur du paramètre
 */
int getConfig_audio_NbInterv()
{
    return get(8);
}

/**
 * @brief Fonction permettant une modification de la configuration
 * 
 * @param param le paramètre à modifier
 * @param valeur la nouvelle valeur à attribuer au paramètre
 */
void modifier_config(int param, int valeur)
{
    int tab[8];
    FILE * f;
    assert(param >= 1 && param <= 5);
    f = open();
    fscanf(f, "%d %d %d %d %d %d %d %d", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5], &tab[6], &tab[7]);
    tab[param+2] = valeur;
    if (param == 1 || param == 2)
    {
        tab[0] = 1;
    } else if (param == 3)
    {
        tab[1] = 1;
    } else
    {
        tab[2] = 1;
    }
    rewind(f);
    fprintf(f, "%d %d %d %d %d %d %d %d", tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7]);
    close(f);
}

/**
 * @brief Fonction d'indexation générale
 * 
 * @param t Pile des descripteurs pour les textes
 * @param im Pile des descripteurs pour les images NB
 * @param imrgb Pile des descripteurs pour les images RGB
 */
void indexation(Pile t, Pile im, Pile imrgb, int c, int d, int e, int fbis) {
    int i, compteur, r;
    char chemin[200];
    char chemin2[200];
    char aux[100];
    char str[12];
    FILE * f;

    printf("Indexation en cours .....\n");
    if (d == 1)
    {
        /* indexation image NB */
        system("rm ../data/listing_desc_imageNB.txt");
        system("ls ../data/Corpus/Images/NG/ | wc -l > templisteimage");
        system("ls ../data/Corpus/Images/NG/ >> templisteimage");
        f = fopen("templisteimage", "r");
        assert(f != NULL);
        fscanf(f, "%d", &compteur);
        for (i = 0; i < compteur/2; i++)
        {
            fscanf(f, "%s", aux);
            fscanf(f, "%s", aux);
            strcpy(chemin, "../data/Corpus/Images/NG/");
            strcat(chemin, aux);
            index_une_image(im, chemin, 1);
        }
        fclose(f);
        system("rm templisteimage");
    }
    
    
    if (e == 1)
    {
        /* indexation image RGB */
        system("rm ../data/listing_desc_imageRGB.txt");
        system("ls ../data/Corpus/Images/RGB/ | wc -l > templisteimagergb");
        system("ls ../data/Corpus/Images/RGB/ >> templisteimagergb");
        f = fopen("templisteimagergb", "r");
        assert(f != NULL);
        fscanf(f, "%d", &compteur);
        for (i = 0; i < compteur/2; i++)
        {
            fscanf(f, "%s", aux);
            fscanf(f, "%s", aux);
            strcpy(chemin, "../data/Corpus/Images/RGB/");
            strcat(chemin, aux);
            index_une_image(imrgb, chemin, 3);
        }
        fclose(f);
        system("rm templisteimagergb");
    }

    if (c == 1)
    {
        /* indexation texte */
        system("rm ../data/links_txt");
        system("ls ../data/Corpus/Textes/ | wc -l > templistetexte");
        system("ls ../data/Corpus/Textes/ >> templistetexte");
        f = fopen("templistetexte", "r");
        assert(f != NULL);
        fscanf(f, "%d", &compteur);
        for (i = 0; i < compteur; i++)
        {
            fscanf(f, "%s", aux);
            strcpy(chemin, "../data/Corpus/Textes/");
            strcat(chemin, aux);
            index_un_texte(chemin, t);
        }
        fclose(f);
        system("rm templistetexte");
    }
    
    if (fbis == 1)
    {
        /* indexation audio */
        /*rm link*/
        system("ls ../data/Corpus/Sons/ | wc -l > templisteson");
        system("ls ../data/Corpus/Sons/ >> templisteson");
        f = fopen("templisteson", "r");
        assert(f != NULL);
        fscanf(f, "%d", &compteur);
        for (i = 0; i < compteur/3; i++)
        {
            fscanf(f, "%s", aux);
            fscanf(f, "%s", aux);
            strcpy(chemin, "../data/Corpus/Sons/");
            strcat(chemin, aux);
            sprintf(str, "%d", i);
            strcpy(chemin2, "../data/Descripteurs/Sons/");
            strcat(chemin2, str);
            r = indexationAudio(chemin, chemin2, i);
            fscanf(f, "%s", aux);
        }
        fclose(f);
        system("rm templisteson");
    }
          
}
