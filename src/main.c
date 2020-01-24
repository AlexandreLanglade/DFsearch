#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/main.h"

/**
 * @brief Fonction permettant d'initialiser le moteur au démarrage : indexation + remplissage des piles
 * 
 * @param t Pile des descripteurs pour les textes
 * @param im Pile des descripteurs pour les images NB
 * @param imrgb Pile des descripteurs pour les images RGB
 */
void init_moteur(Pile t, Pile im, Pile imrgb)
{
    int a, b;
    int i, compteur;
    char chemin[200];
    char aux[100];
    FILE * fp;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    Descripteur_image di;
    Descripteur_texte dt;

    system("ls ../data/Descripteurs/Textes/ | wc -l > temp");
    system("ls ../data/Corpus/Textes/ | wc -l >> temp");
    fp = fopen("temp", "r");
    fscanf(fp, "%d", &a);
    fscanf(fp, "%d", &b);
    if (a != b) c++;
    fclose(fp);

    system("ls ../data/Descripteurs/Images/ | wc -l > temp");
    system("ls ../data/Corpus/Images/NG/ | wc -l >> temp");
    fp = fopen("temp", "r");
    fscanf(fp, "%d", &a);
    fscanf(fp, "%d", &b);
    if (a != b/2) d++;
    fclose(fp);

    system("ls ../data/Descripteurs/ImagesRGB/ | wc -l > temp");
    system("ls ../data/Corpus/Images/RGB/ | wc -l >> temp");
    fp = fopen("temp", "r");
    fscanf(fp, "%d", &a);
    fscanf(fp, "%d", &b);
    if (a != b/2) e++;
    fclose(fp);
/*
    system("ls ../data/Descripteurs/Sons/ | wc -l > temp");
    system("ls ../data/Corpus/Sons/ | wc -l >> temp");
    fp = fopen("temp", "r");
    fscanf(fp, "%d", &a);
    fscanf(fp, "%d", &b);
    if (a != b/3) f++;
    fclose(fp);
*/
    system("rm temp");

    if (c+d+e+f != 0) {
        if (c != 0) system("rm ../data/Descripteurs/Textes/*");
        if (d != 0) system("rm ../data/Descripteurs/Images/*");
        if (e != 0) system("rm ../data/Descripteurs/ImagesRGB/*");
        if (f != 0) system("rm ../data/Descripteurs/Sons/*");
        system("clear");
        indexation(t, im, imrgb, c, d, e, f);
    }
    else {
        /* Texte */ 
        system("ls ../data/Descripteurs/Textes/ | wc -l > temp");
        system("ls ../data/Descripteurs/Textes/ >> temp");
        fp = fopen("temp", "r");
        fscanf(fp, "%d", &compteur);
        for (i = 0; i < compteur; i++)
        {
            fscanf(fp, "%s", aux);
            strcpy(chemin, "../data/Descripteurs/Textes/");
            strcat(chemin, aux);
            dt = init_DescripteurTexte();
            dt = lire_fich_texte(chemin);
            empiler_pile(t, dt, 1);
        }  
        fclose(fp);

        /* Image NB */
        system("ls ../data/Descripteurs/Images/ | wc -l > temp");
        system("ls ../data/Descripteurs/Images/ >> temp");
        fp = fopen("temp", "r");
        fscanf(fp, "%d", &compteur);
        for (i = 0; i < compteur; i++)
        {
            fscanf(fp, "%s", aux);
            strcpy(chemin, "../data/Descripteurs/Images/");
            strcat(chemin, aux);
            di = initDescript();
            lecture_descripteur_image(*di, chemin);
            empiler_pile(im, di, 2);
        }  
        fclose(fp);

        /* Image rgb */
        system("ls ../data/Descripteurs/ImagesRGB/ | wc -l > temp");
        system("ls ../data/Descripteurs/ImagesRGB/ >> temp");
        fp = fopen("temp", "r");
        fscanf(fp, "%d", &compteur);
        for (i = 0; i < compteur; i++)
        {
            fscanf(fp, "%s", aux);
            strcpy(chemin, "../data/Descripteurs/ImagesRGB/");
            strcat(chemin, aux);
            di = initDescript();
            lecture_descripteur_image(*di, chemin);
            empiler_pile(imrgb, di, 2);
        }  
        fclose(fp);
        system("rm temp");
    }
}

void close_moteur(Pile t, Pile im, Pile imrgb)
{
    Descripteur_image di;
    Descripteur_texte dt;
    /*Texte*/
    while (!estVide_pile(t))
    {
        dt = (Descripteur_texte)depiler_pile(t, 1);
        ecrire_fich_texte(dt);
    }
    /*Image*/
    while (!estVide_pile(im))
    {
        di = (Descripteur_image)depiler_pile(im, 2);
        ecriture_descripteur_image(*di, 0);
    }
    /*Image RGB*/
    while (!estVide_pile(imrgb))
    {
        di = (Descripteur_image)depiler_pile(imrgb, 2);
        ecriture_descripteur_image(*di, 1);
    }
}

int main()
{
    int erreur;
    Pile t = initialiser_pile(1);
    Pile im = initialiser_pile(2);
    Pile imrgb = initialiser_pile(2);
    init_moteur(t, im, imrgb);
    system("clear");
    erreur = menu_ouverture(t, im, imrgb);
    do
    {
        switch (erreur)
        {
        case 1:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_ouverture(t, im, imrgb);
            break;
        
        case 2:
            system("clear");
            printf ("\033[31;01m(Err) Mot clé incorrect\033[00m\n");
            erreur = menu_texte(t, im, imrgb);
            break;

        case 3:
            system("clear");
            erreur = menu_utilisateur(t, im, imrgb);
            break;

        case 4:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_utilisateur(t, im, imrgb);
            break;

        case 5:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_texte(t, im, imrgb);
            break;
        
        case 6:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_image(t, im, imrgb);
            break;

        case 7:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_audio(t, im, imrgb);
            break;

        case 8:
            system("clear");
            printf ("\033[31;01m(Err) Chemin incorrect\033[00m\n");
            erreur = menu_texte(t, im, imrgb);
            break;

        case 9:
            system("clear");
            printf ("\033[31;01m(Err) Chemin incorrect\033[00m\n");
            erreur = menu_image(t, im, imrgb);
            break;

        case 10:
            system("clear");
            printf ("\033[31;01m(Err) Chemin incorrect\033[00m\n");
            erreur = menu_audio(t, im, imrgb);
            break;

        case 11:
            system("clear");
            printf ("\033[31;01m(Err) Mot de passe incorrect\033[00m\n");
            erreur = menu_ouverture(t, im, imrgb);
            break;

        case 12:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_administrateur(t, im, imrgb);
            break;

        case 13:
            system("clear");
            erreur = menu_administrateur(t, im, imrgb);
            break;

        default:
            break;
        }
        
    } while (erreur != 0);
    close_moteur(t, im, imrgb);
    return 0;
}