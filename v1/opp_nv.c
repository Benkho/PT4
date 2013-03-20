#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

int getopt (int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

const int TAILLE_BLOC = 512;


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
  taille_avec_header = taille_dec + 512;
  //printf("valeur taille_avec_header : %i\n", taille_avec_header);

  //on divise cette taille par la taille d'un bloc pour obtenir le nombre de blocs
  int nombre_de_blocs;
  nombre_de_blocs = taille_avec_header / 512;
  //printf("valeur nombre_de_blocs : %i\n", nombre_de_blocs );

  //on multiplie ce nombre de blocs par la taille d'un bloc et on ajoute un bloc pour dépasser la taille du fichier
  int depasse;
  depasse = (nombre_de_blocs * 512) + 512;
  //printf("valeur depasse : %i\n", depasse );

  //on soustrait à depasse la taille totale pour obtenir le dépassement
  int depassement;
  depassement = depasse - taille_avec_header;
  //printf("valeur depassement : %i\n", depassement );

  return depassement;
}

int main(int argc, char *argv[])
{  
  int optch;  
  extern int opterr;  
  
  char format[] = "hvctruxfzdsm";  
  
  opterr = 1;  
  
  while ((optch = getopt(argc, argv, format)) != -1)  
    switch (optch)
    {  
      case 'h':  
        printf ("Aide :\n");  
        printf ("Utilisation : tar [OPTION...] [FICHIER]...\n");  
        break;
      case 'v':  
        printf ("Paramètre v recontre : mode verbose\n");
        break;  
      case 'c':  
        printf ("Paramètre c recontre : creer une archive à partir d'une liste de fichiers (et de repertoires)\n");
        break;  
      case 't':  
        printf ("Paramètre t recontre : lister les fichiers (et repertoires) contenus dans une archive\n");
        break;  
      case 'r':  
        printf ("Paramètre r recontre : ajouter de nouveaux fichiers (ou repertoires) à une archive existante\n");
        break;  
      case 'u':  
        printf ("Paramètre u recontre : pour mettre à jour l'archive si les fichiers listes sont plus recents que ceux archives\n");
        break;  
      case 'x':  
        printf ("Paramètre x recontre : pour extraire les fichiers de l'archive\n");

        long taille_fichier_entier;
        taille_fichier_entier = taille_fichier(argv[2]);

        //ouverture du fichier TAR à desarchiver
        FILE *fr = NULL;
        fr = fopen(argv[2], "rb"); // en mode "read binary" 
        if (fr != NULL)
        {
          int end_file; end_file=0;

          while (end_file==0)
          {
            // on récupère le nom du fichier
            char filename[100];
            fread (filename, 100, 1, fr);

            // on créé le chemin complet du fichier de sortie
            char filepath[100];
            sprintf(filepath, "%s%s", argv[3], filename);

            //on créé un nouveau fichier portant ce nom
            FILE *file_n = NULL;
            file_n = fopen(filepath, "w");  // en mode write
            if (file_n != NULL)
            {
              fclose(file_n);
            }
		
		    char permissions[8];
		    fread (permissions, 8, 1, fr);
		    int perm_int;
		    perm_int = atoi(permissions);
		    char perm_cmd[100];
		    sprintf(perm_cmd, "chmod %i %s", perm_int, filepath);
		    printf("perm_cmd: %s\n",perm_cmd);
		    system(perm_cmd);

            char proprio[8];
            fread (proprio, 8, 1, fr);
            
            char groupe[8];
            fread (groupe, 8, 1, fr);
            
            char taille_octal_str[12];
            int taille_dec;
            fread (taille_octal_str, 12, 1, fr);
            taille_dec = ocToDec(atoi(taille_octal_str));
            
            char last_modif[12];
            fread (last_modif, 12, 1, fr);
            
            char checksum[8];
            fread (checksum, 8, 1, fr);
            
            char type[1];
            fread (type, 1, 1, fr);
            
            char linkname[100];
            fread (linkname, 100, 1, fr);
            
            char headrest[255];
            fread (headrest, 255, 1, fr);

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

            char testfinfichier[512];
            fread (testfinfichier, 512, 1, fr);

            end_file=1;
            int i; i = 0;
            while (end_file==1 && i<512)
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
        break;

      case 'f':
        printf ("Paramètre f recontre : pour indiquer le nom du fichier archive, sinon tar utilise l'entree et la sortie standard avec les options precedentes\n");
        break;
      case 'z':  
        printf ("Paramètre z recontre : pour compresser le fichier d'archive (en utilisant gzip)\n");
        break;  
      case 'd':  
        printf ("Paramètre d recontre : pour supprimer un fichier d'une archive\n");
        break;  
      case 's':  
        printf ("Paramètre s recontre\nAvec 'parse' : pour economiser de la place pour stocker les fichier contenant beaucoup de zeros consecutifs (sparse file)");
        break;  
      case 'm':  
        printf ("Paramètre m recontre : pour afficher les differences entre les fichiers archives et les fichiers existants en utilisant la commande Unix 'diff'\n");
        break; 
    }  

return 0;
}
