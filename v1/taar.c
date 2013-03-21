#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int getopt (int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

const int TAILLE_BLOC = 512;
const int TAILLE_NOM_FICHIER = 100;
const int TAILLE_PERMISSIONS = 8;
const int TAILLE_PROPRIETAIRE = 8;
const int TAILLE_GROUPE = 8;
const int TAILLE_TAILLE_FICHIER = 12;
const int TAILLE_DERNIERE_MODIF = 12;
const int TAILLE_CHEKSUM = 8;
const int TAILLE_TYPE = 1;
const int TAILLE_NOM_FICHIER_LIE = 100;
const int TAILLE_USTAR_HEADER = 255;
const int TAILLE_FIN_HEADER = 376;


long taille_fichier (char *filename)
{
  long taille_fichier_entier;
  FILE *f = NULL;
  f = fopen(filename, "rb"); // en mode "read binary" 
  if (f != NULL)
  {
    fseek(f, 0, SEEK_END); // on fixe le curseur à la fin du fichier
    taille_fichier_entier = ftell(f); // ftell lit la valeur du curseur
    fclose(f);
  }  
  return taille_fichier_entier;
}

int ocToDec(int octal)
{
  long int decimal =0;
  int i=0;
  while(octal!=0)
  {
    decimal = decimal + (octal % 10) * pow(8,i++);
    octal = octal/10;
  }
  return decimal;
}

int decalage_curseur_fichier_suivant (long current_location, long taille_dec)
{
  //calcul de la taille du fichier traité en cours avec son header
  int taille_avec_header;
  taille_avec_header = taille_dec + TAILLE_BLOC;
  //printf("valeur taille_avec_header : %i\n", taille_avec_header);

  //on divise cette taille par la taille d'un bloc pour obtenir le nombre de blocs
  int nombre_de_blocs;
  nombre_de_blocs = taille_avec_header / TAILLE_BLOC;
  //printf("valeur nombre_de_blocs : %i\n", nombre_de_blocs );

  //on multiplie ce nombre de blocs par la taille d'un bloc et on ajoute un bloc pour dépasser la taille du fichier
  int depasse;
  depasse = (nombre_de_blocs * TAILLE_BLOC) + TAILLE_BLOC;
  //printf("valeur depasse : %i\n", depasse );

  //on soustrait à depasse la taille totale pour obtenir le dépassement
  int depassement;
  depassement = depasse - taille_avec_header;
  //printf("valeur depassement : %i\n", depassement );

  return depassement;
}

void lister(char *file)
{
  long taille_fichier_entier;
  taille_fichier_entier = taille_fichier(file);

  //ouverture du fichier TAR à desarchiver
  FILE *fr = NULL;
  fr = fopen(file, "rb"); // en mode "read binary" 
  if (fr != NULL)
  {
    int end_file; end_file=0;

    while (end_file==0)
    {
      // on récupère le nom du fichier
      char filename[TAILLE_NOM_FICHIER];
      fread (filename, TAILLE_NOM_FICHIER, 1, fr);
      printf("Nom du fichier : %s\n", filename);

      fseek(fr, 24, SEEK_CUR);
      
      char taille_octal_str[TAILLE_TAILLE_FICHIER];
      int taille_dec;
      fread (taille_octal_str, TAILLE_TAILLE_FICHIER, 1, fr);
      taille_dec = ocToDec(atoi(taille_octal_str));
      printf("Taille du fichier : %i\n", taille_dec);

      fseek(fr, (taille_dec+TAILLE_FIN_HEADER), SEEK_CUR);
      
      //------------------------------------------------------------------------------------------------------------------------


      int decalage;
      decalage = decalage_curseur_fichier_suivant(ftell(fr), taille_dec);
      fseek(fr, decalage, SEEK_CUR);  

      long sauv_position_curseur; sauv_position_curseur = ftell(fr);

      char testfinfichier[TAILLE_BLOC];
      fread (testfinfichier, TAILLE_BLOC, 1, fr);

      end_file=1;
      int i; i = 0;
      while (end_file==1 && i<TAILLE_BLOC)
      {
        if (testfinfichier[i] != 0)
        {
          end_file=0;
        }
        i++;
      }

      fseek(fr, sauv_position_curseur, SEEK_SET);
    }
    fseek(fr, 0, SEEK_END);
    fclose(fr);
  }
}

void extraire(char *filetar, char *sortie)
{
  long taille_fichier_entier;
  taille_fichier_entier = taille_fichier(filetar);

  //ouverture du fichier TAR à desarchiver
  FILE *fr = NULL;
  fr = fopen(filetar, "rb"); // en mode "read binary" 
  if (fr != NULL)
  {
    int end_file; end_file=0;

    while (end_file==0)
    {
      // on récupère le nom du fichier
      char filename[TAILLE_NOM_FICHIER];
      fread (filename, TAILLE_NOM_FICHIER, 1, fr);

      // on créé le chemin complet du fichier de sortie
      char filepath[100];
      sprintf(filepath, "%s%s", sortie, filename);

      //on créé un nouveau fichier portant ce nom
      FILE *file_n = NULL;
      file_n = fopen(filepath, "w");  // en mode write
      if (file_n != NULL)
      {
        fclose(file_n);
      }

      char permissions[TAILLE_PERMISSIONS];
      fread (permissions, TAILLE_PERMISSIONS, 1, fr);
      int perm_int;
      perm_int = atoi(permissions);
      char perm_cmd[100];
      sprintf(perm_cmd, "chmod %i %s", perm_int, filepath);
      system(perm_cmd);

      char proprio[TAILLE_PROPRIETAIRE];
      fread (proprio, TAILLE_PROPRIETAIRE, 1, fr);
      
      char groupe[TAILLE_GROUPE];
      fread (groupe, TAILLE_GROUPE, 1, fr);
      
      char taille_octal_str[TAILLE_TAILLE_FICHIER];
      int taille_dec;
      fread (taille_octal_str, TAILLE_TAILLE_FICHIER, 1, fr);
      taille_dec = ocToDec(atoi(taille_octal_str));
      
      char last_modif[TAILLE_DERNIERE_MODIF];
      fread (last_modif, TAILLE_DERNIERE_MODIF, 1, fr);
      
      char checksum[TAILLE_CHEKSUM];
      fread (checksum, TAILLE_CHEKSUM, 1, fr);
      
      char type[TAILLE_TYPE];
      fread (type, TAILLE_TYPE, 1, fr);
      
      char linkname[TAILLE_NOM_FICHIER_LIE];
      fread (linkname, TAILLE_NOM_FICHIER_LIE, 1, fr);
      
      char headrest[TAILLE_USTAR_HEADER];
      fread (headrest, TAILLE_USTAR_HEADER, 1, fr);

      char *fileraw;
      fileraw = malloc(taille_dec*sizeof(char));
      // char fileraw[taille_dec];
      fread (fileraw, 1, taille_dec, fr);
      
      //------------------------------------------------------------------------------------------------------------------------

      //ecriture du fichier lui même [ 512 -> ...]
      file_n = fopen(filepath, "ab");  /* add binary */
      if (file_n != NULL)
      {
        fwrite(fileraw, 1, taille_dec, file_n);
        fclose(file_n);
      }

      int decalage;
      decalage = decalage_curseur_fichier_suivant(ftell(fr), taille_dec);
      fseek(fr, decalage, SEEK_CUR);  

      long sauv_position_curseur; sauv_position_curseur = ftell(fr);

      char testfinfichier[TAILLE_BLOC];
      fread (testfinfichier, TAILLE_BLOC, 1, fr);

      end_file=1;
      int i; i = 0;
      while (end_file==1 && i<TAILLE_BLOC)
      {
        if (testfinfichier[i] != 0)
        {
          end_file=0;
        }
        i++;
      }

      fseek(fr, sauv_position_curseur, SEEK_SET);
      free(fileraw);
    }
    fseek(fr, 0, SEEK_END);
    fclose(fr);
  }
}

void compresser(char *file)
{
  char cmd[100];
  sprintf(cmd, "gzip -9 %s", file);
  system(cmd);
}


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
        printf ("Paramètre t recontré : lister les fichiers (et repertoires) contenus dans une archive\n");
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
        printf ("Paramètre x recontré : pour extraire les fichiers de l'archive\n");
        extraire(argv[2], argv[3]);
        break;

      case 'f':
        printf ("Paramètre f recontré : pour indiquer le nom du fichier archive, sinon tar utilise l'entree et la sortie standard avec les options precedentes\n");
        break;
      case 'z':  
        printf ("Paramètre z recontré : pour compresser le fichier d'archive (en utilisant gzip)\n");
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
}