#include <stdio.h>  
#include <unistd.h>  
  
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
  
    for (; optind < argc; ++optind)  
        printf ("argv[%d] : %s\n", optind, argv[optind]);  
  
    return 0;  
  
}
