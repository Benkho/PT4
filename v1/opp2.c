#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int getopt (int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

const int TAILLE_BLOC = 512;

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
      printf ("Paramètre v recontré : mode verbose\n");
      break;  
    case 'c':  
		printf ("Paramètre c recontré : créer une archive à partir d'une liste de fichiers (et de répertoires)\n");
		
		
	    //affichage des arguments
	    for (; optind < argc; ++optind)  
	        printf ("argv[%d] : %s\n", optind, argv[optind]);
	    
	    printf("argc :%d\n", argc);
	    printf("optind :%d\n", optind);
	    
	    int ar;
	    for (ar=3; ar<argc; ar++)
	    {
			printf("etat de ar : %d\n", ar);
		    FILE *fr = NULL;
		    fr = fopen(argv[ar], "rb"); // ouverture fichier mode "read binary" 

		    if (fr == NULL) {printf("erreur ouverture fr\n");}
		    else
		    {
				printf("ouverture fr ok\n");
				
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~determination taille fichier~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				fseek(fr, 0, SEEK_END);
				long taillef, nb_bloc;
				taillef = ftell(fr);
				nb_bloc = taillef/TAILLE_BLOC;
				printf("taille du fichier ouvert : %d = 512 * %d octets\n", taillef, nb_bloc);
				fseek(fr, 0, SEEK_SET); // on remet le curseur au debut du fichier
			    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		
			    char t[nb_bloc*TAILLE_BLOC];
			    //~ fread (t, 512, nb_bloc, fr);
			    printf("retour de fread : %i\n",  fread (t, TAILLE_BLOC, nb_bloc, fr));
			    /*
			    int p;
			    for (p=0; p<nb_bloc*512; p++)
				{
					printf("%i\n", t[p]);
				}
				*/
				
				FILE *fw = NULL;
			    fw = fopen(argv[2], "ab"); // ouverture fichier mode "add binary"
			    if (fr == NULL) {printf("erreur ouverture fr\n");}
			    else
			    {
					printf("ouverture fw ok\n");
					
					char tab_header[100];
					tab_header[0]='h';
					tab_header[1]='e';
					tab_header[2]='a';
					tab_header[3]='d';
					tab_header[4]='e';
					tab_header[5]='r';
					tab_header[6]='9';
					tab_header[7]='9';
					printf("retour de fwrite : %i\n", fwrite(tab_header, 8, 1, fw));
					printf("retour de fwrite : %i\n", fwrite(t, TAILLE_BLOC, nb_bloc, fw));
					
					if (fclose(fw) != 0) {printf("erreur fermeture fw\n");}
					else {printf("fermeture fw ok\n");}
				}
		   
			    if (fclose(fr) != 0) {printf("erreur fermeture fr\n");}
			    else {printf("fermeture fr ok\n");}
		    }
	
		}
		
      
      
      
      
      
      break;  
    case 't':  
      printf ("Paramètre t recontré : lister les fichiers (et répertoires) contenus dans une archive\n");
      break;  
    case 'r':  
      printf ("Paramètre r recontré : ajouter de nouveaux fichiers (ou repertoires)\n");
      break;  
    case 'u':  
      printf ("Paramètre u recontré\n");
      break;  
    case 'x':  
      printf ("Paramètre x recontré\n");
      break;  
    case 'f':  
      printf ("Paramètre f recontré\n");
      break;  
    case 'z':  
      printf ("Paramètre z recontré\n");
      break;  
    case 'd':  
      printf ("Paramètre d recontré\n");
      break;  
    case 's':  
      printf ("Paramètre s recontré\n");
      break;  
    case 'm':  
      printf ("Paramètre m recontré\n");
      break; 
    }  

 
    return 0;
      
}
