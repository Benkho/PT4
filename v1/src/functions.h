#ifndef FUNCTIONS_H
#define FUNCTIONS_H

long taille_fichier (char *filename);
int ocToDec(int octal);
int decalage_curseur_fichier_suivant (long current_location, long taille_dec);
void lister(char *file);
void extraire(char *filetar, char *sortie);
void compresser(char *file);

#endif