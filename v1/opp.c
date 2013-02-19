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
    
    
    FILE *fichier = NULL;
    fichier = fopen(argv[1], "r"); // ouverture fichier mode "read"
    if (fichier == NULL) {printf("erreur ouverture fichier\n");}
    
    
    
    
    
    /*
    else
    {
		printf("ouverture fichier ok\n");
		
		char phrase[100000];  
  
		while (fgets(phrase, 10000, fichier) != NULL)
		{  
			printf ("\n");  
			printf (phrase);  
		}
		
	*/	
		
		/*
		char lu[100000];
		int i;
		i=0;

		fread(lu, 1000000000000000, 1, fichier);
		for (i=0; i<100000; i++)
		{
			printf("lecture :   %s\n", lu[i]);
		}
		*/
		
		int fcl;
	    if (fclose(fichier) != 0) {printf("erreur fermeture fichier\n");}
	    else {printf("fermeture fichier ok\n");}
	}
    
        
/*    
	int fd;
	fd = open(argv[1], O_RDONLY, 0);
	if (fd == -1)
	{
		fprintf (stderr, "erreur d'ouverture fichier %s\n", argv[1]);
		return 1;
	}
	else 
	{
		fprintf(stdout, "ouverture fichier ok\n");
		
		int nbOct;
		char lecture;
		nbOct = 1;

		while (nbOct > 0)
		{
			nbOct = read(fd, &lecture, 1);
			printf ("nbOct : %i\n", nbOct);
			fprintf (stdout, "lecture : %i\n", lecture);
		}
		
		int cd;
		cd = close(fd); //fermeture du fichier par son descripteur
		if (cd == -1) fprintf (stderr, "erreur de fermeture fichier %s\n", argv[1]);
		else fprintf(stdout, "fermeture fichier ok\n");
	}
*/  
    return 0;  
  
}
