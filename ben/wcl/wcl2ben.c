// test de recodage de la commande wc

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char**argv)
{
	int i;
	
	if ( (argc == 1) || (argc > 2) ) fprintf(stderr, "erreur de syntaxe : utilisez \"wcl2 nomdufichier\" \n");
	
	else
	{
		printf("il y a %i arguments, les voila :\n", argc);
		for (i=0; i<argc; i++)
		{
			printf("- %s \n", argv[i]);
		}
		
		int fd;
		int cd;
		
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
			int nbOctLu;
			char lecture;
			
			nbOct = 1;
			nbOctLu = 0;

			while (nbOct > 0)
			{
				nbOct = read(fd, &lecture, 1000000);
				nbOctLu = nbOctLu + nbOct;
			}
			
			printf("nombre d'octets lus : %i\n", nbOctLu);					
			//~ printf("cahr lus : %s\n", lecture);			
			
			cd = close(fd); //fermeture du fichier par son descripteur
			if (cd == -1) fprintf (stderr, "erreur de fermeture fichier %s\n", argv[1]);
			else fprintf(stdout, "fermeture fichier ok\n");
		}
		
	}
}
