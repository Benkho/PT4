
/*
 ====fseek(pf,deplacement,reference)====
 FILE *pf; // le pointeur vers le fichier en question
 long deplacement; // le déplacement à réaliser
 int reference; //point de référence pour le déplacement
-le début du fichier si reference vaut SEEK_SET (valant en fait 0) 
-la position courante si reference vaut SEEK_CUR (valant en fait 1) 
-la fin du fichier si reference vaut SEEK_END (valant en fait 2) 

====long ftell (FILE *stream) ====
Elle permet juste de renvoyer la position actuelle du curseur dans le fichier

====size_t fread (void *ptr, size_t size, size_t nmemb, FILE *stream)====
fread pour lire dans les fichiers binaires.
Comme vous le voyez, cette fonction va renvoyer une variable de type size_t qui est en fait une valeur entière contenant le nombre d'éléments que la fonction aura lu. En ce qui concerne les arguments, vous voyez que cette fonction en prend 4 et ceux-ci sont les même que pour la fonction fwrite. Le premier déterminera dans quelle variable les données lues seront stockées, le deuxième désigne la taille des données qui seront lues, le troisième définit le nombre de fois que nous lirons cette taille et le dernier paramètre est le pointeur de fichier dans lequel la lecture s'effectuera.

====int getopt (int argc, char * const argv[], const char * optstring)==== 
extern char * optarg;  
extern int optind, opterr;

*/
/* tarfile.cpp : lecture d'un fichier TAR
 *
 *	** ne fait que lister les fichiers TARés **
 *  ** ne traite ques les fichiers TAR au format USTAR **
 */
#include <stdio.h>  
#include <unistd.h>  
  
int main(int argc, char *argv[]) {  
  
    int optch;  
    extern int opterr;  
  
    char format[] = "abc:co:";  
  
    opterr = 1;  
  
    while ((optch = getopt(argc, argv, format)) != -1)  
    switch (optch) {  
        case 'a':  
            printf ("Paramètre a recontré\n");  
            break;  
        case 'b':  
            printf ("Paramètre b recontré\n");  
            break;  
        case 'c':  
            printf ("Paramètre c rencontré avec argument %s\n", optarg);  
            break;  
        case 'o':  
            printf ("Paramètre o rencontré avec argument %s\n", optarg);  
            break;  
    }  
  
    for (; optind < argc; ++optind)  
        printf ("argv[%d] : %s\n", optind, argv[optind]);  
  
    return 0;  
  
}  
