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
#include<string.h>

int getopt (int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

const int TAILLE_BLOC = 512;
const int DEBUT_TAILLE_H = 24;
const int LONGUEUR_TAILLE_H = 12;
const int OFFSET_H = 376;


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

void compresser(char *filename){
	char cmd[100];
	sprintf(cmd, "gzip -9 %s", filename);
	printf("cmd: %s\n",cmd);
	system(cmd);
}

void lister(char *fichier){
      printf("lol %s\n", fichier);
      printf ("ParamÃštre t recontrÃ© : lister les fichiers (et rÃ©pertoires) contenus dans une archive\n");
      FILE *fr = NULL;
      fr = fopen(fichier, "rb"); // en mode "read binary" 
      
      if (fr == NULL) {printf("erreur ouverture fr %s\n",fichier);}
      else
	{
	  printf("ouverture fr ok (%s)\n",fichier);
	  

	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~determination taille fichier~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  fseek(fr, 0, SEEK_END);
	  long taillef, nb_bloc;
	  taillef = ftell(fr);
	  nb_bloc = taillef/TAILLE_BLOC;
	  fseek(fr, 0, SEEK_SET); // on remet le curseur au debut du fichier
	  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  int boucle;
	  long suivant = 0;
	  int div = 0;
	  int divtotal = 0;
	  int bourrage = 0;
	  int tailleDec = 0;
	  printf("-------------------------------------------------------------------\n");
 	for (boucle =1; boucle <6; boucle++){
	    char filename[100]; 
	    char taille[12]; // 124->136

	    //lire nom fichier
	    fread (filename, 100, 1, fr);
	    printf("Fichier %ld: Nom: %s\n",boucle, filename);
	    //lire la taille du fichier
	    fseek(fr, DEBUT_TAILLE_H, SEEK_CUR);
	    fread (taille,LONGUEUR_TAILLE_H , 1, fr);
	    fseek(fr, OFFSET_H, SEEK_CUR);
	    tailleDec = ocToDec(atoi(taille)); 
	    printf("Fichier %ld: Taille: %ld octets\n", boucle, tailleDec); //taille en décimal
	    printf("-------------------------------------------------------------------\n");

	    /*Algorithme permettant de se déplacer au fichier suivant dans l'archive */
	    div = (tailleDec+TAILLE_BLOC)/TAILLE_BLOC; 
	    divtotal = (div * TAILLE_BLOC)+TAILLE_BLOC;
	    bourrage = divtotal - (tailleDec+TAILLE_BLOC);
	    suivant = (tailleDec)+bourrage;
	    fseek(fr, suivant, SEEK_CUR);
	  } 
   	}


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
      printf ("ParamÃštre v recontrÃ© : mode verbose\n");
      break;  
    case 'c':  
      printf ("ParamÃštre c recontrÃ© : crÃ©er une archive Ã  partir d'une liste de fichiers (et de rÃ©pertoires)\n");
      
      // VOIR OPP2  
      
      break;  
    case 't':  
	lister(argv[2]);
      break;  
      
    case 'r':  
      printf ("ParamÃštre r recontrÃ© : ajouter de nouveaux fichiers (ou repertoires) Ã  une archive existante\n");
      break;  
    case 'u':  
      printf ("ParamÃštre u recontrÃ© : pour mettre Ã  jour l'archive si les fichiers listÃ©s sont plus rÃ©cents que ceux archivÃ©s\n");
      break;  
    case 'x':  
	break;  
    case 'f':  
   	 printf("Nom du fichier: %s\n", argv[2]);
      break;  
    case 'z':
	compresser(argv[2]);
      break;  
    case 'd':  
      printf ("ParamÃštre d recontrÃ© : pour supprimer un fichier d'une archive\n");
      break;  
    case 's':  
      printf ("ParamÃštre s recontrÃ©\nAvec 'parse' : pour Ã©conomiser de la place pour stocker les fichier contenant beaucoup de zÃ©ros consÃ©cutifs (sparse file)");
      break;  
    case 'm':  
      printf ("ParamÃštre m recontrÃ© : pour afficher les diffÃ©rences entre les fichiers archivÃ©s et les fichiers existants en utilisant la commande Unix 'diff'\n");
      break; 
    }  
    return 0;      
}



