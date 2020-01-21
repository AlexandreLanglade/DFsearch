#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"

void init_moteur()
{

}

void close_moteur()
{

}

int main()
{
    int erreur;
    init_moteur();
    system("clear");
    erreur = menu_ouverture();
    do
    {
        switch (erreur)
        {
        case 1:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_ouverture();
            break;
        
        case 2:
            system("clear");
            printf ("\033[31;01m(Err) Mot clé incorrect\033[00m\n");
            erreur = menu_texte();
            break;

        case 3:
            system("clear");
            erreur = menu_utilisateur();
            break;

        case 4:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_utilisateur();
            break;

        case 5:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_texte();
            break;
        
        case 6:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_image();
            break;

        case 7:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_audio();
            break;

        case 8:
            system("clear");
            printf ("\033[31;01m(Err) Chemin incorrect\033[00m\n");
            erreur = menu_texte();
            break;

        case 9:
            system("clear");
            printf ("\033[31;01m(Err) Chemin incorrect\033[00m\n");
            erreur = menu_image();
            break;

        case 10:
            system("clear");
            printf ("\033[31;01m(Err) Chemin incorrect\033[00m\n");
            erreur = menu_audio();
            break;

        case 11:
            system("clear");
            printf ("\033[31;01m(Err) Mot de passe incorrect\033[00m\n");
            erreur = menu_ouverture();
            break;

        case 12:
            system("clear");
            printf ("\033[31;01m(Err) Selection incorrecte\033[00m\n");
            erreur = menu_administrateur();
            break;

        case 13:
            system("clear");
            erreur = menu_administrateur();
            break;

        default:
            break;
        }
        
    } while (erreur != 0);
    close_moteur();
    return 0;
}