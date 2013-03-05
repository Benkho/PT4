/*
 * utilisation :
 * ./a.out -x fichierTAR.tar
 * 
 * */


#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<math.h>

int getopt (int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

const int TAILLE_BLOC = 512;

int ocToDec(int oct){
  long int octal,decimal =0;
  int i=0;
  octal = oct;
  while(octal!=0){
    decimal = decimal + (octal % 10) * pow(8,i++);
    octal = octal/10;
  }
  return decimal;
}


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
      
      // VOIR OPP2  
      
      break;  
    case 't':  

      printf ("Paramètre t recontré : lister les fichiers (et répertoires) contenus dans une archive\n");

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
	  char filename[100]; 
	  //  printf("retour de fread filename, la fonction a lu : %i éléments \n",  fread (filename, 100, 1, fr));
	  char taille[12]; // 124->136
	  // printf("retour de fread taille, la fonction a lu : %i éléments \n",  fread (taille, 12, 1, fr));

	  int tailleDec =  ocToDec(taillef);

	  //	  printf("taille tar %ld\n", tailleDec);
	  printf("taille : %ld\n",taillef);

	  printf("position 1 : %ld\n", ftell(fr));
	  //while(ftell(fr) < taillef ){

	    fread (filename, 100, 1, fr);
	    printf("Fichier 1 nom: %s\n", filename);
	    fseek(fr, 124, SEEK_SET);
	    fread (taille, 12, 1, fr);
	    int decimal =  ocToDec(atoi(taille));
	    printf("Fichier 1 taille: %ld octets\n", decimal);
	    fseek(fr, decimal, SEEK_SET);

	    printf("position 2 : %ld\n", ftell(fr));

	    fseek(fr, f, SEEK_SET);
	    fread (filename, 100, 1, fr);
	    printf("Fichier 2 nom: %s\n", filename);
	    fseek(fr, ftell(fr)+24, SEEK_SET);
	    fread (taille, 12, 1, fr);
	    decimal =  ocToDec(atoi(taille));
	    printf("Fichier 2 taille: %ld octets\n", decimal);
	    fseek(fr, decimal, SEEK_SET);

	    printf("position 3 : %ld\n", ftell(fr));

	    //}
   	}
      break;  

    case 'r':  
      printf ("Paramètre r recontré : ajouter de nouveaux fichiers (ou repertoires) à une archive existante\n");
      break;  
    case 'u':  
      printf ("Paramètre u recontré : pour mettre à jour l'archive si les fichiers listés sont plus récents que ceux archivés\n");
      break;  
    case 'x':  
      /*      printf ("Paramètre x recontré : pour extraire les fichiers de l'archive\n");
      
      //affichage des arguments
      for (; optind < argc; ++optind)  
	printf ("argv[%d] : %s\n", optind, argv[optind]);
      
//état des variables (utile pour boucle)
//~ printf("argc :%d\n", argc);
//~ printf("optind :%d\n", optind);
// -------------------------------------
 
//ouverture du fichier TAR à désarchiver
      FILE *fr = NULL;
      fr = fopen(argv[2], "rb"); // en mode "read binary" 
      
      if (fr == NULL)
	{
	  printf("erreur ouverture fr (%s)\n"),argv[2];
	}
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
      
	  */

	//-------------------Récuperation des infos du HEADER---------------------------------------------------------------------
	
	/*
    EXPLOITATION DE L'ENTETE AVEC FREAD :
    * 
    * t[0   -> 100] : nom du fichier
    * t[100 -> 108] : permissions
    * t[108 -> 116] : propriétaire (id)
    * t[116 -> 124] : groupe (id)
    * t[124 -> 136] : taille en octets
    * t[136 -> 148] : dernière modification en temps Unix
    * t[148 -> 156] : somme de contrôle de l'en-tête
    * t[156 -> 157] : type de fichier
    * t[157 -> 257] : nom du fichier lié
    * t[ -> ] : 
	*/
      /*	
    char filename[100];
	printf("retour de fread filename, la fonction a lu : %i éléments \n",  fread (filename, 100, 1, fr));
	
    char permissions[8];
	printf("retour de fread permissions, la fonction a lu : %i éléments \n",  fread (permissions, 8, 1, fr));
	
    char proprio[8];
    printf("retour de fread proprio, la fonction a lu : %i éléments \n",  fread (proprio, 8, 1, fr));
    
    char groupe[8];
    printf("retour de fread groupe, la fonction a lu : %i éléments \n",  fread (groupe, 8, 1, fr));
    
    char taille[12];
    printf("retour de fread taille, la fonction a lu : %i éléments \n",  fread (taille, 12, 1, fr));
    
    char last_modif[12];
    printf("retour de fread last_modif, la fonction a lu : %i éléments \n",  fread (last_modif, 12, 1, fr));
    
    char checksum[8];
    printf("retour de fread checksum, la fonction a lu : %i éléments \n",  fread (checksum, 8, 1, fr));
    
    char type[1];
    printf("retour de fread type, la fonction a lu : %i éléments \n",  fread (type, 1, 1, fr));
    
    char linkname[100];
    printf("retour de fread linkname, la fonction a lu : %i éléments \n",  fread (linkname, 100, 1, fr));
    
    char headrest[255];
    printf("retour de fread headrest, la fonction a lu : %i éléments \n",  fread (headrest, 255, 1, fr));
    
    char fileraw[(TAILLE_BLOC*nb_bloc)-TAILLE_BLOC];
    printf("retour de fread fileraw, la fonction a lu : %i éléments \n",  fread (fileraw, TAILLE_BLOC, (nb_bloc-1), fr));
    
    //------------------------------------------------------------------------------------------------------------------------
	
	//NOM DU FICHIER t[0   -> 100]
	FILE *file_n = NULL;
	file_n = fopen(filename, "w");  /* write */
      /*	if (file_n == NULL) {printf("erreur ouverture file_n\n");}
	else
	{
		printf("ouverture file_n ok (%s)\n",filename);
		
		if (fclose(file_n) != 0) {printf("erreur fermeture file_n (%s)\n",filename);}
		else {printf("fermeture file_n ok (%s)\n",filename);}
	}
	
	//ecriture du fichier lui même [ 512 -> ...]
	file_n = fopen(filename, "ab");  /* add binary */
      /*	if (file_n == NULL) {printf("erreur ouverture file_n\n");}
	else
	{
		printf("ouverture file_n ok (%s)\n",filename);
		printf("retour de fwrite, la fonction a écrit : %i octets\n", fwrite(fileraw, TAILLE_BLOC, (nb_bloc-1), file_n));
		
		if (fclose(file_n) != 0) {printf("erreur fermeture file_n (%s)\n",filename);}
		else {printf("fermeture file_n ok (%s)\n",filename);}
	}
	
	/*
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
		printf("retour de fwrite, la fonction a écrit : %i octets\n", fwrite(tab_header, 8, 1, fw));
		printf("retour de fwrite, la fonction a écrit : %i octets\n", fwrite(t, TAILLE_BLOC, nb_bloc, fw));
		
		if (fclose(fw) != 0) {printf("erreur fermeture fw\n");}
		else {printf("fermeture fw ok\n");}
	}
	*/
      /*	
    if (fclose(fr) != 0) {printf("erreur fermeture fr\n");}
    else {printf("fermeture fr ok\n");}
}*/


break;  
    case 'f':  
      printf ("Paramètre f recontré : pour indiquer le nom du fichier archive, sinon tar utilise l'entrée et la sortie standard avec les options précédentes\n");
      break;  
    case 'z':  
      printf ("Paramètre z recontré : pour compresser le fichier d'archive (en utilisant gzip)\n");
      break;  
    case 'd':  
      printf ("Paramètre d recontré : pour supprimer un fichier d'une archive\n");
      break;  
    case 's':  
      printf ("Paramètre s recontré\nAvec 'parse' : pour économiser de la place pour stocker les fichier contenant beaucoup de zéros consécutifs (sparse file)");
      break;  
    case 'm':  
      printf ("Paramètre m recontré : pour afficher les différences entre les fichiers archivés et les fichiers existants en utilisant la commande Unix 'diff'\n");
      break; 
    }  

 
    return 0;
      
}
