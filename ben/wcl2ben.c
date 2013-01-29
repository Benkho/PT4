// test de recodage de la commande wc

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


void main(int argc, char**argv)
{
	int i;
	
	if ( (argc == 1) || (argc > 2) )
	{
		fprintf(stderr, "erreur de syntaxe : utilisez \"wcl2 nomdufichier\" \n");
	}
	
	else
	{
		printf("il y a %i arguments\n", argc);
		printf("les voila :\n");
		for (i=0; i<argc; i++)
		{
			printf("%s \n", argv[i]);
		}
	}
}
