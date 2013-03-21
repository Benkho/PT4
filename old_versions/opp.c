#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int getopt (int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char *argv[])
{  
  int optch;  
  extern int opterr;  
  
  char format[] = "hvctruxfzdsm";  
  
  opterr = 1;  
  
  while ((optch = getopt(argc, argv, format)) != -1)  
    switch (optch) {  
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
      printf ("Paramètre r recontre : ajouter de nouveaux fichiers (ou repertoires)\n");
      break;  
    case 'u':  
      printf ("Paramètre u recontre\n");
      break;  
    case 'x':  
      printf ("Paramètre x recontre\n");
      break;  
    case 'f':  
      printf ("Paramètre f recontre\n");
      break;  
    case 'z':  
      printf ("Paramètre z recontre\n");
      break;  
    case 'd':  
      printf ("Paramètre d recontre\n");
      break;  
    case 's':  
      printf ("Paramètre s recontre\n");
      break;  
    case 'm':  
      printf ("Paramètre m recontre\n");
      break; 
    }  

	//affichage des arguments
    for (; optind < argc; ++optind)  
        printf ("argv[%d] : %s\n", optind, argv[optind]);
    
    
    
    FILE *fr = NULL;
    fr = fopen(argv[1], "rb"); // ouverture fichier mode "read binary"
    
    //determination taille fichier
	fseek(fr, 0, SEEK_END);
	long taillef, nb_bloc;
	taillef = ftell(fr);
	nb_bloc = taillef/512;
	printf("taille du fichier ouvert : %d = 512 * %d octets\n", taillef, nb_bloc);
	fseek(fr, 0, SEEK_SET); // on remet le curseur au debut du fichier
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    
    if (fr == NULL) {printf("erreur ouverture fr\n");}
    else
    {
		printf("ouverture fr ok\n");

	    char t[nb_bloc*512];
	    //~ fread (t, 512, nb_bloc, fr);
	    printf("retour de fread : %i\n",  fread (t, 512, nb_bloc, fr));
	    
	    int p;
	    for (p=0; p<nb_bloc*512; p++)
		{
			printf("%i\n", t[p]);
		}
		
		
		FILE *fw = NULL;
	    fw = fopen(argv[2], "wb"); // ouverture fichier mode "write binary"
	    if (fr == NULL) {printf("erreur ouverture fr\n");}
	    else
	    {
			printf("ouverture fw ok\n");
			
			fwrite(t, 512, nb_bloc, fw);
			
			if (fclose(fw) != 0) {printf("erreur fermeture fw\n");}
			else {printf("fermeture fw ok\n");}
		}
   
	    if (fclose(fr) != 0) {printf("erreur fermeture fr\n");}
	    else {printf("fermeture fr ok\n");}
    }

 
    return 0;
      
}
