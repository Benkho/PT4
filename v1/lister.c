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
    case 't':  
      printf ("ParamÃštre t recontrÃ© : lister les fichiers (et rÃ©pertoires) contenus dans une archive\n");
      
      FILE *fr = NULL;
      fr = fopen(argv[2], "rb"); // ouverture fichier mode "read binary"
      
        //determination taille fichier
      /* fseek(fr, 0, SEEK_END);
      long taillef, nb_bloc;
      taillef = ftell(fr);
      nb_bloc = taillef/512;
      printf("taille du fichier ouvert : %d = 512 * %d octets\n", taillef, nb_bloc);
      fseek(fr, 0, SEEK_SET);*/
      
       if (fr == NULL) {printf("erreur ouverture fr\n");}
      else
	{
	  printf("ouverture fr ok\n");
	  char t[20*512];
	  int p = 0;
	  fread(t,20*sizeof(fr), 1, fr);
	  String filename(t[0], 100);
	}
      if (fclose(fr) != 0) {printf("erreur fermeture fr\n");}
      else {printf("fermeture fr ok\n");}

      break;  
    }    
  return 0;
      
}

  
