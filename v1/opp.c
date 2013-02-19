#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
  
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

	//affichage des arguments
    for (; optind < argc; ++optind)  
        printf ("argv[%d] : %s\n", optind, argv[optind]);
    
    
    
    FILE *fr = NULL;
    fr = fopen(argv[1], "rb"); // ouverture fichier mode "read binary"
    if (fr == NULL) {printf("erreur ouverture fr\n");}
    else
    {
		printf("ouverture fr ok\n");
		fseek(fr, 0, SEEK_END);
		
	    char t[20*512];
	    fread (t, 512, 20, fr);
	    
		FILE *fw = NULL;
	    fw = fopen(argv[2], "wb"); // ouverture fichier mode "write binary"
	    if (fr == NULL) {printf("erreur ouverture fr\n");}
	    else
	    {
			printf("ouverture fw ok\n");
			
			fwrite(t, 512, 20, fw);
			
			if (fclose(fw) != 0) {printf("erreur fermeture fw\n");}
			else {printf("fermeture fw ok\n");}
		}
   
	    if (fclose(fr) != 0) {printf("erreur fermeture fr\n");}
	    else {printf("fermeture fr ok\n");}
    }

 
    return 0;
      
}
