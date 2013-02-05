/*main.c
On souhaite que notre commande s’utilise de la façon suivante :
wcl2 nomdemonfichier
avec nomdemonfichier le nom du fichier texte que l’on souhaite ouvrir pour obtenir
une statistique sur le nombre de mots.
*/

#include<stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*fonction qui teste la lettre pointée par c */
/* retourne 1 si la lettre est un separateur */
/* 0 sinon */
int is_separator (char c){
  int status = 0; 
  switch (c) {
  case '\n':
  case ' ' :
  case ',' :
  case ';' :
  case '.' :
  case '!' :
  case '?' :
  case ':' : status =1 ; break;
  default : status = 0; break;
  }
  return status; 
}


int main(int argc, char**argv)
{
  int fd,nblu, etat_courant;
  char lecture;
  int nbmot = 0;
  if ((argc == 1)||(argc >2)) {fprintf (stderr,"usage : wcl2 nomdefichier\n"); return 1;}
  else {
    fd = open (argv[1],O_RDONLY,0);
    if (fd == -1) {fprintf (stderr,"wcl2 : %s n'existe pas \n",argv[1]); return 1;}
    else{
      nblu = 1;
      etat_courant=2;
      while (nblu > 0) {	
	nblu = read (fd,&lecture,1);
	if (nblu == -1) {fprintf (stderr,"erreur de lecture du fichier \n"); return 1;}
	if (nblu > 0) {
	  if (is_separator(lecture) == 1) { /* *lecture est un séparateur */
	    if (etat_courant == 1 ) etat_courant = 2;	 	        	      	
	  }
	  else { /* *lecture est une lettre */
	    if (etat_courant == 2) {etat_courant = 1; nbmot++;}
	  }
	}
      }
      close(fd);
    }
  }
  printf("%i\n",nbmot);	
  return 0;
}
