
cp ~/Desktop/lol.tar /tmp
mkdir /tmp/sortie
mkdir /tmp/sortie

gcc opp_nv.c -lm

 // rm -f /tmp/sortie/* && gcc opp_nv.c -lm

./a.out -x /tmp/lol.tar /tmp/sortie/








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~determination taille fichier~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fseek(fr, 0, SEEK_END);
long taillef, nb_bloc;
taillef = ftell(fr);
nb_bloc = taillef/TAILLE_BLOC;
printf("taille du fichier ouvert (%s) : %d = 512 * %d octets\n", argv[2], taillef, nb_bloc);
fseek(fr, 0, SEEK_SET); // on remet le curseur au debut du fichier
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



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
    printf("la taille en octal string du fichier est: %s \n",taille_octal_str);
    //string -> int
    int taille_oct, taille_dec;
    taille_oct = 0;
    taille_dec = 0;
    taille_oct = atoi(taille_octal_str);
    printf("la taille en octal int du fichier est: %i \n",taille_oct);
    //octal -> decimal
    int i=0;
    while(taille_oct!=0)
    {
      taille_dec = taille_dec + (taille_oct % 10) * pow(8,i++);
      taille_oct = taille_oct/10;
    }
    printf("la taille en decimal int du fichier est: %ld \n",taille_dec);

    
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









CC=gcc
CFLAGS=-std=c99 -lm
EXEC=taar

all: $(EXEC)

taar: taar.o 
    $(CC) -o taar taar.o

taar.o: taar.c
    $(CC) -o taar.o -c taar.c $(CFLAGS)

clean:
    rm -rf *.o

mrproper: clean
    rm -rf $(EXEC)



CC=gcc
CFLAGS=-lm
LDFLAGS=
EXEC=taar

all: $(EXEC)

functions: functions.o taar.o
    $(CC) -o functions functions.o taar.o $(LDFLAGS)

functions.o: functions.c
    $(CC) -o functions.o -c functions.c $(CFLAGS)

taar.o: taar.c functions.h
    $(CC) -o taar.o -c taar.c $(CFLAGS)

clean:
    rm -rf *.o

mrproper: clean
    rm -rf $(EXEC)


CC=gcc -lm
CFLAGS=
LDFLAGS=
EXEC=taar
OBJECTS= functions.o taar.o 
TARGET=taar

$(TARGET): $(OBJECTS)
    $(CC) $(OBJECTS) -o $(TARGET)

functions.o: functions.c functions.h
    $(CC) -c functions.c

taar.o: taar.c functions.h
    $(CC) -c taar.c
    
clean:
    rm -f *~ *.o $(TARGET)


$(CC) -c functions.c
$(CC) -c main.c
$(CC) functions.o main.o -o taar -lm