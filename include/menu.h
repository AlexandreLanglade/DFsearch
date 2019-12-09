// Module de gestion des menus

int menu_utilisateur(int mode); // affiche le menu utilisateur et attend le choix (mode sert à enregistrer si admin ou non pour retour)
int menu_administrateur(); // affiche le menu admin et attend le choix

int sous_menu_texte(); // affiche le sous menu pour les textes + att choix
int sous_menu_image(); // affiche le sous menu pour les images + att choix
int sous_menu_audio(); // affiche le sous menu pour les audios + att choix

int afficher_liste_descripteurs(int type); // affiche liste descripteurs images ou texte ou audio
int afficher_un_descripteur(char * chemin);