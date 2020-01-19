#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/menu.h"

/*
void param_recherche()
{
    system("clear");
    int choix_param_recherche = 0;
    int code_retour = 0;
    do
    {
        printf("Vous allez modifier les paramètres de recherche. \n");
        printf("(1) Paramètres recherches par comparaison. \n");
        printf("(2) Paramètres recherches par spécificité. \n");
        printf("(3) Retour au menu principal. \n");
        printf("(4) Quitter le logiciel. \n");
        code_retour = lire_un_entier(&choix_param_recherche, 1, 4);
        if (choix_param_recherche == 1)
        {
            system("clear");
            printf("Vous allez modifier les paramètres de recherche par comparaison.\n");
            //MODIF PARAMETRES RECHERCHE PAR COMPARAISON
        }
        if (choix_param_recherche == 2)
        {
            system("clear");
            int choix_recherche_spe = 0;
            int code_retour_ = 0;
            do
            {
                printf("Vous allez modifier les paramètres de recherche par spécificité. \n");
                printf("(1) Modifier la recherche de textes par mots-clefs. \n");
                printf("(2) Modifier la recherche d'images par couleur dominante. \n");
                printf("(3) Modifier la recherche de sons par motif. \n");
                printf("(4) Retour au menu principal. \n");
                printf("(5) Quitter le logiciel. \n");
                code_retour_ = lire_un_entier(&choix_recherche_spe, 1, 5);

                if (choix_recherche_spe == 1)
                {
                    system("clear");
                    printf("Vous allez modifier les paramètres de recherche de textes par mots-clefs. \n\n");
                    //printf("");
                }

                if (choix_recherche_spe == 2)
                {
                    system("clear");
                    printf("Vous allez modifier les paramètres de recherche d'images par couleur dominante.\n");
                    //printf("");
                }

                if (choix_recherche_spe == 3)
                {
                    system("clear");
                    printf("Vous allez modifier les paramètres de recherche de sons par motifs. \n");
                    //printf("");
                }

                if (choix_recherche_spe == 4)
                {
                    system("clear");
                    //menu_ouverture();
                }

                if (choix_recherche_spe == 5)
                {
                    system("clear");
                    return;
                }

                if (choix_recherche_spe != 1 && choix_recherche_spe != 2 && choix_recherche_spe != 3 && choix_recherche_spe != 4 && choix_recherche_spe != 5)
                    printf("\nEntrée invalide. Veuillez entrer un des choix proposés.\n\n");
            } while (choix_recherche_spe != 1 && choix_recherche_spe != 2 && choix_recherche_spe != 3 && choix_recherche_spe != 4 && choix_recherche_spe != 5);
        }

        if (choix_param_recherche == 3)
        {
            system("clear");
            //menu_ouverture();
        }

        if (choix_param_recherche == 4)
        {
            return;
        }
        if (choix_param_recherche != 1 && choix_param_recherche != 2 && choix_param_recherche != 3 && choix_param_recherche != 4)
            printf("\nEntrée invalide. Veuillez entrer un des choix proposés. \n\n");
    } while (choix_param_recherche != 1 && choix_param_recherche != 2 && choix_param_recherche != 3 && choix_param_recherche != 4);
}
*/
int menu_texte()
{
    int choix_textes = 0;
    int code_retour = 0;
    char *mot_cle;
    char *chemin;
    printf("Vous avez choisi de rechercher des textes. \n");
    printf("(1) Recherche par mot-clef \n");
    printf("(2) Recherche par comparaison \n");
    printf("(3) Retour au menu utilisateur \n");
    printf("(4) Quitter le logiciel\n");
    code_retour = lire_un_entier(&choix_textes, 1, 4);
    if (code_retour == 0)
        return 5;
    if (choix_textes == 1)
    {
        code_retour = lire_string(&mot_cle);
        if (code_retour == 0)
        {
            return 2;
        }
        recherche_mot_cle();
        return 3;
    }
    else if (choix_textes == 2)
    {
        code_retour = lire_un_chemin(&chemin);
        if (code_retour == 0)
        {
            return 8;
        }
        comparaison_texte();
        return 3;
    }
    else if (choix_textes == 3)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

int menu_image()
{
    int choix_images = 0;
    int code_retour = 0;
    char *chemin;
    printf("Vous avez choisi de rechercher des images. \n");
    printf("(1) Recherche par couleur dominante \n");
    printf("(2) Recherche par comparaison \n");
    printf("(3) Retour au menu utilisateur \n");
    printf("(4) Quitter le logiciel \n");
    code_retour = lire_un_entier(&choix_images, 1, 4);
    if (code_retour == 0)
        return 6;
    if (choix_images == 1)
    {
        recherche_couleur_dominante();
        return 3;
    }
    else if (choix_images == 2)
    {
        code_retour = lire_un_chemin(&chemin);
        if (code_retour == 0)
        {
            return 9;
        }
        comparaison_image();
        return 3;
    }
    else if (choix_images == 3)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

int menu_audio()
{
    int choix_sons = 0;
    int code_retour = 0;
    char *chemin;
    printf("Vous avez choisi de rechercher des sons. \n");
    printf("(1) Recherche par motif \n");
    printf("(2) Recherche par comparaison \n");
    printf("(3) Retour au menu utilisateur \n");
    printf("(4) Quitter le logiciel \n");
    code_retour = lire_un_entier(&choix_sons, 1, 4);
    if (code_retour == 0)
        return 7;
    if (choix_sons == 1)
    {
        code_retour = lire_un_chemin(&chemin);
        if (code_retour == 0)
        {
            return 10;
        }
        recherche_motif();
        return 3;
    }
    else if (choix_sons == 2)
    {
        code_retour = lire_un_chemin(&chemin);
        if (code_retour == 0)
        {
            return 10;
        }
        comparaison_image();
        return 3;
    }
    else if (choix_sons == 3)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

int menu_utilisateur()
{
    int choix_menu_utilisateur = 0;
    int code_retour = 0;
    int code_retour_fils = 0;
    printf("Menu utilisateur :\n");
    printf("(1) Recherche de textes \n");
    printf("(2) Recherche d'images \n");
    printf("(3) Recherche de sons \n");
    printf("(4) Retour à l'acceuil \n");
    printf("(5) Quitter le logiciel \n");
    code_retour = lire_un_entier(&choix_menu_utilisateur, 1, 5);
    if (code_retour == 0)
        return 4;
    if (choix_menu_utilisateur == 1)
    {
        system("clear");
        code_retour_fils = menu_texte();
        return code_retour_fils;
    }
    else if (choix_menu_utilisateur == 2)
    {
        system("clear");
        code_retour_fils = menu_image();
        return code_retour_fils;
    }
    else if (choix_menu_utilisateur == 3)
    {
        system("clear");
        code_retour_fils = menu_audio();
        return code_retour_fils;
    }
    else if (choix_menu_utilisateur == 4)
    {
        system("clear");
        code_retour_fils = menu_ouverture();
        return code_retour_fils;
    }
    else
    {
        return 0;
    }
}

int menu_administrateur()
{
    int choix_menu_administrateur = 0;
    int code_retour = 0;
    printf("Menu administrateur :\n");
    printf("(1) Lancer l'indexation complète\n");
    printf("(2) Lancer l'indexation d'un fichier seul\n");
    printf("(3) Modifier la configuration\n");
    printf("(4) Passer en mode utilisateur\n");
    printf("(5) Quitter le logiciel \n");
    code_retour = lire_un_entier(&choix_menu_administrateur, 1, 5);
    if (code_retour == 0)
        return 12;
    if (choix_menu_administrateur == 1)
    {
        indexation();
        return 13;
    }
    else if (choix_menu_administrateur == 2)
    {
        indexation_un_doc();
        return 13;
    }
    else if (choix_menu_administrateur == 3)
    {
        modif_config();
        return 13;
    }
    else if (choix_menu_administrateur == 4)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

int mdp()
{
    char * mdp;
    printf("Mot de passe : "); 
    lire_string(&mdp);
    if (strcmp(mdp, "admin") == 0)
    { 
        return 13;
    }
    else
    {
        return 11;
    }
}

int menu_ouverture()
{
    int choix_mode = 0;
    int code_retour = 0;
    int code_retour_fils = 0;
    printf("La DufonSociety vous souhaite la bienvenue sur son moteur de recherche\n\n");
    printf("Pour accéder au mode utilisateur, veuillez saisir 1. \n");
    printf("Pour accéder au mode administrateur, veuillez saisir 2. \n");
    printf("Pour quitter le logiciel, veuillez saisir 3. \n");
    code_retour = lire_un_entier(&choix_mode, 1, 3);
    if (code_retour == 0)
        return 1;
    if (choix_mode == 1)
    {
        return 3;
    }
    else if (choix_mode == 2)
    {
        system("clear");
        code_retour_fils = mdp();
        return code_retour_fils;
    }
    else
    {
        return 0;
    }
}
