#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "descripteur_texte.h"
#include "indexation_texte.h"
#include "pile.h"
#include "recherche_texte.h"

int main(int argc, char const *argv[])
{
    int fini=0,i,compteur,finitopipito=0;
    char **resultat;
    char aux[100];
    char chemin[200];
    Pile pile;
    FILE *f;
    Descripteur_texte dt;
    pile = initialiser_pile(1);

    i=0;
    /*
    index_un_texte("/home/aniss/Documents/testFinal/TEXTES/Textes/03-Des_chercheurs_parviennent_α_rΘgΘnΘrer.xml",pile);
    index_un_texte("/home/aniss/Documents/testFinal/TEXTES/Textes/03-Mimer_un_signal_nerveux_pour.xml",pile);
    index_un_texte("/home/aniss/Documents/testFinal/TEXTES/Textes/08-ThΘΓtre___l_ΘchappΘe_belle,_peu.xml",pile);
    index_un_texte("/home/aniss/Documents/testFinal/TEXTES/Textes/10-Le_cyclone_Katrina_complique_le.xml",pile);
    index_un_texte("/home/aniss/Documents/testFinal/TEXTES/Textes/22-Dominique_Noδl____Les_architectes.xml",pile);
    */

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
            index_un_texte(chemin, pile);
        }
        fclose(f);
        system("rm templistetexte");

    do{
        printf("Quel mot chercher ? :");
        char mot[50];
        scanf("%s",mot);
        
        resultat=recherche_mot_cle(pile,mot);   

        i=0;
        fini=0;
        while(i<10 && fini==0)
        {
            if (strcmp("fin",resultat[i])==0)
            {
                fini =1;
            }
            else
            {
            printf("%s \n", resultat[i]);        
            }
            
            i++;
        }
        
        free(resultat);
        printf("Si vous souhaitez arreter la recherche tapez 1: \n");
        scanf("%d",&finitopipito);

    }while (finitopipito!=1);
   

    while (!estVide_pile(pile))
    {
        dt = (Descripteur_texte)depiler_pile(pile, 1);
        ecrire_fich_texte(dt);
    }

    return 0;
}

