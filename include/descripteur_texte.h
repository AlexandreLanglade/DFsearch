#ifndef H_DESCTEXTE
#define H_DESCTEXTE

/*----------------------------------------------------------------------------------------------*/
/*Structures*/

typedef struct etTerme
{
    char *mot;
    int nbOccurences;
    struct etTerme *termeSuivant;
}Terme;

typedef struct descripteur_texte_s
{
    int identifiant;
    int nbMots;
    int nbTermes;
    struct descripteur_texte_s *suivant;
    struct etTerme *listeDesTermes;
}descripteur_texte;

typedef struct descripteur_texte_s * Descripteur_texte;

/*----------------------------------------------------------------------------------------------*/
/*En-têtes des fonctions*/

/*Descripteurs*/
Descripteur_texte init_DescripteurTexte();
void ajout_terme(Descripteur_texte descripteur, Terme *nouveau);
void deleteTerme(Descripteur_texte descripteur);
int isMotExistant(Descripteur_texte descripteur_texte, char *mot);
void setDtSuiv(Descripteur_texte a, Descripteur_texte b);

/*Termes*/
Terme* init_Terme();

#endif