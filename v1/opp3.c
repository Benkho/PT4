/*
 * utilisation :
 * 
 * 		./a.out			-x			fichierTAR.tar			cheminDeSortie
 * 
 *       argv[0]	  argv[1]			argv[2]				    argv[3]
 * */


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
		   
    // VOIR OPP2  
      
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

//affichage des arguments
for (; optind < argc; ++optind)  
	printf ("argv[%d] : %s\n", optind, argv[optind]);

//etat des variables (utile pour boucle)
//~ printf("argc :%d\n", argc);
//~ printf("optind :%d\n", optind);
// -------------------------------------

//ouverture du fichier TAR à desarchiver
FILE *fr = NULL;
fr = fopen(argv[2], "rb"); // en mode "read binary" 

if (fr == NULL) {printf("erreur ouverture fr (%s)\n"),argv[2];}
else
{
	printf("ouverture fr ok (%s)\n",argv[2]);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~determination taille fichier~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fseek(fr, 0, SEEK_END);
	long taillef, nb_bloc;
	taillef = ftell(fr);
	nb_bloc = taillef/TAILLE_BLOC;
	printf("taille du fichier ouvert (%s) : %d = 512 * %d octets\n", argv[2], taillef, nb_bloc);
	fseek(fr, 0, SEEK_SET); // on remet le curseur au debut du fichier
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//DEBUT BOUCLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int boucle;
for (boucle = 0; boucle < 3; boucle++)
{

	printf("\n debut boucle et i = %i\n",boucle);
		
	//-------------------Recuperation des infos du HEADER---------------------------------------------------------------------
	
	/*
    EXPLOITATION DE L'ENTETE AVEC FREAD :
    * 
    * t[0   -> 100] : nom du fichier
    * t[100 -> 108] : permissions
    * t[108 -> 116] : proprietaire (id)
    * t[116 -> 124] : groupe (id)
    * t[124 -> 136] : taille en octets
    * t[136 -> 148] : dernière modification en temps Unix
    * t[148 -> 156] : somme de contrôle de l'en-tête
    * t[156 -> 157] : type de fichier
    * t[157 -> 257] : nom du fichier lie
    * t[ -> ] : 
	*/
	
    char filename[100];
	printf("retour de fread filename, la fonction a lu : %i elements \n",  fread (filename, 100, 1, fr));
	printf("nom du fichier = %s \n",filename);
    char permissions[8];
	printf("retour de fread permissions, la fonction a lu : %i elements \n",  fread (permissions, 8, 1, fr));
	
    char proprio[8];
    printf("retour de fread proprio, la fonction a lu : %i elements \n",  fread (proprio, 8, 1, fr));
    
    char groupe[8];
    printf("retour de fread groupe, la fonction a lu : %i elements \n",  fread (groupe, 8, 1, fr));
    
    char taille_octal_str[12];
    printf("retour de fread taille_octal_str, la fonction a lu : %i elements \n",  fread (taille_octal_str, 12, 1, fr));
    
	//affichage taille fichier
	printf("test taille en octal : %s \n",taille_octal_str);
	//string -> int
	int taille_oct, taille_dec;
	taille_oct = atoi(taille_octal_str);
    //octal -> decimal
    int i=0;
    while(taille_oct!=0)
    {
        taille_dec = taille_dec + (taille_oct % 10) * pow(8,i++);
        taille_oct = taille_oct/10;
    }
    printf("Equivalent decimal value: %ld \n",taille_dec);
	
    
    char last_modif[12];
    printf("retour de fread last_modif, la fonction a lu : %i elements \n",  fread (last_modif, 12, 1, fr));
    
    char checksum[8];
    printf("retour de fread checksum, la fonction a lu : %i elements \n",  fread (checksum, 8, 1, fr));
    
    char type[1];
    printf("retour de fread type, la fonction a lu : %i elements \n",  fread (type, 1, 1, fr));
    
    char linkname[100];
    printf("retour de fread linkname, la fonction a lu : %i elements \n",  fread (linkname, 100, 1, fr));
    
    char headrest[255];
    printf("retour de fread headrest, la fonction a lu : %i elements \n",  fread (headrest, 255, 1, fr));
    
    char fileraw[taille_dec];
    printf("retour de fread fileraw, la fonction a lu : %i elements \n",  fread (fileraw, 1, taille_dec, fr));
    
    //------------------------------------------------------------------------------------------------------------------------
	
	//ajout chemin fichier de sortie
	char filepath[100];
    sprintf(filepath, "%s%s", argv[3], filename);
    printf("test filepath : %s\n", filepath);
	
	//NOM DU FICHIER t[0   -> 100]
	FILE *file_n = NULL;
	file_n = fopen(filepath, "w");  /* write */
	if (file_n == NULL) {printf("erreur ouverture file_n (%s)\n",filepath);}
	else
	{
		printf("ouverture file_n ok (%s)\n",filepath);
		
		if (fclose(file_n) != 0) {printf("erreur fermeture file_n (%s)\n",filepath);}
		else {printf("fermeture file_n ok (%s)\n",filepath);}
	}
	

	
	//ecriture du fichier lui même [ 512 -> ...]
	file_n = fopen(filepath, "ab");  /* add binary */
	if (file_n == NULL) {printf("erreur ouverture file_n (%s)\n",filepath);}
	else
	{
		printf("ouverture file_n ok (%s)\n",filepath);
		printf("retour de fwrite, la fonction a ecrit : %i octets\n", fwrite(fileraw, 1, taille_dec, file_n));
		
		if (fclose(file_n) != 0) {printf("erreur fermeture file_n (%s)\n",filepath);}
		else {printf("fermeture file_n ok (%s)\n",filepath);}
	}
	
	printf("position du curseur dans fr avant decalage : %i \n", ftell(fr));
	fseek(fr, 135, SEEK_CUR);
		printf("position du curseur dans fr apres decalage : %i \n", ftell(fr));

	printf("fin boucle\n\n");
	
}	
    if (fclose(fr) != 0) {printf("erreur fermeture fr (%s)\n",argv[2]);}
    else {printf("fermeture fr ok (%s)\n",argv[2]);}
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
