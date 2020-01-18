#include <stdio.h>
#include "../include/main.h"

void init_moteur()
{

}

void close_moteur()
{

}

int main(int argc, char const *argv[])
{
    int erreur;
    init_moteur();
    erreur = menu_ouverture();
    do
    {
        switch (erreur)
        {
        case 1:
            printf("(Err) Selection incorrecte\n");
            erreur = menu_ouverture();
            break;
        
        case 2:
            printf("(Err) Mot clé incorrect\n");
            erreur = menu_texte();
            break;

        case 3:
            erreur = menu_ouverture();
            break;

        case 4:
            printf("(Err) Selection incorrecte\n");
            erreur = menu_utilisateur();
            break;

        case 5:
            printf("(Err) Selection incorrecte\n");
            erreur = menu_texte();
            break;
        
        case 6:
            printf("(Err) Selection incorrecte\n");
            erreur = menu_image();
            break;

        case 7:
            printf("(Err) Selection incorrecte\n");
            erreur = menu_audio();
            break;

        case 8:
            printf("(Err) Chemin incorrect\n");
            erreur = menu_texte();
            break;

        case 9:
            printf("(Err) Chemin incorrect\n");
            erreur = menu_image();
            break;

        case 10:
            printf("(Err) Chemin incorrect\n");
            erreur = menu_audio();
            break;

        case 11:
            printf("(Err) Mot de passe incorrect\n");
            erreur = mdp();
            break;

        case 12:
            printf("(Err) Selection incorrecte\n");
            erreur = menu_administrateur();
            break;

        default:
            break;
        }
        
    } while (erreur != 0);
    close_moteur();
    return 0;
}