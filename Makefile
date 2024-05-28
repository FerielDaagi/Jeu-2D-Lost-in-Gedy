game:main.o perso.o   
	gcc main.o perso.o -o game -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
perso.o:perso.c
	gcc -c perso.c -g 
 
