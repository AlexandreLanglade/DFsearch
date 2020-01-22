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
    assert(x > 0 && x <= 8);
    int tab[8];
    FILE * f = open();
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
    assert(param >= 1 && param <= 5);
    int tab[8];
    FILE * f = open();
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

void indexation(Pile t, Pile im, Pile imrgb) {

    /* indexation texte */
    if (getModifTexte() == 1)
    {
        system("ls ../data/Corpus/Textes/ > templistetexte");
        FILE* f = NULL;
        f = fopen("templistetexte", "r");
        assert(f != NULL);
        char chem[100];
        while (!feof(f))
        {
            fscanf(f, "%s", chem);
            index_un_texte(t, chem);
        }
        fclose(f);
        system("rm templistetexte");
    }
    else
    {
        /* code */
    }

    /* indexation image */
    if (getModifImage() == 1)
    {
        system("ls ../data/Corpus/Images/NG > templisteimage");
        FILE* f = NULL;
        f = fopen("templisteimage", "r");
        assert(f != NULL);
        char chem[100];
        while (!feof(f))
        {
            fscanf(f, "%s", chem);
            fscanf(f, "%s", chem);
            index_une_image(im, chem, 1);
        }
        fclose(f);
        system("rm templisteimage");

        system("ls ../data/Corpus/Images/RGB > templisteimage");
        FILE* f = NULL;
        f = fopen("templisteimage", "r");
        assert(f != NULL);
        char chem[100];
        while (!feof(f))
        {
            fscanf(f, "%s", chem);
            fscanf(f, "%s", chem);
            /*potentiel bug avec \n fin du ls*/
            index_une_image(imrgb, chem, 3);
        }
        fclose(f);
        system("rm templisteimage");
    }
    else
    {
        /* code */
    }

    /* indexation audio */
    if (getModifAudio() == 1)
    {
        /* code */
    }
    else
    {
        /* code */
    }
}
