#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "functions.h"

int getopt (int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char *argv[])
{  
  int optch;  
  extern int opterr;  
  char format[] = "hvctruxfzdsm";  
  bool verbose = false;
  
  opterr = 1;  
  
  //boucle qui traite les options
  while ((optch = getopt(argc, argv, format)) != -1)  
    switch (optch)
    {  
      case 'h':  
        printf ("Aide :\n");
        printf ("Lister  : taar -t fichierTAR\n");
        printf ("Extraire  : taar -x fichierTAR cheminDeSortie\n");
        printf ("Compresser  : taar -z fichierTAR\n");
        break;

      case 'v':  
        printf ("Paramètre v recontré : mode verbose\n");
        verbose = true;
        break;

      case 'c':  
        printf ("Paramètre c recontré : creer une archive à partir d'une liste de fichiers (et de repertoires)\n");
        printf ("Non implémenté\n");
        break;  
      case 't':  
        // printf ("Paramètre t recontré : lister les fichiers contenus dans une archive\n");
        lister(argv[2]);
        break;

      case 'r':  
        printf ("Paramètre r recontré : ajouter de nouveaux fichiers (ou repertoires) à une archive existante\n");
        printf ("Non implémenté\n");
        break;  
      case 'u':  
        printf ("Paramètre u recontré : pour mettre à jour l'archive si les fichiers listes sont plus recents que ceux archives\n");
        printf ("Non implémenté\n");
        break;  
      case 'x':  
        // printf ("Paramètre x recontré : pour extraire les fichiers de l'archive\n");
        extraire(argv[2], argv[3]);
        break;

      case 'f':
        printf ("Paramètre f recontré : pour indiquer le nom du fichier archive, sinon tar utilise l'entree et la sortie standard avec les options precedentes\n");
        break;
      case 'z':  
        // printf ("Paramètre z recontré : pour compresser le fichier d'archive (en utilisant gzip)\n");
        compresser(argv[2]);
        break;

      case 'd':  
        printf ("Paramètre d recontré : pour supprimer un fichier d'une archive\n");
        printf ("Non implémenté\n");
        break;  
      case 's':  
        printf ("Paramètre s recontré\nAvec 'parse' : pour economiser de la place pour stocker les fichier contenant beaucoup de zeros consecutifs (sparse file)");
        printf ("Non implémenté\n");
        break;  
      case 'm':
        printf ("Paramètre m recontré : pour afficher les differences entre les fichiers archives et les fichiers existants en utilisant la commande Unix 'diff'\n");
        printf ("Non implémenté\n");
        break; 
    }

  return EXIT_SUCCESS;
}